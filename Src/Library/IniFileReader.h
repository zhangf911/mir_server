#ifndef LIBRARY_INIFILEREADER_H
#define LIBRARY_INIFILEREADER_H

#include "Type.h"

class IniFileReader
{
public:
	IniFileReader();

	~IniFileReader();

public:
	// ��������
	bool LoadIniFile(const char* INfileName);

	// ����
	void Clear();
public:

	// ��ȡ�������͵������ֶ�ֵ
	int ReadInt(const string& INsectionName, const string& INkeyName);

	// ��ȡ�������͵������ֶ�ֵ
	double ReadFloat(const string& INsectionName, const string& INkeyName);

	// ��ȡ�ַ������͵������ֶ�ֵ
	const string& ReadString(const string& INsectionName, const string& INkeyName);

public:
	// ���
	void Print();

private:
	map<string, map<string, string>> m_iniDataMap;
};

#endif