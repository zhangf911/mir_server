#include "EnPacket.h"

EnPacket::EnPacket()
{
	m_data.clear();
	m_pos = 0;
}

EnPacket::EnPacket(const EnPacket& INinstance)
{
	m_data = INinstance.m_data;
	m_pos = INinstance.m_pos;
}

EnPacket::EnPacket(EnPacket&& INright)
{
	m_data = std::move(INright.m_data);
	m_pos = std::move(INright.m_pos);
}

EnPacket::~EnPacket()
{
	m_data.clear();
	m_pos = 0;
}

EnPacket& EnPacket::operator= (const EnPacket& INinstance)
{
	m_data = INinstance.m_data;
	m_pos = INinstance.m_pos;
	return *this;
}

EnPacket& EnPacket::operator= (EnPacket&& INright)
{
	m_data = std::move(INright.m_data);
	m_pos = std::move(INright.m_pos);

	return *this;
}

void EnPacket::PushBool(bool INvalue)
{
	PushData(&INvalue);
}

void EnPacket::PushChar(char INvalue)
{
	PushData(&INvalue);
}

void EnPacket::PushUChar(unsigned char INvalue)
{
	PushData(&INvalue);
}

void EnPacket::PushShort(short INvalue)
{
	PushData(&INvalue);
}

void EnPacket::PushUShort(unsigned short INvalue)
{
	PushData(&INvalue);
}

void EnPacket::PushInt(int INvalue)
{
	PushData(&INvalue);
}

void EnPacket::PushUInt(unsigned int INvalue)
{
	PushData(&INvalue);
}

void EnPacket::PushLong(long INvalue)
{
	PushData(&INvalue);
}

void EnPacket::PushULong(unsigned long INvalue)
{
	PushData(&INvalue);
}

#ifdef WIN32
void EnPacket::PushInt64(__int64 INvalue)
{
	PushData(&INvalue);
}
#else
void EnPacket::PushInt64(long long INvalue)
{
	PushData(&INvalue);
} 
#endif

void EnPacket::PushFloat(float INvalue)
{
	PushData(&INvalue);
}

void EnPacket::PushDouble(double INvalue)
{
	PushData(&INvalue);
}

#ifdef WIN32
void EnPacket::PushUInt64(unsigned __int64 INvalue)
{
	PushData(&INvalue);
}
#else
void EnPacket::PushUInt64(unsigned long long INvalue)
{
	PushData(&INvalue);
}
#endif
void EnPacket::PushString(const string& INdata)
{
	PushString(INdata.c_str(), static_cast<UInt32>(INdata.size()));
}

void EnPacket::PushUInt16String(const string& INdata)
{
	PushUShort(static_cast<unsigned short>(INdata.size()));
	PushString(INdata);
}

void EnPacket::PushString(const char* INdata, UInt32 INdataSize)
{
	PushData(INdata, INdataSize);
}

void EnPacket::Seekg(UInt32 INpos)
{
	m_pos = static_cast<UInt32>(INpos > m_data.size() ? m_data.size() : INpos);
}	

template <typename DataType>
void EnPacket::PushData(DataType* INdata, UInt32 INdataSize /* = sizeof */)
{
	if(m_pos == m_data.size())
	{
		m_data.append((char*)INdata, INdataSize);
		m_pos = static_cast<UInt32>(m_data.size());
	}
	else
	{
		m_data.insert(m_pos, (char*)INdata, INdataSize);
	}
}
