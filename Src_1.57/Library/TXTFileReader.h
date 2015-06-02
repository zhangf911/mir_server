#ifndef LIBRARY_TXTFILEREADER_H
#define LIBRARY_TXTFILEREADER_H

#include "Type.h"

// TXT文本读取类
class TXTFileReader
{
public:
	enum {EDataStartLine = 3, EDataTypeLine = 1,};

public:
	TXTFileReader();

	~TXTFileReader();

public:
	// 加载TXT配置文件
	bool LoadTXTFile(const char* INfileName);

	// 读取整形类型的配置字段值
	int ReadInt(UInt32 INline, UInt32 INindex);

	// 读取浮点类型的配置字段值
	double ReadFloat(UInt32 INline, UInt32 INindex);

	// 读取字符串类型的配置字段值
	const string& ReadString(UInt32 INline, UInt32 INindex);

	// 读取记录数量
	UInt32 GetRecordCount();

	// 读取字段数量
	UInt32 GetFieldCount();

public:
	void Print();

private:
	// txt配置数据表
	vector<vector<string>> m_txtDataMap;
};


#endif