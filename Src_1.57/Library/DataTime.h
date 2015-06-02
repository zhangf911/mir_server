#ifndef LIBRARY_UTIL_DATATIME_H
#define LIBRARY_UTIL_DATATIME_H

#include "Type.h"

namespace Library
{
	/**
	* @class DataTime
	* @note ���̰߳�ȫ�����ܱ�֤���߳���������ȷ��
	**/
	class DataTimeHelper
	{
	public:
		/**
		* @brief ��ȡ�����賿ʱ��
		**/
		static time_t GetCurDayZeroTime();

		/**
		* @brief ��ȡ�����賿ʱ��
		**/
		static time_t GetCurDayLocalZeroTime();

		/**
		* @brief ��ȡ�����賿ʱ��
		**/
		static time_t GetCurDayUTCZeroTime();

		// ��ȡָ�����ڵ��賿ʱ���
		static time_t GetDayZeroTime(time_t INtime);

		// ��ȡ��ǰʱ���ַ���
		static string GetCurTimeString();

		/**
		* @brief ������ʱ��ת��Ϊ�ַ�����ʽ
		* @note  ��ʽΪ xxxx-xx-xx xx:xx:xx
		**/
		static string ToString(time_t INtime);

		/**
		* @brief ���ַ�����ʽ��ʱ��ת��Ϊ����ֵ
		* @note  �ַ�����ʽ xxxx-xx-xx xx:xx:xx
		**/
		static time_t ToInt(const string& INdataTimeString);

		// ��ȡ��ǰʱ������һ��ʱ���ַ���
		static string GetTimeStringAfter(time_t INtime);

		// ��ȡ��ǰʱ������һ��ʱ���ַ���
		static string GetTimeStringAfter(const string& INtime);

		// ��ȡָ��ʱ�������һ��ʱ���ַ���
		static string GetTimeStringAfter(time_t INstartTime, time_t INsecond);

		// ��ȡָ��ʱ�������һ��ʱ���ַ���
		static string GetTimeStringAfter(const string& INstartTime, time_t INsecond);

		// �Ƿ�ͬһ��
		static bool IsSameDay(const string& INtime1, const string INtime2);

		// �Ƿ�ͬһ��
		static bool IsSameDay(time_t INtime1, time_t INtime2);

		// �Ƿ�time1��time2��
		static bool IsLater(const string& INtime1, const string INtime2);

		// �Ƿ�time1��time2��
		static bool IsLater(time_t INtime1, time_t INtim2);

		// ʱ���(��λ��)
		static time_t DiffSecond(const string INtime1, const string INtime2);

		// ʱ���(��λ��)
		static time_t DiffSecond(time_t INtime1, time_t INtime2);

		// ���ڲ�(��λ��)
		static Int32 DiffDay(const string INtime1, const string INtime2);

		// ���ڲ�(��λ��)
		static Int32 DiffDay(time_t INtime1, time_t INtime2);

		// ��ȡ���ڼ�
		static Int32 GetWeekDay(time_t INtime);
	private:
		// ʱ���ַ���תtm��ʽ
		static tm ToTM(const string& INdataTimeString);

	public:
		// ��ȡʱ��
		static time_t GetTime(time_t* INtime);

		// ��ȡʱ��
		static tm GetTMTime(const time_t* INtime, bool INlocal = true);

		// ��ȡ����ʱ��
		static tm GetLocalTMTime(const time_t* INtime);

		// ��ȡUTCʱ��
		static tm GetUTCTMTime(const time_t* INtime);

		// ��ȡ��ǰUTCʱ��
		static string GetCurUTCTimeString();

		// ��ȡ��ǰ����ʱ��
		static string GetCurLocalTimeString();

		// ����ʱ��ƫ������
		static void SetTimeOffSecond(time_t INtime){ m_timeOffSecond = INtime; }
	private:
		static time_t m_timeOffSecond;
	};
};



#endif