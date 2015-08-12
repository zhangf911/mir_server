#include "NetPacket.h"

ReceivedPacket::ReceivedPacket(UInt32 INmaxBodyLength)
	: m_connectionID(0), m_packetType(0), m_maxBodyLength(INmaxBodyLength)
{
	Clear();
}

ReceivedPacket::ReceivedPacket(const ReceivedPacket& INright)
{
	m_connectionID = INright.m_connectionID;
	m_packetType = INright.m_packetType;
	m_packet.packetLength = INright.m_packet.packetLength;
	m_packet.packetData = INright.m_packet.packetData;
	m_maxBodyLength = INright.m_maxBodyLength;
}

ReceivedPacket::~ReceivedPacket()
{
	Clear();
}

ReceivedPacket::ReceivedPacket(ReceivedPacket&& INright)
{
	m_connectionID = std::move(INright.m_connectionID);
	m_packetType = std::move(INright.m_packetType);
	m_packet.packetLength = std::move(INright.m_packet.packetLength);
	m_packet.packetData = std::move(INright.m_packet.packetData);
	m_maxBodyLength = INright.m_maxBodyLength;

	INright.m_connectionID = 0;
	INright.m_packetType = 0;
	INright.m_packet.packetLength = 0;
}

ReceivedPacket& ReceivedPacket::operator=(ReceivedPacket&& INright)
{
	m_connectionID = std::move(INright.m_connectionID);
	m_packetType = std::move(INright.m_packetType);
	m_packet.packetLength = std::move(INright.m_packet.packetLength);
	m_packet.packetData = std::move(INright.m_packet.packetData);
	m_maxBodyLength = INright.m_maxBodyLength;

	INright.m_connectionID = 0;
	INright.m_packetType = 0;
	INright.m_packet.packetLength = 0;
	return *this;
}

bool ReceivedPacket::DecodeHeader()
{
	char header[EPacketHeaderLength + 1] = "";
	std::memcpy(header, (char *)m_packet.packetData.data(), EPacketHeaderLength);
	m_packet.packetLength = *(int*)header;//std::atoi(header);
	if (m_packet.packetLength > EPacket_Big_MaxBodyLength)
	{
		cout << "Wrong Packet Header Length : " << m_packet.packetLength << endl;
		m_packet.packetLength = 0;
		return false;
	}
	return true;
}

void ReceivedPacket::EncodeHeader()
{
	char header[EPacketHeaderLength + 1] = "";
	std::sprintf(header, "%4d", EPacketHeaderLength);
	std::memcpy(m_packet.packetData.data(), header, EPacketHeaderLength);
}

void ReceivedPacket::MoveHeadData(ReceivedPacket& INright)
{
	std::memcpy(INright.m_packet.packetData.data(), m_packet.packetData.data(), EPacketHeaderLength);
}

UInt16 ReceivedPacket::GetPacketType()
{
	if(m_packetType != 0)
	{
		return m_packetType;
	}

	if(m_packet.packetData.size() < sizeof(UInt16))
	{
		return 0;
	}

	UInt16 type = *(UInt16*)m_packet.packetData.data();
	return type;
}

void ReceivedPacket::Clear()
{
	m_connectionID = 0;
	m_packetType = 0;
	m_packet.packetLength = 0;
	m_packet.packetData.clear();
	m_packet.packetData.resize(m_maxBodyLength);
}

SendPacket::SendPacket(const SendPacket& INinstance)
{
	m_packetType = INinstance.m_packetType;
	m_packetData = INinstance.m_packetData;
}

SendPacket& SendPacket::operator=(const SendPacket& INinstance)
{
	m_packetType = INinstance.m_packetType;
	m_packetData = INinstance.m_packetData;
	return *this;
}

SendPacket::SendPacket(SendPacket&& INright)
{
	m_packetType = std::move(INright.m_packetType);
	m_packetData = std::move(INright.m_packetData);
}

SendPacket& SendPacket::operator=(SendPacket&& INright)
{
	m_packetType = std::move(INright.m_packetType);
	m_packetData = std::move(INright.m_packetData);

	return *this;
}

void SendPacket::EnCodePacket()
{
	UInt32 packetSize = sizeof(UInt16) + m_packetData.GetLength();

	EnPacket packet;
	packet.PushUInt(packetSize);
	packet.PushUShort(m_packetType);
	packet.PushString(m_packetData.GetString().c_str(), m_packetData.GetLength());

	m_packetData = std::move(packet);
}

UInt32 SendPacket::GetPacketSize()
{
	return m_packetData.GetLength();
}