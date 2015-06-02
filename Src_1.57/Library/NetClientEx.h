#ifndef LIBRARY_NETCLIENT_H
#define LIBRARY_NETCLIENT_H

#include "Type.h"
#include "NetPacket.h"
#include "IoService.h"


#ifdef ASIO_STANDALONE
#include "asio.hpp"
using asio::ip::tcp;
//using asio::io_service;
using std::error_code;
#else
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
using boost::asio::ip::tcp;
//using boost::asio::io_service;
using boost::system::error_code;
#endif

#include <mutex>

class NetClientEx
{
public:
	typedef deque<SendPacket> SendPacketDeque;
	typedef deque<ReceivedPacket> ReceivedPacketDeque;
public:
	NetClientEx(IoService& INIoService);

	~NetClientEx();

public:
	void SetResolver(boost::asio::ip::tcp::resolver::iterator INendPoint) { m_endPoint = INendPoint; }

	void Send(SendPacket& INsendPacket);

	void Close();

	bool IsSocketOpen() { return m_socket.is_open(); }

	bool IsConnect() { return m_bConnect; }
	
	void ReConnect() { DoConnect(m_endPoint); }

	void GetReceivedPacketDeque(ReceivedPacketDeque& INpacketDeque);

public:
	IoService& GetIoService(){ return m_ioService; };

private:
	void DoConnect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

	void DoReadHeader();

	void DoReadBody();

	void DoWrite();

	void Clear();

	void AddReceivedPacket(ReceivedPacket& INpacket);
private:
	IoService& m_ioService;
	// �����׽���
	tcp::socket m_socket;
	// ���ӵ�ַ�˿�
	boost::asio::ip::tcp::resolver::iterator m_endPoint;
	// ���հ�
	ReceivedPacket m_receivedPacket;
	// ���մ��
	ReceivedPacket m_receivedBigPacket;
	// ���ն�����
	std::mutex m_receivedDequeMutex;
	// ���Ͷ���
	SendPacketDeque m_sendPacketDeque;
	// ���Ͷ�����
	std::mutex m_sendDequeMutex;
	// ������հ�
	ReceivedPacketDeque m_receivedPacketDeque;
	// ������Ϣ��������
	std::mutex m_receiveDequeMutex;
	// ��ǰ�Ƿ�����
	bool m_bConnect;
};

#endif