#include "DePacket.h"
#include "NetPacket.h"

DePacket::DePacket()
{
	//m_data = NULL;
	m_data.clear();
}

DePacket::~DePacket()
{
	//delete[] m_data;
	m_data.clear();
}

bool DePacket::InitialPacket(ReceivedPacket& INpacket)
{
	m_data = std::move(INpacket.GetPacketDef().packetData);

	m_dataSize = INpacket.GetPacketDef().packetLength - sizeof(unsigned short);
	m_readPos = m_data.data() + sizeof(unsigned short);
	m_unReadSize = m_dataSize;

	return true;
}

bool DePacket::InitialPacket(string& INdata)
{
	return InitialPacket(INdata.c_str(), static_cast<UInt32>(INdata.size()));
}

bool DePacket::InitialPacket(const char* INdata, UInt32 INdataSize)
{
	try
	{
		//m_data = new char[INdataSize + 1];
	}
	catch(...)
	{
		//Log::Instance()->WriteException("%s, %d, Allocate Memory Failed!",
		//	__FUNCTION__, __LINE__);
		return false;
	}

	//m_data.resize(INdataSize + 1);

	m_data.assign(INdata, INdata + INdataSize);
	//memcpy(m_data, INdata, INdataSize);
	//m_data[INdataSize] = '\0';
	m_dataSize = INdataSize;
	m_readPos = m_data.data();
	m_unReadSize = INdataSize;

	return true;
}

bool DePacket::GetBool()
{
	if(sizeof(bool) > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}
	bool value = *m_readPos > 0 ? true : false;
	m_unReadSize -= sizeof(bool);
	m_readPos += sizeof(bool);
	return value;
}

char DePacket::GetChar()
{
	if(sizeof(char) > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}
	char value = *m_readPos;
	m_unReadSize -= sizeof(char);
	m_readPos += sizeof(char);
	return value;
}

unsigned char DePacket::GetUChar()
{
	if(sizeof(unsigned char) > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}

	unsigned char value = *(unsigned char*)m_readPos;
	m_unReadSize -= sizeof(unsigned char);
	m_readPos += sizeof(unsigned char);
	return value;
}

short DePacket::GetShort()
{
	if(sizeof(short) > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}

	short value = *(short*)m_readPos;
	m_unReadSize -= sizeof(short);
	m_readPos += sizeof(short);
	return value;
}

unsigned short DePacket::GetUShort()
{
	if(sizeof(unsigned short) > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}

	unsigned short value = *(unsigned short*)m_readPos;
	m_unReadSize -= sizeof(unsigned short);
	m_readPos += sizeof(unsigned short);
	return value;
}

int DePacket::GetInt()
{
	if(sizeof(int) > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}

	int value = *(int*)m_readPos;
	m_unReadSize -= sizeof(int);
	m_readPos += sizeof(int);
	return value;
}

unsigned int DePacket::GetUInt()
{
	if(sizeof(unsigned int) > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}

	unsigned int value = *(unsigned int*)m_readPos;
	m_unReadSize -= sizeof(unsigned int);
	m_readPos += sizeof(unsigned int);
	return value;
}

long DePacket::GetLong()
{
	if(sizeof(long) > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}

	long value = *(long*)m_readPos;
	m_unReadSize -= sizeof(long);
	m_readPos += sizeof(long);
	return value;
}

unsigned long DePacket::GetULong()
{
	if(sizeof(unsigned long) > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}

	unsigned long value = *(unsigned long*)m_readPos;
	m_unReadSize -= sizeof(unsigned long);
	m_readPos += sizeof(unsigned long);
	return value;
}

#ifdef WIN32
__int64 DePacket::GetInt64()
{
	if(sizeof(__int64) > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}

	__int64 value = *(__int64*)m_readPos;
	m_unReadSize -= sizeof(__int64);
	m_readPos += sizeof(__int64);
	return value;
}
#else
long long DePacket::GetInt64()
{
	if(sizeof(long long) > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}

	long long value = *(long long*)m_readPos;
	m_unReadSize -= sizeof(long long);
	m_readPos += sizeof(long long);
	return value;
}
#endif

#ifdef WIN32
unsigned __int64 DePacket::GetUInt64()
{
	if(sizeof(unsigned __int64) > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}

	unsigned __int64 value = *(unsigned __int64*)m_readPos;
	m_unReadSize -= sizeof(unsigned __int64);
	m_readPos += sizeof(unsigned __int64);
	return value;
}
#else
unsigned long long DePacket::GetUInt64()
{
	if(sizeof(unsigned long long) > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}

	unsigned long long value = *(unsigned long long*)m_readPos;
	m_unReadSize -= sizeof(unsigned long long);
	m_readPos += sizeof(unsigned long long);
	return value;
}
#endif

float DePacket::GetFloat()
{
	if(sizeof(float) > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}

	float value = *(float*)m_readPos;
	m_unReadSize -= sizeof(float);
	m_readPos += sizeof(float);
	return value;
}

double DePacket::GetDouble()
{
	if(sizeof(double) > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}

	double value = *(double*)m_readPos;
	m_unReadSize -= sizeof(double);
	m_readPos += sizeof(double);
	return value;
}

char* DePacket::GetString(UInt32 INsize)
{
	if(INsize > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}

	char* value = m_readPos;
	m_unReadSize -= INsize;
	m_readPos += INsize;
	return value;
}

void DePacket::GetString(string& OUTvalue, UInt32 INsize)
{
	if(INsize > m_unReadSize)
	{
		throw EDePacketErrorCode_OutOfRange;
	}

	OUTvalue = string(m_readPos, INsize);
	m_unReadSize -= INsize;
	m_readPos += INsize;
}

void DePacket::GetUInt16String(string& OUTvalue)
{
	unsigned int length = GetUShort();
	GetString(OUTvalue, length);
}