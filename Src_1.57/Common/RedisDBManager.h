#ifndef GAMESERVER_REDISDBMANAGER_H
#define GAMESERVER_REDISDBMANAGER_H

#include "Type.h"
#include "RedisDBOperator.h"
#include "CommDef.h"
#include "RedisKeyManager.h"

class RedisDBManager
{
public:
	RedisDBManager();

	~RedisDBManager();

public:
	// 初始化
	bool Initial();

	// 运行
	void Run();

	// 清理
	void Clear();

	// 获取一个redis客户端
	boost::optional<RedisDBOperator&> GetFreeRedisDBOperator();

	// 获取
	boost::optional<RedisDBOperator&> GetDataSyncRedisDBOperator();

	// 是否开启redis
	bool IsOpenRedis(){ return m_redisOpen; };
private:
	// 是否开启redis
	bool m_redisOpen;
	// redis客户端列表
	vector<RedisDBOperator> m_redisDBOperatorVector;
};

#define REDIS_DBMANAGER_INSTANCE Singleton<RedisDBManager>::Instance()
#define REDIS_DBMANAGER_DESTROY Singleton<RedisDBManager>::DestroyInstance()

#endif