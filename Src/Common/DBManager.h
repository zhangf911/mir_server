#ifndef GAMESERVER_DBMANAGER_H
#define GAMESERVER_DBMANAGER_H

#include "Type.h"
#include "DBEngine.h"
#include "CommDef.h"
#include <mutex>
#include <condition_variable>

class DBManager
{
public:
	typedef deque<string> SqlDeque;
public:
	DBManager();

	~DBManager();

public:
	// 初始化
	bool Initial();

	// 添加数据库操作
	void AddSql(string& INsql);

	// 添加批量数据库操作
	void AddSql(list<string>& INsqlList);

	// 获取sql操作队列
	void GetSqlDeque(SqlDeque& INsqlDeque);

	// 查询
	DBEngine* Query(const string& INsql);

	// 数据库线程主循环
	/*static*/ void Run(/*DBManager* INpDBManager*/);

	// 设置状态
	void Exit(){ m_runState = false; };

	// 执行所有
	void ExecuteAll();

	// 立即执行
	bool ExecuteAtOnce(const string& INsql);

	// 清理
	void Clear();
private:
	// 数据库SQL操作队列
	SqlDeque m_sqlDeque;
	// 数据库SQL操作队列锁
	std::mutex m_sqlDequeMutex;
	// 数据库线程状态
	bool m_runState;
	// 查询引擎
	DBEngine m_queryEngine;
	// 执行引擎
	DBEngine m_executeEngine;
	// 心跳计数
	UInt32 m_heartBeatCount;
	// 心跳计数输出时间戳
	UInt32 m_heartBeatCountTime;
	// 数据库
	string m_dbName;
};

#define DBMANAGER_INSTANCE Singleton<DBManager>::Instance()
#define DBMANAGER_DESTROY Singleton<DBManager>::DestroyInstance()

class DBQueryHelper
{
public:
	template <typename DBDataHandler>
	static UInt32 QueryHandler(const string INsql, DBDataHandler INhandler)
	{
		DBEngine* pDBEngine = DBMANAGER_INSTANCE->Query(INsql);
		if (pDBEngine)
		{
			if (pDBEngine->IsEof())
			{
				cout << "There is no Player Record" << endl;
			}
			UInt32 recordCount = pDBEngine->GetRecordCount();
			UInt32 fieldCount = pDBEngine->GetFieldCount();

			if (recordCount > 0)
			{
				if (!pDBEngine->IsFirst())
				{
					pDBEngine->MoveFirst();
				}

				for (UInt32 i = 0; i < recordCount; ++i)
				{
					INhandler(*pDBEngine);

					pDBEngine->MoveNext();
				}

				return recordCount;
			}
		}
		else
		{
			DEBUG_LOG("%s, %d, DBEngine Process Query '%s' Failed!",
				__FUNCTION__, __LINE__, INsql.c_str());
		}

		return 0;
	}
};

#endif