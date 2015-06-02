#ifndef LIBRARY_UTIL_UTIL_H
#define LIBRARY_UTIL_UTIL_H

#include "Type.h"

enum TimeVariables
{
	ETime_Second = 1,
	ETime_Minute = ETime_Second * 60,
	ETime_Hour   = ETime_Minute * 60,
	ETime_Day	= ETime_Hour * 24,
	ETime_Month	= ETime_Day * 30,
	ETime_Year	= ETime_Month * 12
};

enum MsTimeVariables
{
	EMsTime_Second = 1000,
	EMsTime_6Seconds = EMsTime_Second * 6,
	EMsTime_Minute = EMsTime_Second * 60,
	EMsTime_Hour   = EMsTime_Minute * 60,
	EMsTime_Day	  = EMsTime_Hour * 24
};

namespace Library
{
	/**
	* @brief ȡ�����ȸ���ֵ���������
	* @param INfloatValue : �����ȸ���ֵ
	* @return �����ȸ���ֵ���������
	* @exception 
	* @note 
	*/
	float Round(float INfloatValue);

	/**
	* @brief ȡ˫���ȸ���ֵ���������
	* @param INdoubleValue : ˫���ȸ���ֵ
	* @return ˫���ȸ���ֵ���������
	* @exception 
	* @note 
	*/
	double Round(double INdoubleValue);

	/**
	* @brief ȡ��˫���ȸ���ֵ���������
	* @param INlongDouble : ��˫���ȸ���ֵ
	* @return ��˫���ȸ���ֵ���������
	* @exception 
	* @note 
	*/
	long double Round(long double INlongDoubleValue);

	/**
	* @brief ˯��
	* @param INtimems : ������
	* @exception 
	* @note 
	*/
	void Sleep(unsigned long INtimems);

	/**
	* @brief ��ȡ���ŵĺ�����
	* @return ���ŵĺ�����
	* @exception 
	* @note 
	*/
	UInt32 GetMSTime();
}


#endif