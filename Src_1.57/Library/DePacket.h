#ifndef LIBRARY_BASE_DEPACKET_H
#define LIBRARY_BASE_DEPACKET_H

#include "Type.h"

enum DePacketErrorCode
{
	EDePacketErrorCode_OutOfRange,
};

class ReceivedPacket;

class DePacket
{
private:
	/** 数据大小 **/
	UInt32 m_dataSize;
	/** 包数据 **/
	vector<char> m_data;
	/** 已读取大小 **/
	UInt32 m_unReadSize;
	/** 读取位置 **/
	char* m_readPos;
public:
	/**
	* @brief 构造函数
	**/
	DePacket();

	/**
	* @brief 析构函数
	**/
	~DePacket();

public:
	/**
	* @brief 初始化解包器
	**/
	bool InitialPacket(string& INdata);

	/**
	* @brief 初始化解包器
	**/
	bool InitialPacket(ReceivedPacket& INpacket);

	/**
	* @brief 初始化解包器
	**/
	bool InitialPacket(const char* INdata, UInt32 INdataSize);

	/**
	* @brief 读取一个布尔值
	**/
	bool GetBool();

	/**
	* @brief 读取一个有符号字符值
	**/
	char GetChar();

	/**
	* @brief 读取一个无符号字符值
	**/
	unsigned char GetUChar();

	/**
	* @brief 读取一个有符号短整型值
	**/
	short GetShort();

	/**
	* @brief 读取一个无符号短整型值
	**/
	unsigned short GetUShort();

	/**
	* @brief 读取一个有符号整型值
	**/
	int GetInt();

	/**
	* @brief 读取一个无符号整型值
	**/
	unsigned int GetUInt();

	/**
	* @brief 读取一个有符号长整型值
	**/
	long GetLong();

	/**
	* @brief 读取一个无符号长整型值
	**/
	unsigned long GetULong();

	/**
	* @brief 读取一个64位有符号整型值
	**/
#ifdef WIN32
	__int64 GetInt64();
#else
	long long GetInt64();
#endif
	/**
	* @brief 读取一个64位无符号整型值
	**/
#ifdef WIN32
	unsigned __int64 GetUInt64();
#else
	unsigned long long GetUInt64();
#endif
	/**
	* @brief 读取一个单精度浮点值值
	**/
	float GetFloat();

	/**
	* @brief 读取一个双精度浮点值值
	**/
	double GetDouble();

	/**
	* @brief 读取一个字符串值
	**/
	char* GetString(UInt32 INsize);

	/**
	* @brief 读取一个字符串值
	**/
	void GetString(string& OUTvalue, UInt32 INsize);

	/**
	* @brief 读取一个字符串值
	**/
	void GetUInt16String(string& OUTvalue);
};

#endif