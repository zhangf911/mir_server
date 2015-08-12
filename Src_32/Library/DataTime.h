#ifndef LIBRARY_UTIL_DATATIME_H
#define LIBRARY_UTIL_DATATIME_H

#include "Type.h"

namespace Library
{
	/**
	* @class DataTime
	* @note 非线程安全，不能保证多线程下数据正确性
	**/
	class DataTimeHelper
	{
	public:
		/**
		* @brief 获取当日凌晨时间
		**/
		static time_t GetCurDayZeroTime();

		/**
		* @brief 获取当日凌晨时间
		**/
		static time_t GetCurDayLocalZeroTime();

		/**
		* @brief 获取当日凌晨时间
		**/
		static time_t GetCurDayUTCZeroTime();

		// 获取指定日期的凌晨时间戳
		static time_t GetDayZeroTime(time_t INtime);

		// 获取当前时间字符串
		static string GetCurTimeString();

		/**
		* @brief 将整型时间转换为字符串形式
		* @note  格式为 xxxx-xx-xx xx:xx:xx
		**/
		static string ToString(time_t INtime);

		/**
		* @brief 将字符串形式的时间转换为整型值
		* @note  字符串格式 xxxx-xx-xx xx:xx:xx
		**/
		static time_t ToInt(const string& INdataTimeString);

		// 获取当前时间往后一段时间字符串
		static string GetTimeStringAfter(time_t INtime);

		// 获取当前时间往后一段时间字符串
		static string GetTimeStringAfter(const string& INtime);

		// 获取指定时间段往后一段时间字符串
		static string GetTimeStringAfter(time_t INstartTime, time_t INsecond);

		// 获取指定时间段往后一段时间字符串
		static string GetTimeStringAfter(const string& INstartTime, time_t INsecond);

		// 是否同一天
		static bool IsSameDay(const string& INtime1, const string INtime2);

		// 是否同一天
		static bool IsSameDay(time_t INtime1, time_t INtime2);

		// 是否time1比time2晚
		static bool IsLater(const string& INtime1, const string INtime2);

		// 是否time1比time2晚
		static bool IsLater(time_t INtime1, time_t INtim2);

		// 时间差(单位秒)
		static time_t DiffSecond(const string INtime1, const string INtime2);

		// 时间差(单位秒)
		static time_t DiffSecond(time_t INtime1, time_t INtime2);

		// 日期差(单位天)
		static Int32 DiffDay(const string INtime1, const string INtime2);

		// 日期差(单位天)
		static Int32 DiffDay(time_t INtime1, time_t INtime2);

		// 获取星期几
		static Int32 GetWeekDay(time_t INtime);
	private:
		// 时间字符串转tm格式
		static tm ToTM(const string& INdataTimeString);

	public:
		// 获取时间
		static time_t GetTime(time_t* INtime);

		// 获取时间
		static tm GetTMTime(const time_t* INtime, bool INlocal = true);

		// 获取本地时间
		static tm GetLocalTMTime(const time_t* INtime);

		// 获取UTC时间
		static tm GetUTCTMTime(const time_t* INtime);

		// 获取当前UTC时间
		static string GetCurUTCTimeString();

		// 获取当前本地时间
		static string GetCurLocalTimeString();

		// 设置时区偏移秒数
		static void SetTimeOffSecond(time_t INtime){ m_timeOffSecond = INtime; }
	private:
		static time_t m_timeOffSecond;
	};
};



#endif