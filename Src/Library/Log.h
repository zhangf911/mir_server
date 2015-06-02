#ifndef LIBRARY_BASE_LOG_H
#define LIBRARY_BASE_LOG_H

#include "Type.h"

namespace Library
{
	#define LogBufSize 32768
	#define TIME_FORMAT "[%Y-%m-%d %H:%M:%S] "
	#define TIME_FORMAT2 "[%Y-%m-%d %H-%M-%S]"
	#define TIME_FORMAT_LENGTH 40
	#define HEAD_LENGTH 20

	enum LogType
	{
		/// 控制台提示信息
		ELogType_Console_Note = 0x0001,
		/// 控制台调试信息
		ELogType_Console_Debug = 0x0002,
		/// 控制台错误信息
		ELogType_Console_Error = 0x0004,
		/// 控制台异常信息
		ELogType_Console_Exception = 0x0008,
		/// 控制台assert信息
		ELogType_Console_Assert = 0x00100,
		/// 控制台各类信息
		ELogType_Console_All = ELogType_Console_Note | ELogType_Console_Debug | ELogType_Console_Error | ELogType_Console_Exception | ELogType_Console_Assert,
		/// 文件提示信息
		ELogType_File_Note = 0x0010,
		/// 文件调试信息
		ELogType_File_Debug = 0x0020,
		/// 文件错误信息
		ELogType_File_Error = 0x0040,
		/// 文件异常信息
		ELogType_File_Exception = 0x0080,
		/// 文件assert信息
		ELogType_File_Assert = 0x0200,
		/// 文件各类信息
		ELogType_File_All = ELogType_File_Note | ELogType_File_Debug | ELogType_File_Error | ELogType_File_Exception | ELogType_File_Assert,
		/// 所有信息
		ELogType_All = ELogType_Console_All | ELogType_File_All,
	};

	enum LogColor
	{
		ELogColor_Black,
		ELogColor_Red,
		ELogColor_Green,
		ELogColor_Brown,
		ELogColor_Blue,
		ELogColor_Magenta,
		ELogColor_Cyan,
		ELogColor_Grey,
		ELogColor_Yellow,
		ELogColor_LRed,
		ELogColor_LGreen,
		ELogColor_LBlue,
		ELogColor_LMagenta,
		ELogColor_LCyan,
		ELogColor_White,
	};

	enum ELogTextCode
	{
		ELogTextCode_ANSI,
		ELogTextCode_UTF8,
	};
	
	class Log
	{
	private:
		/** 输出日志配置 **/
		UInt32 m_logPriority;
		/** 日志文件 **/
		ofstream m_fileStream;
		/** 文件编码格式 **/
		UInt32 m_fileCode;
		/** 当前文本编码格式 **/
		UInt32 m_textCode;
		/** 时间格式 **/
		bool m_localTime;
	public:
		Log();

		~Log();

	public:

		/**
		* @brief 初始化
		**/
		void Initial(const char* INfileName, bool INlocaltime = true, UInt32 INtextCode = ELogTextCode_ANSI);

		/**
		* @brief 设置日志等级
		**/
		void SetLogPriority(UInt32 INpriority);

		/**
		* @brief 获取日志等级
		**/
		UInt32 GetLogPriority();

		/**
		* @brief 设置日志文本编码
		* @param INcodeType : 编码类型
		* @exception
		* @note
		**/
		void SetLogTextCode(UInt32 INcodeType);

		/**
		* @brief 获取日志文本编码
		* @return 日志文本编码
		* @exception
		* @note
		**/
		UInt32 GetLogTextCode();
		
		/**
		* @brief 设置日志颜色
		**/
		void SetColor(LogColor INcolor);
				
		/**
		* @brief 恢复默认日志颜色
		**/
		void ResetColor();
		
		/**
		* @brief 输出提示信息
		**/
		void WriteNote(const char* INline, ...);

		/**
		* @brief 输出调试信息
		**/
		void WriteDebug(const char* INline, ...);

		/**
		* @brief 输出错误信息
		**/
		void WriteError(const char* INline, ...);

		/**
		* @brief 输出异常信息
		**/
		void WriteException(const char* INline, ...);

		/**
		* @brief 输出assert信息
		**/
		void WriteAssert(const char* INline, ...);

		/**
		* @brief 输出assert信息
		**/
		void WriteNon(const char* INline, ...){};

		/**
		* @brief 输出一行控制台日志
		**/
		void WriteConsoleLine(const char* INline, UInt32 INtype);

		/**
		* @brief 输出一行文件日志
		**/
		void WriteFileLine(const char* INline, UInt32 INtype);

		/**
		* @brief 输出一行控制台日志
		**/
		void WriteConsoleLine(const string& INline, UInt32 INtype);

		/**
		* @brief 输出一行文件日志
		**/
		void WriteFileLine(const string& INline, UInt32 INtype);

		/**
		* @brief 输出一行
		**/
		void WriteLine(const char* INline, ...);

		/**
		* @brief 格式化时间字符串
		**/
		static void GetTimeString(char* INbuffer, const char* INtimeFormat, bool INlocalTime = true);
	};
}

#endif