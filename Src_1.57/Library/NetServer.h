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
	// 启动网络服务
	bool Start();

	// 运行网络心跳
	void Run();

	// 停止网络服务
	void Stop();

	// 发送消息到客户端
	//Int32 Send(UInt32 INclientID, const char* INpData, UInt32 INdataSize);

	// 发送消息到客户端
	Int32 Send(UInt32 INclientID, SendPacket& INpacket);

	// 组播发送
	Int32 BoardCast(SendPacket& INpacket);

	// 端口与客户端的链接
	void Disconnect(UInt32 INclinetID);

	// 端口连接
	void StopClient(NetConnectionPtr INnetClientPtr);

	// 链接完成处理
	void OnConnectComplete(boost::shared_ptr<boost::asio::ip::tcp::socket> INpSocket, boost::system::error_code INerrorCode);

	// 添加接收包
	void AddReceivedPacket(ReceivedPacket& INpacket);

	// 获取消息包队列
	UInt32 GetReceivedPacketDeque(ReceivedPacketDeque& INpacketDeque);

	// 设置一次获取接受包的最大条数，0表示全部
	void SetReceiveDequeCount(UInt32 INCount) { m_receiveDequeCount = INCount; }

	// 设置网络接受包的最大条数， 0表示不限制
	void SetReceiveDequeMax(UInt32 INMax) { m_receivePacketDequeMax = INMax; }

public:
	IoService& GetIoService(){return m_ioservice;};

private:
	// IO服务
	IoService& m_ioservice;
	// 客户端链接集合
	//NetClientSet m_netClientSet;
	NetClientMap m_netClientMap;
	// 等待处理断开连接表
	NetClientMap m_disconnectClientMap;
	// 等待处理断开连接表互斥锁
	std::mutex m_disconnectMutex;
	// 链接接收器
	boost::asio::ip::tcp::acceptor m_acceptor;
	// 网络服务器状态
	bool m_serverState;
	// 网络接收包
	ReceivedPacketDeque m_receivedPacketDeque;
	// 已收消息包互斥锁
	std::mutex m_receiveDequeMutex;
	// 发送包队列
	SendPacketDeque m_sendPacketDeque;
	// 发送队列互斥锁
	std::mutex m_sendDequeMutex;
	// 
	UInt32 m_connectionID;
	// 一次获取接受包的最大条数，0表示全部
	UInt32 m_receiveDequeCount;
	// 网络接受包的最大条数， 0表示不限制
	UInt32 m_receivePacketDequeMax;

#ifdef ENCRYPT
	// 加解密
	ENCRYPTSERVER	m_encryptRecv;
#endif

};


#endif