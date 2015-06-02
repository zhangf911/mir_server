#include "NetClientEx.h"
#include "NetServer.h"

NetClientEx::NetClientEx(IoService& INIoService)
: m_socket(INIoService.GetIOService()), m_receivedPacket(EPacket_Small_MaxBodyLength), m_receivedBigPacket(EPacket_Big_MaxBodyLength), m_ioService(INIoService)
{
	m_receivedPacket.Clear();
	m_receivedBigPacket.Clear();
	m_sendPacketDeque.clear();

	m_bConnect = false;
}

NetClientEx::~NetClientEx()
{
	boost::system::error_code ignored_ec; 
	m_socket.close(ignored_ec);

	Clear();
}

void NetClientEx::Send(SendPacket& INsendPacket)
{
	m_ioService.GetIOService().post(
		[this, INsendPacket]()
	{
		bool write_in_progress = !m_sendPacketDeque.empty();
		m_sendPacketDeque.push_back(std::move(INsendPacket));
		if (!write_in_progress)
		{
			DoWrite();
		}
	});
}

void NetClientEx::Close()
{
	m_ioService.GetIOService().post([this]() { boost::system::error_code ignored_ec; m_socket.close(ignored_ec); });
}

void NetClientEx::DoConnect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
	cout << "Connect To Server " << endpoint_iterator->host_name() 
		<< " IP : " << endpoint_iterator->endpoint().address() 
		<< " Port : " << endpoint_iterator->endpoint().port()
		<< endl;
	boost::asio::async_connect(m_socket, endpoint_iterator,
		[this](boost::system::error_code ec, boost::asio::ip::tcp::resolver::iterator)
	{
		if (!ec)
		{
			cout << "Connect Server " << m_socket.remote_endpoint().address() << ":" << m_socket.remote_endpoint().port() << " Succeed!" << endl;

			//m_receivedPacket.Clear();
			//m_receivedBigPacket.Clear();
			//m_sendPacketDeque.clear();

			m_bConnect = true;

			DoReadHeader();
		}
		else
		{
			cout << "Connect Server Failed!" << endl;
			boost::system::error_code ignored_ec;
			m_socket.close(ignored_ec);

			Clear();
 		}
	});
}

void NetClientEx::DoReadHeader()
{
	boost::asio::async_read(m_socket,
		boost::asio::buffer(m_receivedPacket.GetPacketDef().packetData.data(), EPacketHeaderLength),
		[this](boost::system::error_code ec, std::size_t /*length*/)
	{
		if (!ec && m_receivedPacket.DecodeHeader())
		{
			DoReadBody();
		}
		else
		{
			m_receivedPacket.Clear();
			m_receivedPacket.SetPacketType(EPacketTypeSpecial_Disconnect);
			AddReceivedPacket(m_receivedPacket);
			m_receivedPacket.Clear();

			cout << "Error : " << ec << " Stop Client " << endl;

			boost::system::error_code ignored_ec; 
			m_socket.close(ignored_ec);

			Clear();
		}
	});
}

void NetClientEx::DoReadBody()
{
	if(m_receivedPacket.GetPacketDef().packetLength > EPacket_Small_MaxBodyLength)
	{
		m_receivedBigPacket.GetPacketDef().packetLength = m_receivedPacket.GetPacketDef().packetLength;

		boost::asio::async_read(m_socket,
			boost::asio::buffer(m_receivedBigPacket.GetPacketDef().packetData.data(), m_receivedBigPacket.GetPacketDef().packetLength),
			[this](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
#ifdef NET_DEBUG_INFO
				cout << "Receive Packet Body, Size : " << length << endl;
#endif
				{
					if(m_receivedPacket.GetPacketDef().packetLength > EPacket_Small_MaxBodyLength)
					{
						AddReceivedPacket(m_receivedBigPacket);
						m_receivedBigPacket.Clear();
					}
					else
					{
						AddReceivedPacket(m_receivedPacket);
						m_receivedPacket.Clear();
					}
				}
				DoReadHeader();
			}
			else
			{
				m_receivedPacket.Clear();
				m_receivedPacket.SetPacketType(EPacketTypeSpecial_Disconnect);
				AddReceivedPacket(m_receivedPacket);
				m_receivedPacket.Clear();

				cout << "Error : " << ec << " Stop Client " << endl;

				boost::system::error_code ignored_ec;
				m_socket.close(ignored_ec);

				Clear();
			}
		});
	}
	else
	{
		boost::asio::async_read(m_socket,
			boost::asio::buffer(m_receivedPacket.GetPacketDef().packetData.data(), m_receivedPacket.GetPacketDef().packetLength),
			[this](boost::system::error_code ec, std::size_t length)
		{
			if (!ec)
			{
#ifdef NET_DEBUG_INFO
				cout << "Receive Packet Body, Size : " << length << endl;
#endif
				{
					if(m_receivedPacket.GetPacketDef().packetLength > EPacket_Small_MaxBodyLength)
					{
						AddReceivedPacket(m_receivedBigPacket);
						m_receivedBigPacket.Clear();
					}
					else
					{
						AddReceivedPacket(m_receivedPacket);
						m_receivedPacket.Clear();
					}
				}
				DoReadHeader();
			}
			else
			{
				m_receivedPacket.Clear();
				m_receivedPacket.SetPacketType(EPacketTypeSpecial_Disconnect);
				AddReceivedPacket(m_receivedPacket);
				m_receivedPacket.Clear();

				cout << "Error : " << ec << " Stop Client " << endl;

				boost::system::error_code ignored_ec;
				m_socket.close(ignored_ec);

				Clear();
			}
		});
	}

}

void NetClientEx::DoWrite()
{
	EnPacket& packet = m_sendPacketDeque.front().GetEnPacket();
#ifdef NET_DEBUG_INFO
	cout << "Post Send Packet Size : " << packet.GetLength() << endl;
#endif
	boost::asio::async_write(m_socket,
		boost::asio::buffer(packet.GetString(),
		packet.GetLength()),
		[this](boost::system::error_code ec, std::size_t length)
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
			m_receivedPacket.Clear();
			m_receivedPacket.SetPacketType(EPacketTypeSpecial_Disconnect);
			AddReceivedPacket(m_receivedPacket);
			m_receivedPacket.Clear();

			cout << "Error : " << ec << " Stop Client " << endl;

			boost::system::error_code ignored_ec;
			m_socket.close(ignored_ec);

			Clear();
		}
	});
}

void NetClientEx::Clear()
{
	m_receivedPacket.Clear();
	m_receivedBigPacket.Clear();
	m_sendPacketDeque.clear();

	m_bConnect = false;
}

void NetClientEx::AddReceivedPacket(ReceivedPacket& INpacket)
{
#ifdef ENCRYPT
	m_encryptRecv.Encrypt((char *)INpacket.GetPacketDef().packetData.data(), INpacket.GetPacketDef().packetLength);
#endif

	std::lock_guard<std::mutex> guard(m_receiveDequeMutex);

	m_receivedPacketDeque.push_back(std::move(INpacket));
}

void NetClientEx::GetReceivedPacketDeque(ReceivedPacketDeque& INpacketDeque)
{
	std::lock_guard<std::mutex> guard(m_receiveDequeMutex);
	INpacketDeque = std::move(m_receivedPacketDeque);
	m_receivedPacketDeque.clear();
}