#include "Log.h"
#include <cstdio>
#include <cstdarg>
#include <iostream>
#include <time.h>

#ifdef WIN32
#include <Windows.h>
#else

#endif

namespace Library
{
	Log::Log()
	{
		m_logPriority = 0;
	}

	Log::~Log()
	{
		if(!m_fileStream.is_open())
		{
			m_fileStream.close();
		}
	}

	void Log::Initial(const char* INfileName, bool INlocaltime, UInt32 INtextCode)
	{
		m_localTime = INlocaltime;
		// 打开文件
		if(!m_fileStream.is_open())
		{
			m_fileCode = INtextCode;

			char timeBuf[40];
			GetTimeString(timeBuf, TIME_FORMAT2, m_localTime);
			string filename = INfileName;
			string temp = filename.substr(0, filename.find_last_of('.'));
			string extensionName = filename.substr(filename.find_last_of('.'));
			temp += timeBuf;
			temp += extensionName;
			m_fileStream.open(temp.c_str());
			if(!m_fileStream)
			{
				std::cerr << "Open File : " << temp << " Failed!" << std::endl;
			}
		}
	}

	void Log::SetLogPriority(UInt32 INpriority)
	{
		m_logPriority = INpriority;
	}

	UInt32 Log::GetLogPriority()
	{
		return m_logPriority;
	}

	void Log::SetLogTextCode(UInt32 INcodeType)
	{
		m_textCode = INcodeType;
	}

	UInt32 Log::GetLogTextCode()
	{
		return m_textCode;
	}

	void Log::SetColor(LogColor INcolor)
	{
		//ConsoleInterface::SetConsoleTextColor(true, Color(INcolor));
	}

	void Log::ResetColor()
	{
		//ConsoleInterface::ResetConsoleTextColor(true);
	}

	void Log::WriteNote(const char* INline, ...)
	{
		if(((m_logPriority & ELogType_Console_Note) == 0) && 
			((m_logPriority & ELogType_File_Note) == 0))
		{
			return;
		}
		char buf[LogBufSize];
		va_list ap;

		va_start(ap, INline);
#ifdef WIN32
		vsnprintf_s(buf, LogBufSize, INline, ap);
#else
		vsnprintf(buf, LogBufSize, INline, ap);
#endif
		va_end(ap);

		if(m_logPriority & ELogType_Console_Note)
		{
			//SetColor(ELogColor_DeepYellow);
			// 输出控制台提示信息
			WriteConsoleLine(buf, ELogType_Console_Note);
		}
		if(m_logPriority & ELogType_File_Note)
		{
			if(!m_fileStream)
			{
				std::cerr << "File have not opened!" << std::endl;
				return;
			}
			// 输出文件提示信息
			WriteFileLine(buf, ELogType_File_Note);
		}
	}

	void Log::WriteDebug(const char* INline, ...)
	{
		if(((m_logPriority & ELogType_Console_Debug) == 0) && 
			((m_logPriority & ELogType_File_Debug) == 0))
		{
			return;
		}
		char buf[LogBufSize];
		va_list ap;

		va_start(ap, INline);
#ifdef WIN32
		vsnprintf_s(buf, LogBufSize, INline, ap);
#else
		vsnprintf(buf, LogBufSize, INline, ap);
#endif
		va_end(ap);

		if(m_logPriority & ELogType_Console_Debug)
		{
			//SetColor(ELogColor_DeepGreen);
			// 输出控制台调试信息
			WriteConsoleLine(buf, ELogType_Console_Debug);
		}
		if(m_logPriority & ELogType_File_Debug)
		{
			if(!m_fileStream)
			{
				std::cerr << "File have not opened!" << std::endl;
				return;
			}
			// 输出文件调试信息
			WriteFileLine(buf, ELogType_File_Debug);
		}
	}

	void Log::WriteError(const char* INline, ...)
	{
		if(((m_logPriority & ELogType_Console_Error) == 0) && 
			((m_logPriority & ELogType_File_Error) == 0))
		{
			return;
		}
		char buf[LogBufSize];
		va_list ap;

		va_start(ap, INline);
#ifdef WIN32
		vsnprintf_s(buf, LogBufSize, INline, ap);
#else
		vsnprintf(buf, LogBufSize, INline, ap);
#endif
		va_end(ap);

		if(m_logPriority & ELogType_Console_Error)
		{
			//SetColor(ELogColor_DeepRed);
			SetColor(ELogColor_LRed);
			// 输出控制台错误信息
			WriteConsoleLine(buf, ELogType_Console_Error);
			// 
			//SetColor(ELogColor_White);
			ResetColor();
		}
		
		if(m_logPriority & ELogType_File_Error)
		{
			if(!m_fileStream)
			{
				std::cerr << "File have not opened!" << std::endl;
				return;
			}
			// 输出文件错误信息
			WriteFileLine(buf, ELogType_File_Error);
		}
	}

	void Log::WriteException(const char* INline, ...)
	{
		if(((m_logPriority & ELogType_Console_Exception) == 0) && 
			((m_logPriority & ELogType_File_Exception) == 0))
		{
			return;
		}
		char buf[LogBufSize];
		va_list ap;

		va_start(ap, INline);
#ifdef WIN32
		vsnprintf_s(buf, LogBufSize, INline, ap);
#else
		vsnprintf(buf, LogBufSize, INline, ap);
#endif
		va_end(ap);

		if(m_logPriority & ELogType_Console_Exception)
		{
			SetColor(ELogColor_Magenta);
			// 输出控制台异常信息
			WriteConsoleLine(buf, ELogType_Console_Exception);
			ResetColor();
		}

		if(m_logPriority & ELogType_File_Exception)
		{
			if(!m_fileStream)
			{
				std::cerr << "File have not opened!" << std::endl;
				return;
			}
			// 输出文件异常信息
			WriteFileLine(buf, ELogType_File_Exception);
		}
	}

	void Log::WriteAssert(const char* INline, ...)
	{
		if (((m_logPriority & ELogType_Console_Assert) == 0) &&
			((m_logPriority & ELogType_File_Assert) == 0))
		{
			return;
		}
		char buf[LogBufSize];
		va_list ap;

		va_start(ap, INline);
#ifdef WIN32
		vsnprintf_s(buf, LogBufSize, INline, ap);
#else
		vsnprintf(buf, LogBufSize, INline, ap);
#endif
		va_end(ap);

		if (m_logPriority & ELogType_Console_Assert)
		{
			SetColor(ELogColor_Magenta);
			// 输出控制台异常信息
			WriteConsoleLine(buf, ELogType_Console_Assert);
			ResetColor();
		}

		if (m_logPriority & ELogType_File_Assert)
		{
			if (!m_fileStream)
			{
				std::cerr << "File have not opened!" << std::endl;
				return;
			}
			// 输出文件异常信息
			WriteFileLine(buf, ELogType_File_Assert);
		}
	}

	void Log::WriteConsoleLine(const char* INline, UInt32 INtype)
	{
		char strTime[TIME_FORMAT_LENGTH];
		GetTimeString(strTime, TIME_FORMAT, m_localTime);
		string head;
		switch(INtype)
		{
		case ELogType_Console_Note:
		case ELogType_File_Note:
			{
				head = "[Note] ";
				break;
			}
		case ELogType_Console_Debug:
		case ELogType_File_Debug:
			{
				head = "[Debug] ";
				break;
			}
		case ELogType_Console_Error:
		case ELogType_File_Error:
			{
				head = "[Error] ";
				break;
			}
		case ELogType_Console_Exception:
		case ELogType_File_Exception:
			{
				head = "[Exception] ";
				break;
			}
		default:
			{
				head = "";
				break;
			}
		}

		std::cout << strTime << head << INline << std::endl;
	}

	void Log::WriteFileLine(const char* INline, UInt32 INtype)
	{
		char strTime[TIME_FORMAT_LENGTH];
		GetTimeString(strTime, TIME_FORMAT, m_localTime);
		string head;
		switch(INtype)
		{
		case ELogType_Console_Note:
		case ELogType_File_Note:
			{
				head = "[Note]";
				break;
			}
		case ELogType_Console_Debug:
		case ELogType_File_Debug:
			{
				head = "[Debug]";
				break;
			}
		case ELogType_Console_Error:
		case ELogType_File_Error:
			{
				head = "[Error]";
				break;
			}
		case ELogType_Console_Exception:
		case ELogType_File_Exception:
			{
				head = "[Exception]";
				break;
			}
		case ELogType_Console_Assert:
		case ELogType_File_Assert:
			{
				head = "[Assert]";
				break;
			}
		default:
			{
				head = "";
				break;
			}
		}

		m_fileStream << strTime << head << INline << std::endl;
	}

	void Log::WriteConsoleLine(const string& INline, UInt32 INtype)
	{

	}

	void Log::WriteFileLine(const string& INline, UInt32 INtype)
	{

	}

	void Log::WriteLine(const char* INline, ...)
	{

	}

	void Log::GetTimeString(char* INbuffer, const char* INtimeFormat, bool INlocalTime)
	{
		
		time_t now;
		//struct tm * timeinfo = NULL;
		tm timeinfo;
		time( &now );

#ifdef WIN32
		if (INlocalTime)
		{
			localtime_s(&timeinfo, &now);
		}
		else
		{
			now += 3600 * 8;
			gmtime_s(&timeinfo, &now);
		}
#else
		if(INlocalTime)
		{
			localtime_r(&now, &timeinfo);
		}
		else
		{
			now += 3600 * 8;
			gmtime_r(&now, &timeinfo);
		}
#endif
		strftime(INbuffer, TIME_FORMAT_LENGTH, INtimeFormat, &timeinfo);

		//timeinfo = localtime( &now );

		//if( timeinfo != NULL )
		//{
		//	strftime(INbuffer,TIME_FORMAT_LENGTH,INtimeFormat,timeinfo);
		//}
		//else
		//{
		//	INbuffer[0] = '\0';
		//}
	}
}