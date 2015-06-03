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
	// ��ʼ��
	bool Initial();

	// ����
	void Run();

	// ����
	void Clear();

	// ��ȡһ��redis�ͻ���
	boost::optional<RedisDBOperator&> GetFreeRedisDBOperator();

	// ��ȡ
	boost::optional<RedisDBOperator&> GetDataSyncRedisDBOperator();

	// �Ƿ���redis
	bool IsOpenRedis(){ return m_redisOpen; };
private:
	// �Ƿ���redis
	bool m_redisOpen;
	// redis�ͻ����б�
	vector<RedisDBOperator> m_redisDBOperatorVector;
};

#define REDIS_DBMANAGER_INSTANCE Singleton<RedisDBManager>::Instance()
#define REDIS_DBMANAGER_DESTROY Singleton<RedisDBManager>::DestroyInstance()

#endif