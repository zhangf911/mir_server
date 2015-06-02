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
		// ��ȡת����Ҫ�Ŀ��ַ�����
		int iWideCharSize = MultiByteToWideChar(CP_ACP, 0, INasciiString.c_str(), INasciiString.size(), lpWideCharStr, 0);

		if(0 == iWideCharSize)
		{
			return false;
		}

		lpWideCharStr = new WCHAR[iWideCharSize];

		// ת���ɿ��ַ�
		iWideCharSize = MultiByteToWideChar(CP_ACP, 0, INasciiString.c_str(), INasciiString.size(), lpWideCharStr, iWideCharSize);

		if(0 == iWideCharSize)
		{
			// �ͷŶ�̬������ڴ�ռ�
			if (lpWideCharStr != nullptr)
			{
				delete[] lpWideCharStr;
				lpWideCharStr = nullptr;
			}

			return false;
		}

		// ��ȡת����UTF8���ַ�����
		int iMultiByteSize = WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, iWideCharSize, lpMultiByteStr, 0, nullptr, nullptr);

		if(0 == iMultiByteSize)
		{ 
			// �ͷŶ�̬������ڴ�ռ�
			if (lpWideCharStr != nullptr)
			{
				delete[] lpWideCharStr;
				lpWideCharStr = nullptr;
			}

			return false;
		}

		lpMultiByteStr = new char[iMultiByteSize];

		// ת����UTF8�ַ�
		iMultiByteSize = WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, iWideCharSize, lpMultiByteStr, iMultiByteSize, nullptr, nullptr);

		if(0 == iMultiByteSize)
		{ 
			// �ͷŶ�̬������ڴ�ռ�
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

		// �ַ������
		OUTutf8String.erase();
		// ��ֵ
		OUTutf8String.append(lpMultiByteStr, iMultiByteSize);

		// �ͷŶ�̬������ڴ�ռ�
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
		// ��ȡת����Ҫ�Ŀ��ַ�����
		int iWideCharSize = MultiByteToWideChar(CP_UTF8, 0, INutf8String.c_str(), INutf8String.size(), lpWideCharStr, 0);

		if(0 == iWideCharSize)
		{
			return false;
		}

		lpWideCharStr = new WCHAR[iWideCharSize];

		// ת���ɿ��ַ�
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

		// ��ȡת����ASCII���ַ�����
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

		// ת����ASCII�ַ�
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

		// �ַ������
		OUTasciiString.erase();

		// ��ֵ
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