#ifndef GAMESERVER_CONFIGPARSEHELPER_H
#define GAMESERVER_CONFIGPARSEHELPER_H

#include "Type.h"
#include "StringUtil.h"
#include "TXTFileReader.h"
#include "CommDef.h"

class ConfigParseHelper
{
public:
	// 配置加载模板
	template <typename ConfigDataHandler>
	static bool LoadTXTFile(const string& INfileName, ConfigDataHandler INconfigDataHandler)
	{
		CONFIG_LOAD_NOTE("Start Load Config '%s' ......",
			INfileName.c_str());

		TXTFileReader txtFileReader;
		if (!txtFileReader.LoadTXTFile(INfileName.c_str()))
		{
			ERROR_LOG("%s, %d, Load Config Failed!",
				__FUNCTION__, __LINE__);
			return false;
		}

		UInt32 recordCount = txtFileReader.GetRecordCount();
		UInt32 fieldCount = txtFileReader.GetFieldCount();

		for (UInt32 i = 0; i < recordCount; ++i)
		{
			INconfigDataHandler(txtFileReader, i);
		}

		CONFIG_LOAD_NOTE("Load Config '%s' ......Succeed!",
			INfileName.c_str());

		return true;
	};

	// 配置加载模板
	template <typename ConfigDataHandler>
	static bool LoadAndParseTXTFile(const string& INfileName, ConfigDataHandler INconfigDataHandler)
	{
		CONFIG_LOAD_NOTE("Start Load Config '%s' ......",
			INfileName.c_str());

		TXTFileReader txtFileReader;
		if (!txtFileReader.LoadTXTFile(INfileName.c_str()))
		{
			ERROR_LOG("%s, %d, Load Config Failed!",
				__FUNCTION__, __LINE__);
			return false;
		}

		txtFileReader.Parse();
		txtFileReader.Print();

		CONFIG_LOAD_NOTE("Load Config '%s' ......Succeed!",
			INfileName.c_str());

		return true;
	};

	// 数据格式解析模板
	template <typename Parser>
	static void ParseFormatString(string& INformatString, Parser INparser)
	{
		if (INformatString.compare("0") != 0)
		{
			vector<string> dropItemVector;
			Library::StringUtil::Split<'#'>(INformatString, dropItemVector);
			for (auto it = dropItemVector.begin(); it != dropItemVector.end(); ++it)
			{
				vector<string> itemProp;
				Library::StringUtil::Split<'|'>(*it, itemProp);

				bool succeed = INparser(itemProp);
				SJ_ASSERT(succeed);
			}
		}
	};
};


#endif