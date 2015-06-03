#ifndef GAMESERVER_JSONHELPER_H
#define GAMESERVER_JSONHELPER_H

#include "Type.h"
#include "json/value.h"

namespace Json
{
	class Value;
}

class JsonHelper
{
public:
	static UInt32 ReadInt(Json::Value& INdata, const char* INkey)
	{
		if (INdata.isObject() && INdata.isMember(INkey) && INdata[INkey].isIntegral())
		{
			return INdata[INkey].asUInt();
		}
		return 0;
	}

	static double ReadDouble(Json::Value& INdata, const char* INkey)
	{
		if (INdata.isObject() && INdata.isMember(INkey) && INdata[INkey].isDouble())
		{
			return INdata[INkey].asDouble();
		}
		return 0;
	}

	static string ReadString(Json::Value& INdata, const char* INkey)
	{
		if (INdata.isObject() && INdata.isMember(INkey) && INdata[INkey].isString())
		{
			return INdata[INkey].asString();
		}

		return "";
	}

	template<typename DataReader>
	static void ReadArray(Json::Value& INdata, const char* INkey, DataReader INdataReader)
	{
		if (INdata.isObject() && INdata[INkey].isArray())
		{
			for (auto it = INdata[INkey].begin(); it != INdata[INkey].end(); ++it)
			{
				Json::Value& heroInfo = *it;

				INdataReader(heroInfo);
			}
		}
	}

	template<typename DataReader>
	static void ReadArray(Json::Value& INdata, DataReader INdataReader)
	{
		if (INdata.isArray())
		{
			for (auto it = INdata.begin(); it != INdata.end(); ++it)
			{
				Json::Value& heroInfo = *it;

				INdataReader(heroInfo);
			}
		}
	}
};


#endif