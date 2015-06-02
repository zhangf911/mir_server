#ifndef LIBRARY_NETPACKET_H
#define LIBRARY_NETPACKET_H

#include "Type.h"
#include "EnPacket.h"

enum PacketCommDef
{
	EPacketHeaderLength = 4,
	EPacket_Small_MaxBodyLength = 128,
	EPacket_Big_MaxBodyLength = 8192,//4096,
};

enum PacketTypeSpecial
{
	EPacketTypeSpecial_Connect,
	EPacketTypeSpecial_Common,
	EPacketTypeSpecial_Disconnect,
};

struct PacketDef
{
	UInt32 packetLength;
	vector<char> packetData;
};

class ReceivedPacket
{
public:
	ReceivedPacket(UInt32 INmaxBodyLength);

	ReceivedPacket(const ReceivedPacket& INright);

	~ReceivedPacket();

	ReceivedPacket(ReceivedPacket&& INright);

	ReceivedPacket& operator=(ReceivedPacket&& INright);
public:
	// 获取数据包
	PacketDef& GetPacketDef(){return m_packet;};

	// 解析包头
	bool DecodeHeader();

	// 编码包头
	void EncodeHeader();

	void MoveHeadData(ReceivedPacket& INright);

	// 设置网络包类型
	void SetPacketType(UInt16 INpacketType){m_packetType = INpacketType;};

	// 获取网络消息报类型
	UInt16 GetPacketType();

	// 设置连接编号
	void SetConnectionID(UInt32 INconnectionID){m_connectionID = INconnectionID;};

	// 获取连接编号
	UInt32 GetConnectionID(){return m_connectionID;};

	// 清理
	void Clear();

protected:
	// 连接ID
	UInt32 m_connectionID;
	// 数据包类型
	UInt16 m_packetType;
	// 最大包体大小
	UInt32 m_maxBodyLength;
	// 消息包数据
	PacketDef m_packet;
};

class SendPacket
{
public:
	SendPacket(){m_packetType = 0;};

	SendPacket(const SendPacket& INinstance);

	SendPacket& operator=(const SendPacket& INinstance);

	SendPacket(SendPacket&& INright);

	SendPacket& operator= (SendPacket&& INright);

	~SendPacket(){m_packetType = 0;};

public:
	// 设置消息包类型
	void SetPacketType(UInt16 INpacketType){m_packetType = INpacketType;};

	// 获取包类型
	UInt16 GetPacketType(){return m_packetType;};

	// 获取消息序列包
	EnPacket& GetEnPacket(){return m_packetData;};

	// 获取包大小
	UInt32 GetPacketSize();

	// 编码数据包
	void EnCodePacket();
private:
	UInt16 m_packetType;
	EnPacket m_packetData;
};

#endif