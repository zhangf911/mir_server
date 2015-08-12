#ifndef LIBRARY_TXTFILEREADER_H
#define LIBRARY_TXTFILEREADER_H

#include "Type.h"

// TXT�ı���ȡ��
class TXTFileReader
{
public:
	enum {EDataStartLine = 3, EDataTypeLine = 1,};

public:
	TXTFileReader();

	~TXTFileReader();

public:
	// ����TXT�����ļ�
	bool LoadTXTFile(const char* INfileName);

	// ��ȡ�������͵������ֶ�ֵ
	int ReadInt(UInt32 INline, UInt32 INindex);

	// ��ȡ�������͵������ֶ�ֵ
	double ReadFloat(UInt32 INline, UInt32 INindex);

	// ��ȡ�ַ������͵������ֶ�ֵ
	const string& ReadString(UInt32 INline, UInt32 INindex);

	// ��ȡ��¼����
	UInt32 GetRecordCount();

	// ��ȡ�ֶ�����
	UInt32 GetFieldCount();

public:
	void Print();

private:
	// txt�������ݱ�
	vector<vector<string>> m_txtDataMap;
};


#endif