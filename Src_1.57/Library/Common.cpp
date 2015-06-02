#include "Common.h"
#include "Type.h"

#ifdef WIN32
	#include <windows.h>
	#include <Psapi.h>
#else
	#include <sys/types.h>
	#include <sys/time.h>
	#include <sys/resource.h>
#endif

namespace Library
{
	string Common::MemSizeToString(UInt64 memSize)
	{
		int KAll = memSize / 1024;
		int G = KAll / 1000 / 1000;
		int M = (KAll - G * 1000 * 1000) / 1000;
		int K = KAll - G * 1000 * 1000 - M * 1000;
		char buf[128];
		if (G >= 1)
		{
			std::sprintf(buf, "%d, %03d, %03d K", G, M, K);
		}
		else if (M >= 1)
		{
			std::sprintf(buf, "%d, %03d K", M, K);
		}
		else
		{
			std::sprintf(buf, "%d K", K);
		}

		return string(buf);
	}

	UInt64 Common::GetProcessMemorySize()
	{
		UInt64 i64Size = 0;
#ifdef WIN32
		PROCESS_MEMORY_COUNTERS pmc;
		if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
		{
			i64Size = pmc.WorkingSetSize;
		}
#else
		struct rusage buf;
		if (getrusage(RUSAGE_SELF, &buf) == 0)
		{
			i64Size = buf.ru_maxrss;
		}
#endif

		return i64Size;
	}

	bool Common::IsHaveInVector(vector<UInt32> vt, UInt32 INFind)
	{
		for (auto& it : vt)
		{
			if (it == INFind)
			{
				return true;
			}
		}

		return false;
	}

}



