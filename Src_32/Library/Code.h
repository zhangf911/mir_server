#ifndef LIBRARY_BASE_CODE_H
#define LIBRARY_BASE_CODE_H

#include <string>
using std::string;

class Code
{
public:
	/**
	* @brief ��ASCII�����ַ���ת����UTF8�����ַ���
	* @param const string& INasciiString: ASCII�ַ���
	* @param string& OUTutf8String: UTF8�����ַ���
	* @return true: �ɹ�; false: ʧ��
	**/
	static bool ASCIIToUTF8(const string& INasciiString, string& OUTutf8String);

	/**
	* @brief ��UTF8�����ַ���ת����ASCII�����ַ���
	* @param const string& INutf8String: UTF8�����ַ���
	* @param string& OUTasciiString: ASCII�ַ���
	* @return true: �ɹ�; false: ʧ��
	**/
	static bool UTF8ToASCII(const string& INutf8String, string& OUTasciiString);


};


#endif