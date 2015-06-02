#include "NetConnection.h"
#include "NetServer.h"

#include <boost/bind.hpp>

NetConnection::NetConnection(NetServer& INnetServer, SocketPtr INpSocket, UInt32 INconnectionID)
	:m_netServer(INnetServer), m_socket(INpSocket), m_connectionID(INconnectionID),
	m_receivePacketCount(0), m_receivePacket(EPacket_Small_MaxBodyLength), m_receiveBigPacket(EPacket_Big_MaxBodyLength)
{

}

NetConnection::~NetConnection()
{
	Stop();
}

const char* NetConnection::GetIP()
{
	return m_socket->remote_endpoint().address().to_string().c_str();
}

void NetConnection::Start()
{
	DoReadPacketHead();
}

void NetConnection::Update()
{
	//std::lock_guard<std::mutex> guard(m_receiveDequeMutex);
	//while(!m_receivedPacketDeque.empty())
	//{
	//	ReceivedPacket packet = std::move(m_receivedPacketDeque.front());
	//	
	//	m_receivedPacketDeque.pop_front();
	//}

}

void NetConnection::Stop()
{
	if(m_socket && m_socket->is_open())
	{
		//m_socket->shutdown(boost::asio::ip::tcp::socket::socket_base::shutdown_both);
		boost::system::error_code ignored_ec;
		m_socket->close(ignored_ec);
		cout << "Socket Close Exception, ErrorCode : " << ignored_ec << endl;
	}

	m_receivedPacketDeque.clear();
	m_receivePacket.Clear();
	m_receiveBigPacket.Clear();
	m_sendPacketDeque.clear();
}

void NetConnection::Close()
{
	if (m_socket && m_socket->is_open())
	{
		//m_socket->shutdown(boost::asio::ip::tcp::socket::socket_base::shutdown_both);
		boost::system::error_code ignored_ec;
		m_socket->close(ignored_ec);
		cout << "Socket Close Exception, ErrorCode : " << ignored_ec << endl;
	}
}

void NetConnection::GetReceivedPacketDeque(ReceivedPacketDeque& OUTpacketDeque)
{
	std::lock_guard<std::mutex> lockGuard(m_receiveDequeMutex);
	OUTpacketDeque = std::move(m_receivedPacketDeque);
	m_receivedPacketDeque.clear();
}

void NetConnection::Send(SendPacket& INsendPacket)
{
	if (m_socket && m_socket->is_open())
	{
		bool write_in_progress = !m_sendPacketDeque.empty();
		m_sendPacketDeque.push_back(std::move(INsendPacket));
		if (!write_in_progress)
		{
			DoWrite();
		}
	}
	//auto self(shared_from_this());
	//m_netServer.GetIoService().GetIOService().post(
	//	[this, self, INsendPacket]()
	//{
	//	if (m_socket && m_socket->is_open())
	//	{
	//		bool write_in_progress = !m_sendPacketDeque.empty();
	//		m_sendPacketDeque.push_back(std::move(INsendPacket));
	//		if (!write_in_progress)
	//		{
	//			DoWrite();
	//		}
	//	}
	//});
}

void NetConnection::DoReadPacketHead()
{
	boost::asio::async_read(*m_socket,
		boost::asio::buffer(m_receivePacket.GetPacketDef().packetData.data(), EPacketHeaderLength), boost::bind(&NetConnection::OnReadPacketHeaderComplete, shared_from_this(), boost::asio::placeholders::error));
}

void NetConnection::DoReadPacketBody()
{
	if(m_receivePacket.GetPacketDef().packetLength > EPacket_Small_MaxBodyLength)
	{
		m_receiveBigPacket.GetPacketDef().packetLength = m_receivePacket.GetPacketDef().packetLength;

		boost::asio::async_read(*m_socket,
			boost::asio::buffer(m_receiveBigPacket.GetPacketDef().packetData.data(), m_receiveBigPacket.GetPacketDef().packetLength), boost::bind(&NetConnection::OnReadPacketBodyComplete, shared_from_this(), boost::asio::placeholders::error));

	}
	else
	{
		boost::asio::async_read(*m_socket,
			boost::asio::buffer(m_receivePacket.GetPacketDef().packetData.data(), m_receivePacket.GetPacketDef().packetLength), boost::bind(&NetConnection::OnReadPacketBodyComplete, shared_from_this(), boost::asio::placeholders::error));
	}
}

void NetConnection::OnReadPacketHeaderComplete(boost::system::error_code ec)
{
	// 
#ifdef NET_DEBUG_INFO
	cout << "Receive Packet Header" << endl;
#endif
	if (!ec && m_receivePacket.DecodeHeader())
	{
#ifdef NET_DEBUG_INFO
		cout << "Packet Header Length is : " << m_receivePacket.GetPacketDef().packetLength << endl;
#endif
		DoReadPacketBody();
	}
	else
	{
		m_receivePacket.Clear();
		m_receivePacket.SetConnectionID(m_connectionID);
		m_receivePacket.SetPacketType(EPacketTypeSpecial_Disconnect);
		m_netServer.AddReceivedPacket(m_receivePacket);
		m_receivePacket.Clear();

		cout << "Error : " << ec << " Stop Client " << endl;
		m_netServer.StopClient(shared_from_this());
	}
}

void NetConnection::OnReadPacketBodyComplete(boost::system::error_code ec)
{
#ifdef NET_DEBUG_INFO
	cout << "Receive Packet Body" << endl;
#endif
	if (!ec)
	{
		{
			bool reCount = false;
			if(m_receivePacketCount >= 100000000)
			{
				reCount = false;
				m_receivePacketCount = 1;
			}
			else
			{
				++m_receivePacketCount;
			}
			
			// 投递网络消息包
			if(m_receivePacket.GetPacketDef().packetLength > EPacket_Small_MaxBodyLength)
			{
				m_receiveBigPacket.SetConnectionID(m_connectionID);
				if(!reCount && m_receivePacketCount == 1)
				{
					m_receiveBigPacket.SetPacketType(EPacketTypeSpecial_Connect);
				}
				m_netServer.AddReceivedPacket(m_receiveBigPacket);
				m_receiveBigPacket.Clear();
			}
			else
			{
				m_receivePacket.SetConnectionID(m_connectionID);
				if(!reCount && m_receivePacketCount == 1)
				{
					m_receivePacket.SetPacketType(EPacketTypeSpecial_Connect);
				}
				m_netServer.AddReceivedPacket(m_receivePacket);
				m_receivePacket.Clear();
			}
		}

		DoReadPacketHead();
	}
	else
	{
		m_receivePacket.Clear();
		m_receivePacket.SetConnectionID(m_connectionID);
		m_receivePacket.SetPacketType(EPacketTypeSpecial_Disconnect);
		m_netServer.AddReceivedPacket(m_receivePacket);
		m_receivePacket.Clear();
		cout << "Error : " << ec << " Stop Client " << endl;
		m_netServer.StopClient(shared_from_this());
	}
}

void NetConnection::DoWrite()
{
	auto self(shared_from_this());
	boost::asio::async_write(*m_socket,
		boost::asio::buffer(m_sendPacketDeque.front().GetEnPacket().GetString(),
		m_sendPacketDeque.front().GetEnPacket().GetLength()),
		[this, self](boost::system::error_code ec, std::size_t length)
	{
		if (!ec)
		{
#ifdef NET_DEBUG_INFO
			cout << "Send Packet Complete, Size : " << length << endl;
#endif
			m_sendPacketDeque.pop_front();
			if (!m_sendPacketDeque.empty())
			{
				DoWrite();
			}
		}
		else
		{
			m_receivePacket.Clear();
			m_receivePacket.SetConnectionID(m_connectionID);
			m_receivePacket.SetPacketType(EPacketTypeSpecial_Disconnect);
			m_netServer.AddReceivedPacket(m_receivePacket);
			m_receivePacket.Clear();

			cout << "Error : " << ec << " Stop Client " << endl;
			m_netServer.StopClient(shared_from_this());
		}
	});
}