#include "RedisDBManager.h"
#include "IniFileReader.h"

RedisDBManager::RedisDBManager()
{
	Clear();
}

RedisDBManager::~RedisDBManager()
{
	DESTROY_INSTANCE_LOG(RedisDBManager);
	Clear();
}

bool RedisDBManager::Initial()
{
	IniFileReader iniFileReader;
	iniFileReader.LoadIniFile("../../Config/ini/Redis.ini");
	
	UInt32 openflage = iniFileReader.ReadInt("Redis", "Open");
	if(openflage)
	{
		string host = iniFileReader.ReadString("RedisServer", "Host");
		UInt16 port = iniFileReader.ReadInt("RedisServer", "Port");

		if (m_redisDBOperatorVector.empty())
		{
			m_redisDBOperatorVector.resize(3);
		}

		for (auto& dbOperator : m_redisDBOperatorVector)
		{
			if (!dbOperator.Initial(host, port))
			{
				return false;
			}
		}

		m_redisOpen = true;

		NOTE_LOG("初始化redis数据同步");
	}

	return true;
}

void RedisDBManager::Run()
{

}

void RedisDBManager::Clear()
{
	m_redisDBOperatorVector.clear();
}

boost::optional<RedisDBOperator&> RedisDBManager::GetFreeRedisDBOperator()
{
	if(!m_redisDBOperatorVector.empty())
	{
		return m_redisDBOperatorVector.front();
	}
	return boost::none;
}

boost::optional<RedisDBOperator&> RedisDBManager::GetDataSyncRedisDBOperator()
{
	if (m_redisDBOperatorVector.size() > 1)
	{
		return m_redisDBOperatorVector[1];
	}
	return boost::none;
}