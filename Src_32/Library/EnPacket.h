#ifndef LIBRARY_BASE_ENPACKET_H
#define LIBRARY_BASE_ENPACKET_H

#include "Type.h"

class EnPacket
{
private:
	/** ���������� **/
	string m_data;
	/** д��λ�� **/
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
	* @brief ѹ��һ������ֵ
	**/
	void PushBool(bool INvalue);

	/**
	* @brief ѹ��һ���ַ�ֵ
	**/
	void PushChar(char INvalue);

	/**
	* @brief ѹ��һ���޷����ַ�ֵ
	**/
	void PushUChar(unsigned char INvalue);

	/**
	* @brief ѹ��һ��������ֵ
	**/
	void PushShort(short INvalue);

	/**
	* @brief ѹ��һ���޷��Ŷ�����ֵ
	**/
	void PushUShort(unsigned short INvalue);

	/**
	* @brief ѹ��һ��λ����ֵ
	**/
	void PushInt(int INvalue);

	/**
	* @brief ѹ��һ���޷�������ֵ
	**/
	void PushUInt(unsigned int INvalue);

	/**
	* @brief ѹ��һ��������ֵ
	**/
	void PushLong(long INvalue);

	/**
	* @brief ѹ��һ���޷��ų�����ֵ
	**/
	void PushULong(unsigned long INvalue);

	/**
	* @brief ѹ��һ��64λ�з�������ֵ
	**/
#ifdef WIN32
	void PushInt64(__int64 INvalue);
#else
	void PushInt64(long long INvalue);
#endif
	/**
	* @brief ѹ��һ��64λ�޷�������ֵ
	**/
#ifdef WIN32
	void PushUInt64(unsigned __int64 INvalue);
#else
	void PushUInt64(unsigned long long INvalue);
#endif
	/**
	* @brief ѹ��һ�������ȸ���ֵ
	**/
	void PushFloat(float INvalue);

	/**
	* @brief ѹ��һ��˫���ȸ���ֵ
	**/
	void PushDouble(double INvalue);

	/**
	* @brief ѹ��һ���ַ���
	**/
	void PushString(const char* INdata, UInt32 INdataSize);

	/**
	* @brief ѹ��һ���ַ���
	**/
	void PushString(const string& INdata);

	/**
	* @brief ѹ��һ���ַ���,ѹ���ʽΪ��һ���ֶ���UInt16���ַ������ȣ��ڶ����ֶ�Ϊstring
	**/
	void PushUInt16String(const string& INdata);

	/**
	* @brief ��λ
	* @param INpos : λ��
	* @exception
	* @note INpos�������ݴ�С������Ϊ����β��
	**/
	void Seekg(UInt32 INpos);

	/**
	* @brief ��ȡ������
	**/
	const string& GetString()
	{
		return m_data;
	};

	/**
	* @brief ��ȡ������, ���޸�
	**/
	string& GetStringData()
	{
		return m_data;
	};

	/**
	* @brief ��ȡ����С
	**/
	inline UInt32 GetLength()
	{
		return static_cast<UInt32>(m_data.size());
	};

	/**
	* @brief ���������
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