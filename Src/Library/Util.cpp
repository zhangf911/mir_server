#include "Util.h"
#include <cmath>

#ifdef WIN32
#include <Windows.h>
#else
#include<sys/time.h>
#endif

using namespace std;

namespace Library
{
	float Round(float INfloatValue)
	{
		return std::floor(INfloatValue + 0.5f);
	}

	double Round(double INdoubleValue)
	{
		return std::floor(INdoubleValue + 0.5);
	}

	long double Round(long double INlongDoubleValue)
	{
		return std::floor(INlongDoubleValue + 0.5);
	}

	void Sleep(unsigned long INtimems)
	{
#ifdef WIN32
		::Sleep(INtimems);
#else
		timespec tv;

		tv.tv_sec = INtimems / 1000;
		tv.tv_nsec = (INtimems % 1000) * 1000 * 1000;

		nanosleep(&tv, NULL);
#endif
	}

	UInt32 GetMSTime()
	{
		UInt32 msTime = 0;
#ifdef WIN32
		msTime = GetTickCount();
#else
		timeval tv;
		gettimeofday(&tv, NULL);
		msTime = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
#endif
		return msTime;
	}
}