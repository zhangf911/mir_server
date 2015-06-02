#include "NetServer.h"
#include "NetConnection.h"
#include <functional>
using std::bind;
using namespace std::placeholders;

NetServer::NetServer(IoService& INioService, UInt16 INport)
	:m_ioservice(INioService),
	m_acceptor(INioService.GetIOService()),
	m_serverState(false), m_connectionID(0), m_receiveDequeCount(0), m_receivePacketDequeMax(0)
{
	//, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), INport)
	boost::asio::ip::address addr;
	addr.from_string("0.0.0.0");
	boost::asio::ip::tcp::endpoint ep(addr, INport);
	m_acceptor.open(ep.protocol());
	
	m_acceptor.set_option(boost::asio::socket_base::reuse_address(true));
	m_acceptor.bind(ep);

	m_acceptor.set_option(boost::asio::socket_base::receive_buffer_size(640000));
	m_acceptor.set_option(boost::asio::socket_base::send_buffer_size(640000));

	m_acceptor.listen(1024);

	m_acceptor.set_option(boost::asio::ip::tcp::no_delay(true));
	m_acceptor.set_option(boost::asio::socket_base::keep_alive(true));
	m_acceptor.set_option(boost::asio::socket_base::enable_connection_aborted(true));
}

NetServer::~NetServer()
{
	Stop();
}

bool NetServer::Start()
{
	// ��ʼ�ȴ����ӣ��������� 
	SocketPtr psocket(new  boost::asio::ip::tcp::socket(m_ioservice.GetIOService())); 
	// �������¼�ֻ��error_code������������boost::bind��socket�󶨽�ȥ 
	m_acceptor.async_accept(*psocket, 
		bind(&NetServer::OnConnectComplete, this , psocket, _1));
	
	// 
	cout << "Ͷ���������, Port : " << m_acceptor.local_endpoint().port() << endl;
	m_serverState = true;

	return true;
}

void NetServer::Run()
{
	if(m_serverState)
	{
		// ����������������
		for(auto it = m_netClientMap.begin(); it != m_netClientMap.end(); ++it)
		{
			it->second->Update();
		}

		// ����Ͽ�����
		for(auto it = m_disconnectClientMap.begin(); it != m_disconnectClientMap.end(); ++it)
		{
			auto disconnectIt = m_netClientMap.find(it->second->GetConnectionID());
			if (disconnectIt != m_netClientMap.end())
			{
				m_netClientMap.erase(disconnectIt);
			}
		}

		// �������ӳɹ�

		cout << "Current NetClient Size : " << m_netClientMap.size() << endl;
	}
}

void NetServer::Stop()
{
	m_acceptor.close();
}

Int32 NetServer::Send(UInt32 INclientID, SendPacket& INpacket)
{
	Int32 errorCode = 0;
	//auto it = m_netClientMap.find(INclientID);
	//if (it != m_netClientMap.end())
	//{
	//	it->second->Send(INpacket);
	//}
	//SendPacket packet = std::move(INpacket);
	GetIoService().GetIOService().post(
		[this, INclientID, INpacket]()
	{
		SendPacket packet = std::move(INpacket);
		auto it = m_netClientMap.find(INclientID);
		if (it != m_netClientMap.end())
		{
			it->second->Send(packet);
		}
	});

	return errorCode;
}

Int32 NetServer::BoardCast(SendPacket& INpacket)
{
	Int32 errorCode = 0;
	GetIoService().GetIOService().post(
		[this, INpacket]()
	{
		SendPacket packet = std::move(INpacket);
		for(auto client : m_netClientMap)
		{
			SendPacket packettemp = packet;
			client.second->Send(packettemp);
		}
	});
	return errorCode;
}

void NetServer::Disconnect(UInt32 INclinetID)
{
	GetIoService().GetIOService().post(
		[this, INclinetID]()
	{
		auto it = m_netClientMap.find(INclinetID);
		if (it != m_netClientMap.end())
		{
			it->second->Close();
			m_netClientMap.erase(it);
		}
	});

}

void NetServer::StopClient(NetConnectionPtr INnetClientPtr)
{
	GetIoService().GetIOService().post(
		[this, INnetClientPtr]()
	{
		auto it = m_netClientMap.find(INnetClientPtr->GetConnectionID());
		if(it != m_netClientMap.end())
		{
			m_netClientMap.erase(it);
		}
	});
}

void NetServer::OnConnectComplete(boost::shared_ptr<boost::asio::ip::tcp::socket> INpSocket, boost::system::error_code INerrorCode)
{
	if(INerrorCode || !INpSocket) 
	{
		return ; 
	}
	// �����ȴ����� 
	Start();

	++m_connectionID;

	// ��ʾԶ��IP 
	boost::system::error_code ignored_ec;
	std::cout << "New Connection From IP : " << INpSocket->remote_endpoint(ignored_ec).address() 
		<< " ConnectionID : " << m_connectionID << std::endl;

	// ��ӵ����Ӽ�
	NetConnectionPtr pNetClient(new NetConnection(*this, INpSocket, m_connectionID));
	if(pNetClient)
	{
		m_netClientMap[m_connectionID] = pNetClient;
		//m_netClientSet.insert(pNetClient);

		pNetClient->Start();
	}
	
	cout << "Current NetClient Size : " << m_netClientMap.size() << endl;
}

void NetServer::AddReceivedPacket(ReceivedPacket& INpacket)
{
#ifdef ENCRYPT
	m_encryptRecv.Encrypt((char *)INpacket.GetPacketDef().packetData.data(), INpacket.GetPacketDef().packetLength);
#endif

	std::lock_guard<std::mutex> guard(m_receiveDequeMutex);

	if (m_receivePacketDequeMax > 0 && m_receivedPacketDeque.size() >= m_receivePacketDequeMax)
	{
		cout << "ReceivePacket size :" << m_receivedPacketDeque.size() << endl;
		//return;  // ��ʱֻ�������ʾ�������߼����� 
	}

	m_receivedPacketDeque.push_back(std::move(INpacket));
}

UInt32 NetServer::GetReceivedPacketDeque(ReceivedPacketDeque& INpacketDeque)
{
	std::lock_guard<std::mutex> guard(m_receiveDequeMutex);

	if (m_receiveDequeCount == 0 || m_receivedPacketDeque.size() <= m_receiveDequeCount)
	{
		INpacketDeque = std::move(m_receivedPacketDeque);
		m_receivedPacketDeque.clear();

		return 0;
	}
	else
	{
		for (auto it = m_receivedPacketDeque.begin(); it != m_receivedPacketDeque.begin() + m_receiveDequeCount; ++it)
		{
			INpacketDeque.push_back(std::move(*it));
		}
		//INpacketDeque.assign();
		m_receivedPacketDeque.erase(m_receivedPacketDeque.begin(), m_receivedPacketDeque.begin() + m_receiveDequeCount);

		return m_receivedPacketDeque.size();
	}

	return 0;
}