#include "DataTime.h"

#include "Log.h"

#include <sstream>
using std::stringstream;

#include <time.h>

#define TIME_FORMAT3 "%Y-%m-%d %H:%M:%S"
#define TIME_FORMAT_LENGTH 40

void PrintTime(const struct tm INtm)
{
	printf("tm_year = %d", INtm.tm_year);
	printf("tm_mon = %d", INtm.tm_mon);
	printf("tm_mday = %d", INtm.tm_mday);
	printf("tm_hour = %d\n", INtm.tm_hour);
	printf("tm_min = %d", INtm.tm_min);
	printf("tm_sec = %d", INtm.tm_sec);
	printf("tm_wday = %d", INtm.tm_wday);
	printf("tm_isdst = %d\n", INtm.tm_isdst);
#if WIN32

#else
	printf("tm_timezone = %s\n", INtm.tm_zone);
	printf("tm_gmtoff = %ld\n", INtm.tm_gmtoff);
#endif
	printf("\n");
}

namespace Library
{
	time_t DataTimeHelper::m_timeOffSecond = 0;

	time_t DataTimeHelper::GetCurDayZeroTime()
	{
#if WIN32
		return GetCurDayLocalZeroTime();
#else
		return GetCurDayUTCZeroTime();
#endif
	}

	time_t DataTimeHelper::GetCurDayLocalZeroTime()
	{
		time_t nowTimestamp = GetTime(nullptr);

		tm zeroTimetm = GetLocalTMTime(&nowTimestamp);

		zeroTimetm.tm_hour = 0;
		zeroTimetm.tm_min = 0;
		zeroTimetm.tm_sec = 0;

		time_t zeroTimestamp = mktime(&zeroTimetm);

		return zeroTimestamp;
	}

	time_t DataTimeHelper::GetCurDayUTCZeroTime()
	{
		time_t nowTimestamp = GetTime(nullptr);

		tm zeroTimetm = GetUTCTMTime(&nowTimestamp);

		zeroTimetm.tm_hour = 0;
		zeroTimetm.tm_min = 0;
		zeroTimetm.tm_sec = 0;

		time_t zeroTimestamp = mktime(&zeroTimetm);

		return zeroTimestamp;
	}

	time_t DataTimeHelper::GetDayZeroTime(time_t INtime)
	{
		tm zeroTimetm = GetTMTime(&INtime);

		zeroTimetm.tm_hour = 0;
		zeroTimetm.tm_min = 0;
		zeroTimetm.tm_sec = 0;

		time_t zeroTimestamp = mktime(&zeroTimetm);

		return zeroTimestamp;
	}

	string DataTimeHelper::GetCurTimeString()
	{
		time_t now = GetTime(nullptr);

		char buf[40];
		//now += m_timeOffSecond;
		tm timeInfo = GetTMTime(&now);

		strftime(buf, 40, "%Y-%m-%d %H:%M:%S", &timeInfo);

		return string(buf);	
	}

	string DataTimeHelper::ToString(time_t INtime)
	{
		if(INtime == 0)
		{
			return "0000-00-00 00:00:00";
		}

		char buf[40];

		time_t now = INtime;
		//now += m_timeOffSecond;
		tm timeInfo = GetTMTime(&now);

		strftime(buf, 40, "%Y-%m-%d %H:%M:%S", &timeInfo);

		return string(buf);	
	}

	time_t DataTimeHelper::ToInt(const string& INdataTimeString)
	{
		if (INdataTimeString.compare("0000-00-00 00:00:00") == 0 || INdataTimeString == "")
		{
			return 0;
		}

		tm localtm = ToTM(INdataTimeString);

		time_t result = mktime(&localtm);

		return result;
	}

	string DataTimeHelper::GetTimeStringAfter(time_t INtime)
	{
		return ToString(GetTime(nullptr) + INtime);
	}

	string DataTimeHelper::GetTimeStringAfter(const string& INtime)
	{
		return ToString(GetTime(nullptr) + ToInt(INtime));
	}

	string DataTimeHelper::GetTimeStringAfter(const string& INstartTime, time_t INsecond)
	{
		return ToString(ToInt(INstartTime) + INsecond);
	}

	string DataTimeHelper::GetTimeStringAfter(time_t INstartTime, time_t INsecond)
	{
		return ToString(INstartTime + INsecond);
	}

	bool DataTimeHelper::IsSameDay(const string& INtime1, const string INtime2)
	{
		tm tm1 = ToTM(INtime1);
		tm tm2 = ToTM(INtime2);

		if(tm1.tm_year == tm2.tm_year &&
			tm1.tm_mon == tm2.tm_mon &&
			tm1.tm_mday == tm2.tm_mday)
		{
			return true;
		}

		return false;
	}

	bool DataTimeHelper::IsSameDay(time_t INtime1, time_t INtime2)
	{
		tm tm1 = GetTMTime(&INtime1);
		tm tm2 = GetTMTime(&INtime2);

		if(tm1.tm_year == tm2.tm_year &&
			tm1.tm_mon == tm2.tm_mon &&
			tm1.tm_mday == tm2.tm_mday)
		{
			return true;
		}

		return false;
	}

	bool DataTimeHelper::IsLater(const string& INtime1, const string INtime2)
	{
		return IsLater(ToInt(INtime1), ToInt(INtime2));
	}

	bool DataTimeHelper::IsLater(time_t INtime1, time_t INtim2)
	{
		return difftime(INtime1, INtim2) > 0 ? true : false;
	}

	time_t DataTimeHelper::DiffSecond(const string INtime1, const string INtime2)
	{
		time_t time1 = ToInt(INtime1);
		time_t time2 = ToInt(INtime2);

		return time_t(difftime(time1, time2));
	}

	time_t DataTimeHelper::DiffSecond(time_t INtime1, time_t INtime2)
	{
		return time_t(difftime(INtime1, INtime2));
	}

	Int32 DataTimeHelper::DiffDay(const string INtime1, const string INtime2)
	{
		tm tm1 = ToTM(INtime1);
		tm tm2 = ToTM(INtime2);

		return tm1.tm_yday - tm2.tm_yday;
	}

	Int32 DataTimeHelper::DiffDay(time_t INtime1, time_t INtime2)
	{
		tm tm1 = GetTMTime(&INtime1);
		tm tm2 = GetTMTime(&INtime2);

		return tm1.tm_yday - tm2.tm_yday;
	}

	Int32 DataTimeHelper::GetWeekDay(time_t INtime)
	{
		tm tmtime = GetTMTime(&INtime);
		return tmtime.tm_wday;
	}

	tm DataTimeHelper::ToTM(const string& INdataTimeString)
	{
		string timestr;
		stringstream timess(INdataTimeString);
		char buf[] = "-- :: ";
		UInt32 index = 0;

		Int32 tm_time[6] = {0};
		while(getline(timess, timestr, buf[index]))
		{
			tm_time[index] = atoi(timestr.c_str());
			++index;
		}

		time_t now;
		GetTime(&now);

		tm nowtimetm = GetTMTime(&now);

		nowtimetm.tm_year = tm_time[0] - 1900;
		nowtimetm.tm_mon = tm_time[1] - 1;
		nowtimetm.tm_mday = tm_time[2];
		nowtimetm.tm_hour = tm_time[3];
		nowtimetm.tm_min = tm_time[4];
		nowtimetm.tm_sec = tm_time[5];

		time_t newTime = mktime(&nowtimetm);
		//newTime += m_timeOffSecond;
		nowtimetm = GetTMTime(&newTime);

		return nowtimetm;
	}

	time_t DataTimeHelper::GetTime(time_t* INtime)
	{
		if(INtime != nullptr)
		{
			*INtime = time(INtime) + m_timeOffSecond;
			return *INtime;
		}
		else
		{
			return time(INtime) + m_timeOffSecond;
		}
	}

	tm DataTimeHelper::GetTMTime(const time_t* INtime, bool INlocal)
	{
#if WIN32
		//if(INlocal)
		//{
			return GetLocalTMTime(INtime);
#else
		//}
		//else
		//{
			return GetUTCTMTime(INtime);
		//}
#endif
	}

	tm DataTimeHelper::GetLocalTMTime(const time_t* INtime)
	{
		tm timetm;
#ifdef WIN32
		localtime_s(&timetm, INtime);
#else
		localtime_r(INtime, &timetm);
#endif
		return timetm;
	}

	tm DataTimeHelper::GetUTCTMTime(const time_t* INtime)
	{
		//time_t realtime = *INtime + 3600 * 8;
		tm timetm;
#ifdef WIN32
		//gmtime_s(&timetm, &realtime);
		gmtime_s(&timetm, INtime);
#else
		//gmtime_r(&realtime, &timetm);
		gmtime_r(INtime, &timetm);
#endif
		return timetm;
	}

	string DataTimeHelper::GetCurUTCTimeString()
	{
		time_t now = GetTime(nullptr);

		char buf[40];
		tm timeInfo = GetUTCTMTime(&now);

		strftime(buf, 40, "%Y-%m-%d %H:%M:%S", &timeInfo);

		return string(buf);
	}

	string DataTimeHelper::GetCurLocalTimeString()
	{
		time_t now = GetTime(nullptr);

		char buf[40];
		tm timeInfo = GetLocalTMTime(&now);

		strftime(buf, 40, "%Y-%m-%d %H:%M:%S", &timeInfo);

		return string(buf);
	}
}



