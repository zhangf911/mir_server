#ifndef LIBRARY_UTIL_COMMON_H
#define LIBRARY_UTIL_COMMON_H

#include "Type.h"

namespace Library
{
	/**
	* @class Common
	* @note ���̰߳�ȫ�����ܱ�֤���߳���������ȷ��
	**/
	class Common
	{
	public:
		/**
		* @brief ת���ֽ�����Ϊ�ַ���
		**/
		static string MemSizeToString(UInt64 memSize);
		
		/**
		* @brief ��ȡ�����ڴ��С
		**/
		static UInt64 GetProcessMemorySize();

		/**
		* @brief һ�������Ƿ���������
		**/
		static bool IsHaveInVector(vector<UInt32> vt, UInt32 INFind);
	};

}


#endif