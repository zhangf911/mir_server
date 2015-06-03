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
		/// ����̨��ʾ��Ϣ
		ELogType_Console_Note = 0x0001,
		/// ����̨������Ϣ
		ELogType_Console_Debug = 0x0002,
		/// ����̨������Ϣ
		ELogType_Console_Error = 0x0004,
		/// ����̨�쳣��Ϣ
		ELogType_Console_Exception = 0x0008,
		/// ����̨assert��Ϣ
		ELogType_Console_Assert = 0x00100,
		/// ����̨������Ϣ
		ELogType_Console_All = ELogType_Console_Note | ELogType_Console_Debug | ELogType_Console_Error | ELogType_Console_Exception | ELogType_Console_Assert,
		/// �ļ���ʾ��Ϣ
		ELogType_File_Note = 0x0010,
		/// �ļ�������Ϣ
		ELogType_File_Debug = 0x0020,
		/// �ļ�������Ϣ
		ELogType_File_Error = 0x0040,
		/// �ļ��쳣��Ϣ
		ELogType_File_Exception = 0x0080,
		/// �ļ�assert��Ϣ
		ELogType_File_Assert = 0x0200,
		/// �ļ�������Ϣ
		ELogType_File_All = ELogType_File_Note | ELogType_File_Debug | ELogType_File_Error | ELogType_File_Exception | ELogType_File_Assert,
		/// ������Ϣ
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
		/** �����־���� **/
		UInt32 m_logPriority;
		/** ��־�ļ� **/
		ofstream m_fileStream;
		/** �ļ������ʽ **/
		UInt32 m_fileCode;
		/** ��ǰ�ı������ʽ **/
		UInt32 m_textCode;
		/** ʱ���ʽ **/
		bool m_localTime;
	public:
		Log();

		~Log();

	public:

		/**
		* @brief ��ʼ��
		**/
		void Initial(const char* INfileName, bool INlocaltime = true, UInt32 INtextCode = ELogTextCode_ANSI);

		/**
		* @brief ������־�ȼ�
		**/
		void SetLogPriority(UInt32 INpriority);

		/**
		* @brief ��ȡ��־�ȼ�
		**/
		UInt32 GetLogPriority();

		/**
		* @brief ������־�ı�����
		* @param INcodeType : ��������
		* @exception
		* @note
		**/
		void SetLogTextCode(UInt32 INcodeType);

		/**
		* @brief ��ȡ��־�ı�����
		* @return ��־�ı�����
		* @exception
		* @note
		**/
		UInt32 GetLogTextCode();
		
		/**
		* @brief ������־��ɫ
		**/
		void SetColor(LogColor INcolor);
				
		/**
		* @brief �ָ�Ĭ����־��ɫ
		**/
		void ResetColor();
		
		/**
		* @brief �����ʾ��Ϣ
		**/
		void WriteNote(const char* INline, ...);

		/**
		* @brief ���������Ϣ
		**/
		void WriteDebug(const char* INline, ...);

		/**
		* @brief ���������Ϣ
		**/
		void WriteError(const char* INline, ...);

		/**
		* @brief ����쳣��Ϣ
		**/
		void WriteException(const char* INline, ...);

		/**
		* @brief ���assert��Ϣ
		**/
		void WriteAssert(const char* INline, ...);

		/**
		* @brief ���assert��Ϣ
		**/
		void WriteNon(const char* INline, ...){};

		/**
		* @brief ���һ�п���̨��־
		**/
		void WriteConsoleLine(const char* INline, UInt32 INtype);

		/**
		* @brief ���һ���ļ���־
		**/
		void WriteFileLine(const char* INline, UInt32 INtype);

		/**
		* @brief ���һ�п���̨��־
		**/
		void WriteConsoleLine(const string& INline, UInt32 INtype);

		/**
		* @brief ���һ���ļ���־
		**/
		void WriteFileLine(const string& INline, UInt32 INtype);

		/**
		* @brief ���һ��
		**/
		void WriteLine(const char* INline, ...);

		/**
		* @brief ��ʽ��ʱ���ַ���
		**/
		static void GetTimeString(char* INbuffer, const char* INtimeFormat, bool INlocalTime = true);
	};
}

#endif