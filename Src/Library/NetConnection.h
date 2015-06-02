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
	// 客户端IP
	const char* GetIP();
public:
	// 开启网络接收
	void Start();

	// 更新
	void Update();

	// 关闭网络连接
	void Stop();

	//　仅断开连接
	void Close();

	// 获取已收消息队列
	void GetReceivedPacketDeque(ReceivedPacketDeque& OUTpacketDeque);

	// 发送消息
	void Send(SendPacket& INsendPacket);
public:
	// 获取已收取网络包数量
	UInt32 GetReceivedPacketCount(){return m_receivePacketCount;}

	// 获取连接ID
	UInt32 GetConnectionID(){return m_connectionID;};

private:
	// 网络包头读取
	void DoReadPacketHead();

	// 网络包体读取
	void DoReadPacketBody();

	// 发送网络消息
	void DoWrite();

	// 包头读取完成处理
	void OnReadPacketHeaderComplete(boost::system::error_code ec);

	// 包体读取完成处理
	void OnReadPacketBodyComplete(boost::system::error_code ec);
private:
	// 连接编号
	UInt32 m_connectionID;
	// 套接字
	SocketPtr m_socket;
	// 接收包
	ReceivedPacket m_receivePacket;
	// 接收大包
	ReceivedPacket m_receiveBigPacket;
	// 已收消息包队列
	ReceivedPacketDeque m_receivedPacketDeque;
	// 已收消息包互斥锁
	std::mutex m_receiveDequeMutex;
	// 发送包队列
	SendPacketDeque m_sendPacketDeque;
	// 发送队列互斥锁
	std::mutex m_sendDequeMutex;
	// 服务器
	NetServer& m_netServer;
	// 接收缓存
	// boost::aligned_storage<1024 * 4> m_receiveBuffer;
	// 接收数据读取位置
	UInt32 m_receivePacketCount;
	
};

typedef boost::shared_ptr<NetConnection> NetConnectionPtr;

#endif