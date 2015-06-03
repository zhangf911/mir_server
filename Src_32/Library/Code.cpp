#include "Code.h"
#ifdef WIN32
#include <Windows.h>
#endif

bool Code::ASCIIToUTF8(const string& INasciiString, string& OUTutf8String)
{
#ifdef WIN32
	LPWSTR lpWideCharStr = nullptr;
	LPSTR lpMultiByteStr = nullptr;

	try
	{
		// 获取转换需要的宽字符个数
		int iWideCharSize = MultiByteToWideChar(CP_ACP, 0, INasciiString.c_str(), INasciiString.size(), lpWideCharStr, 0);

		if(0 == iWideCharSize)
		{
			return false;
		}

		lpWideCharStr = new WCHAR[iWideCharSize];

		// 转换成宽字符
		iWideCharSize = MultiByteToWideChar(CP_ACP, 0, INasciiString.c_str(), INasciiString.size(), lpWideCharStr, iWideCharSize);

		if(0 == iWideCharSize)
		{
			// 释放动态申请的内存空间
			if (lpWideCharStr != nullptr)
			{
				delete[] lpWideCharStr;
				lpWideCharStr = nullptr;
			}

			return false;
		}

		// 获取转换成UTF8的字符个数
		int iMultiByteSize = WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, iWideCharSize, lpMultiByteStr, 0, nullptr, nullptr);

		if(0 == iMultiByteSize)
		{ 
			// 释放动态申请的内存空间
			if (lpWideCharStr != nullptr)
			{
				delete[] lpWideCharStr;
				lpWideCharStr = nullptr;
			}

			return false;
		}

		lpMultiByteStr = new char[iMultiByteSize];

		// 转换成UTF8字符
		iMultiByteSize = WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, iWideCharSize, lpMultiByteStr, iMultiByteSize, nullptr, nullptr);

		if(0 == iMultiByteSize)
		{ 
			// 释放动态申请的内存空间
			if (lpWideCharStr != nullptr)
			{
				delete[] lpWideCharStr;
				lpWideCharStr = nullptr;
			}

			if (lpMultiByteStr != nullptr)
			{
				delete[] lpMultiByteStr;
				lpMultiByteStr = nullptr;
			}

			return false;
		}

		// 字符串清空
		OUTutf8String.erase();
		// 赋值
		OUTutf8String.append(lpMultiByteStr, iMultiByteSize);

		// 释放动态申请的内存空间
		if(lpWideCharStr != nullptr)
		{
			delete [] lpWideCharStr;
			lpWideCharStr = nullptr;
		}
		if(lpMultiByteStr != nullptr)
		{
			delete [] lpMultiByteStr;
			lpMultiByteStr = nullptr;
		}

		return true;
	}
	catch(...)
	{
		if(lpWideCharStr != nullptr)
		{
			delete [] lpWideCharStr;
			lpWideCharStr = nullptr;
		}

		if(lpMultiByteStr != nullptr)
		{
			delete [] lpMultiByteStr;
			lpMultiByteStr = nullptr;
		}

		return false;
	}
#endif
}

bool Code::UTF8ToASCII(const string& INutf8String, string& OUTasciiString)
{
#ifdef WIN32
	LPWSTR lpWideCharStr = nullptr;
	LPSTR lpMultiByteStr = nullptr;

	try
	{
		// 获取转换需要的宽字符个数
		int iWideCharSize = MultiByteToWideChar(CP_UTF8, 0, INutf8String.c_str(), INutf8String.size(), lpWideCharStr, 0);

		if(0 == iWideCharSize)
		{
			return false;
		}

		lpWideCharStr = new WCHAR[iWideCharSize];

		// 转换成宽字符
		iWideCharSize = MultiByteToWideChar(CP_UTF8, 0, INutf8String.c_str(), INutf8String.size(), lpWideCharStr, iWideCharSize);

		if(0 == iWideCharSize)
		{
			if (lpWideCharStr != nullptr)
			{
				delete[] lpWideCharStr;
				lpWideCharStr = nullptr;
			}

			return false;
		}

		// 获取转换成ASCII的字符个数
		int iMultiByteSize = WideCharToMultiByte(CP_ACP, 0, lpWideCharStr, iWideCharSize, lpMultiByteStr, 0, nullptr, nullptr);

		if(0 == iMultiByteSize)
		{ 
			if (lpWideCharStr != nullptr)
			{
				delete[] lpWideCharStr;
				lpWideCharStr = nullptr;
			}

			return false;
		}

		lpMultiByteStr = new char[iMultiByteSize];

		// 转换成ASCII字符
		iMultiByteSize = WideCharToMultiByte(CP_ACP, 0, lpWideCharStr, iWideCharSize, lpMultiByteStr, iMultiByteSize, nullptr, nullptr);

		if(0 == iMultiByteSize)
		{ 
			if (lpWideCharStr != nullptr)
			{
				delete[] lpWideCharStr;
				lpWideCharStr = nullptr;
			}

			if (lpMultiByteStr != nullptr)
			{
				delete[] lpMultiByteStr;
				lpMultiByteStr = nullptr;
			}

			return false;
		}

		// 字符串清空
		OUTasciiString.erase();

		// 赋值
		OUTasciiString.append(lpMultiByteStr, iMultiByteSize);

		if(lpWideCharStr != nullptr)
		{
			delete [] lpWideCharStr;
			lpWideCharStr = nullptr;
		}

		if(lpMultiByteStr != nullptr)
		{
			delete [] lpMultiByteStr;
			lpMultiByteStr = nullptr;
		}

		return true;
	}
	catch(...)
	{
		if(lpWideCharStr != nullptr)
		{
			delete [] lpWideCharStr;
			lpWideCharStr = nullptr;
		}

		if(lpMultiByteStr != nullptr)
		{
			delete [] lpMultiByteStr;
			lpMultiByteStr = nullptr;
		}

		return false;
	}
#endif
}