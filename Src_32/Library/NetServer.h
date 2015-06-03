#ifndef LIBRARY_NETSERVER_H
#define LIBRARY_NETSERVER_H

#include "Type.h"
#include "IoService.h"
#include "NetPacket.h"

#include <mutex>
#include <atomic>

#ifdef ENCRYPT
	#include "EncryptServer.h"

	#define LOGIN_KEY1				0xa61fce5e	
	#define LOGIN_KEY2				0x443ffc04	
	typedef	EncryptServer<LOGIN_KEY1, LOGIN_KEY2>	ENCRYPTSERVER;
#endif

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
using boost::system::error_code;

class NetConnection;
typedef boost::shared_ptr<NetConnection> NetConnectionPtr;

class NetServer
{
public:
	typedef deque<SendPacket> SendPacketDeque;
	typedef deque<ReceivedPacket> ReceivedPacketDeque;
	typedef set<NetConnectionPtr> NetClientSet;
	typedef map<UInt32, NetConnectionPtr> NetClientMap;
	typedef boost::shared_ptr<boost::asio::ip::tcp::socket> SocketPtr;
public:
	NetServer(IoService& INioService, UInt16 INport);

	~NetServer();

public:
	// �����������
	bool Start();

	// ������������
	void Run();

	// ֹͣ�������
	void Stop();

	// ������Ϣ���ͻ���
	//Int32 Send(UInt32 INclientID, const char* INpData, UInt32 INdataSize);

	// ������Ϣ���ͻ���
	Int32 Send(UInt32 INclientID, SendPacket& INpacket);

	// �鲥����
	Int32 BoardCast(SendPacket& INpacket);

	// �˿���ͻ��˵�����
	void Disconnect(UInt32 INclinetID);

	// �˿�����
	void StopClient(NetConnectionPtr INnetClientPtr);

	// ������ɴ���
	void OnConnectComplete(boost::shared_ptr<boost::asio::ip::tcp::socket> INpSocket, boost::system::error_code INerrorCode);

	// ��ӽ��հ�
	void AddReceivedPacket(ReceivedPacket& INpacket);

	// ��ȡ��Ϣ������
	UInt32 GetReceivedPacketDeque(ReceivedPacketDeque& INpacketDeque);

	// ����һ�λ�ȡ���ܰ������������0��ʾȫ��
	void SetReceiveDequeCount(UInt32 INCount) { m_receiveDequeCount = INCount; }

	// ����������ܰ������������ 0��ʾ������
	void SetReceiveDequeMax(UInt32 INMax) { m_receivePacketDequeMax = INMax; }

public:
	IoService& GetIoService(){return m_ioservice;};

private:
	// IO����
	IoService& m_ioservice;
	// �ͻ������Ӽ���
	//NetClientSet m_netClientSet;
	NetClientMap m_netClientMap;
	// �ȴ�����Ͽ����ӱ�
	NetClientMap m_disconnectClientMap;
	// �ȴ�����Ͽ����ӱ�����
	std::mutex m_disconnectMutex;
	// ���ӽ�����
	boost::asio::ip::tcp::acceptor m_acceptor;
	// ���������״̬
	bool m_serverState;
	// ������հ�
	ReceivedPacketDeque m_receivedPacketDeque;
	// ������Ϣ��������
	std::mutex m_receiveDequeMutex;
	// ���Ͱ�����
	SendPacketDeque m_sendPacketDeque;
	// ���Ͷ��л�����
	std::mutex m_sendDequeMutex;
	// 
	UInt32 m_connectionID;
	// һ�λ�ȡ���ܰ������������0��ʾȫ��
	UInt32 m_receiveDequeCount;
	// ������ܰ������������ 0��ʾ������
	UInt32 m_receivePacketDequeMax;

#ifdef ENCRYPT
	// �ӽ���
	ENCRYPTSERVER	m_encryptRecv;
#endif

};


#endif