#ifndef LIBRARY_NETCLIENT_H
#define LIBRARY_NETCLIENT_H

#include "Type.h"
#include "NetPacket.h"

#ifdef ASIO_STANDALONE
#include "asio.hpp"
using asio::ip::tcp;
using asio::io_service
using std::error_code;
#else
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
using boost::asio::ip::tcp;
using boost::asio::io_service;
using boost::system::error_code;
#endif

class NetServer;

#include <mutex>

enum NetClientStatus
{
	ENetClientStatus_UnConnected,
	ENetClientStatus_Connecting,
	ENetClientStatus_Connected,
};

class NetClient
{
public:
	typedef deque<SendPacket> SendPacketDeque;
	typedef deque<ReceivedPacket> ReceivedPacketDeque;
public:
	NetClient(NetServer& INnetServer,
		tcp::resolver::iterator INendPoint);

	~NetClient();

public:
	void Send(SendPacket& INsendPacket);

	void Close();

	bool IsSocketOpen() { return m_socket.is_open(); }

	UInt8 GetConnectStatus() { return m_connectStatus; }
	
	void ReConnect() { DoConnect(m_endPoint); }
private:
	void DoConnect(tcp::resolver::iterator endpoint_iterator);

	void DoReadHeader();

	void DoReadBody();

	void DoWrite();

	void Clear();
private:
	// 网络服务器
	NetServer& m_netServer;
	// 连接套接字
	tcp::socket m_socket;
	// 连接地址端口
	tcp::resolver::iterator m_endPoint; 
	// 接收包
	ReceivedPacket m_receivedPacket;
	// 接收大包
	ReceivedPacket m_receivedBigPacket;
	// 接收队列锁
	std::mutex m_receivedDequeMutex;
	// 发送队列
	SendPacketDeque m_sendPacketDeque;
	// 发送队列锁
	std::mutex m_sendDequeMutex;
	// 连接状态
	UInt8 m_connectStatus;
};

#endif