#ifndef LIBRARY_BASE_CODE_H
#define LIBRARY_BASE_CODE_H

#include <string>
using std::string;

class Code
{
public:
	/**
	* @brief ½«ASCII±àÂë×Ö·û´®×ª»»³ÉUTF8±àÂë×Ö·û´®
	* @param const string& INasciiString: ASCII×Ö·û´®
	* @param string& OUTutf8String: UTF8±àÂë×Ö·û´®
	* @return true: ³É¹¦; false: Ê§°Ü
	**/
	static bool ASCIIToUTF8(const string& INasciiString, string& OUTutf8String);

	/**
	* @brief ½«UTF8±àÂë×Ö·û´®×ª»»³ÉASCII±àÂë×Ö·û´®
	* @param const string& INutf8String: UTF8±àÂë×Ö·û´®
	* @param string& OUTasciiString: ASCII×Ö·û´®
	* @return true: ³É¹¦; false: Ê§°Ü
	**/
	static bool UTF8ToASCII(const string& INutf8String, string& OUTasciiString);


};


#endif