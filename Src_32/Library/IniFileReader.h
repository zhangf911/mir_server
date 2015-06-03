#ifndef LIBRARY_INIFILEREADER_H
#define LIBRARY_INIFILEREADER_H

#include "Type.h"

class IniFileReader
{
public:
	IniFileReader();

	~IniFileReader();

public:
	// 加载配置
	bool LoadIniFile(const char* INfileName);

	// 清理
	void Clear();
public:

	// 读取整形类型的配置字段值
	int ReadInt(const string& INsectionName, const string& INkeyName);

	// 读取浮点类型的配置字段值
	double ReadFloat(const string& INsectionName, const string& INkeyName);

	// 读取字符串类型的配置字段值
	const string& ReadString(const string& INsectionName, const string& INkeyName);

public:
	// 输出
	void Print();

private:
	map<string, map<string, string>> m_iniDataMap;
};

#endif