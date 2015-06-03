#ifndef LIBRARY_UTIL_COMMON_H
#define LIBRARY_UTIL_COMMON_H

#include "Type.h"

namespace Library
{
	/**
	* @class Common
	* @note 非线程安全，不能保证多线程下数据正确性
	**/
	class Common
	{
	public:
		/**
		* @brief 转换字节整数为字符串
		**/
		static string MemSizeToString(UInt64 memSize);
		
		/**
		* @brief 获取进程内存大小
		**/
		static UInt64 GetProcessMemorySize();

		/**
		* @brief 一个整数是否在数组里
		**/
		static bool IsHaveInVector(vector<UInt32> vt, UInt32 INFind);
	};

}


#endif