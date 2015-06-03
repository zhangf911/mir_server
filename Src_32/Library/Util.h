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
	* @brief 取单精度浮点值的最大整数
	* @param INfloatValue : 单精度浮点值
	* @return 单精度浮点值的最大整数
	* @exception 
	* @note 
	*/
	float Round(float INfloatValue);

	/**
	* @brief 取双精度浮点值的最大整数
	* @param INdoubleValue : 双精度浮点值
	* @return 双精度浮点值的最大整数
	* @exception 
	* @note 
	*/
	double Round(double INdoubleValue);

	/**
	* @brief 取长双精度浮点值的最大整数
	* @param INlongDouble : 长双精度浮点值
	* @return 长双精度浮点值的最大整数
	* @exception 
	* @note 
	*/
	long double Round(long double INlongDoubleValue);

	/**
	* @brief 睡眠
	* @param INtimems : 毫秒数
	* @exception 
	* @note 
	*/
	void Sleep(unsigned long INtimems);

	/**
	* @brief 获取已逝的毫秒数
	* @return 已逝的毫秒数
	* @exception 
	* @note 
	*/
	UInt32 GetMSTime();
}


#endif