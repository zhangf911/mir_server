#ifndef LIBRARY_BASE_ENPACKET_H
#define LIBRARY_BASE_ENPACKET_H

#include "Type.h"

class EnPacket
{
private:
	/** 二进制数据 **/
	string m_data;
	/** 写入位置 **/
	UInt32 m_pos;
public:
	EnPacket();

	EnPacket(const EnPacket& INinstance);

	EnPacket(EnPacket&& INright);

	~EnPacket();

public:
	EnPacket& operator = (const EnPacket& INinstance);

	EnPacket& operator = (EnPacket&& INright);

public:
	/**
	* @brief 压入一个布尔值
	**/
	void PushBool(bool INvalue);

	/**
	* @brief 压入一个字符值
	**/
	void PushChar(char INvalue);

	/**
	* @brief 压入一个无符号字符值
	**/
	void PushUChar(unsigned char INvalue);

	/**
	* @brief 压入一个短整型值
	**/
	void PushShort(short INvalue);

	/**
	* @brief 压入一个无符号短整型值
	**/
	void PushUShort(unsigned short INvalue);

	/**
	* @brief 压入一个位整型值
	**/
	void PushInt(int INvalue);

	/**
	* @brief 压入一个无符号整型值
	**/
	void PushUInt(unsigned int INvalue);

	/**
	* @brief 压入一个长整型值
	**/
	void PushLong(long INvalue);

	/**
	* @brief 压入一个无符号长整型值
	**/
	void PushULong(unsigned long INvalue);

	/**
	* @brief 压入一个64位有符号整型值
	**/
#ifdef WIN32
	void PushInt64(__int64 INvalue);
#else
	void PushInt64(long long INvalue);
#endif
	/**
	* @brief 压入一个64位无符号整型值
	**/
#ifdef WIN32
	void PushUInt64(unsigned __int64 INvalue);
#else
	void PushUInt64(unsigned long long INvalue);
#endif
	/**
	* @brief 压入一个单精度浮点值
	**/
	void PushFloat(float INvalue);

	/**
	* @brief 压入一个双精度浮点值
	**/
	void PushDouble(double INvalue);

	/**
	* @brief 压入一个字符串
	**/
	void PushString(const char* INdata, UInt32 INdataSize);

	/**
	* @brief 压入一个字符串
	**/
	void PushString(const string& INdata);

	/**
	* @brief 压入一个字符串,压入格式为第一个字段是UInt16的字符串长度，第二个字段为string
	**/
	void PushUInt16String(const string& INdata);

	/**
	* @brief 定位
	* @param INpos : 位置
	* @exception
	* @note INpos超过数据大小，则处理为数据尾端
	**/
	void Seekg(UInt32 INpos);

	/**
	* @brief 获取包数据
	**/
	const string& GetString()
	{
		return m_data;
	};

	/**
	* @brief 获取包数据, 可修改
	**/
	string& GetStringData()
	{
		return m_data;
	};

	/**
	* @brief 获取包大小
	**/
	inline UInt32 GetLength()
	{
		return static_cast<UInt32>(m_data.size());
	};

	/**
	* @brief 清理包数据
	**/
	void Clear()
	{
		m_data.clear();
		m_pos = 0;
	};

private:
	template <typename DataType>
	void PushData(DataType* INdata, UInt32 INdataSize = sizeof(DataType));
};

#endif