#ifndef LIBRARY_NETCONNECTION_H
#define LIBRARY_NETCONNECTION_H

#include "Type.h"
#include "NetPacket.h"

class NetServer;

//#include <memory>
//using std::shared_ptr;
#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

#include <boost/asio.hpp>
#include <boost/aligned_storage.hpp>
#include <boost/system/error_code.hpp>
#include <boost/enable_shared_from_this.hpp>
using boost::enable_shared_from_this;

#include <mutex>


class NetConnection : public boost::enable_shared_from_this<NetConnection>
{
public:
	typedef deque<SendPacket> SendPacketDeque;
	typedef deque<ReceivedPacket> ReceivedPacketDeque;
	typedef boost::shared_ptr<boost::asio::ip::tcp::socket> SocketPtr;
public:
	NetConnection(NetServer& INnetServer, SocketPtr INpSocket, UInt32 INconnectionID);

	~NetConnection();

public:
	// �ͻ���IP
	const char* GetIP();
public:
	// �����������
	void Start();

	// ����
	void Update();

	// �ر���������
	void Stop();

	//�����Ͽ�����
	void Close();

	// ��ȡ������Ϣ����
	void GetReceivedPacketDeque(ReceivedPacketDeque& OUTpacketDeque);

	// ������Ϣ
	void Send(SendPacket& INsendPacket);
public:
	// ��ȡ����ȡ���������
	UInt32 GetReceivedPacketCount(){return m_receivePacketCount;}

	// ��ȡ����ID
	UInt32 GetConnectionID(){return m_connectionID;};

private:
	// �����ͷ��ȡ
	void DoReadPacketHead();

	// ��������ȡ
	void DoReadPacketBody();

	// ����������Ϣ
	void DoWrite();

	// ��ͷ��ȡ��ɴ���
	void OnReadPacketHeaderComplete(boost::system::error_code ec);

	// �����ȡ��ɴ���
	void OnReadPacketBodyComplete(boost::system::error_code ec);
private:
	// ���ӱ��
	UInt32 m_connectionID;
	// �׽���
	SocketPtr m_socket;
	// ���հ�
	ReceivedPacket m_receivePacket;
	// ���մ��
	ReceivedPacket m_receiveBigPacket;
	// ������Ϣ������
	ReceivedPacketDeque m_receivedPacketDeque;
	// ������Ϣ��������
	std::mutex m_receiveDequeMutex;
	// ���Ͱ�����
	SendPacketDeque m_sendPacketDeque;
	// ���Ͷ��л�����
	std::mutex m_sendDequeMutex;
	// ������
	NetServer& m_netServer;
	// ���ջ���
	// boost::aligned_storage<1024 * 4> m_receiveBuffer;
	// �������ݶ�ȡλ��
	UInt32 m_receivePacketCount;
	
};

typedef boost::shared_ptr<NetConnection> NetConnectionPtr;

#endif