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
	// ��ȡ���ݰ�
	PacketDef& GetPacketDef(){return m_packet;};

	// ������ͷ
	bool DecodeHeader();

	// �����ͷ
	void EncodeHeader();

	void MoveHeadData(ReceivedPacket& INright);

	// �������������
	void SetPacketType(UInt16 INpacketType){m_packetType = INpacketType;};

	// ��ȡ������Ϣ������
	UInt16 GetPacketType();

	// �������ӱ��
	void SetConnectionID(UInt32 INconnectionID){m_connectionID = INconnectionID;};

	// ��ȡ���ӱ��
	UInt32 GetConnectionID(){return m_connectionID;};

	// ����
	void Clear();

protected:
	// ����ID
	UInt32 m_connectionID;
	// ���ݰ�����
	UInt16 m_packetType;
	// �������С
	UInt32 m_maxBodyLength;
	// ��Ϣ������
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
	// ������Ϣ������
	void SetPacketType(UInt16 INpacketType){m_packetType = INpacketType;};

	// ��ȡ������
	UInt16 GetPacketType(){return m_packetType;};

	// ��ȡ��Ϣ���а�
	EnPacket& GetEnPacket(){return m_packetData;};

	// ��ȡ����С
	UInt32 GetPacketSize();

	// �������ݰ�
	void EnCodePacket();
private:
	UInt16 m_packetType;
	EnPacket m_packetData;
};

#endif