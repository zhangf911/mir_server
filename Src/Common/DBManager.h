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
	// ��ʼ��
	bool Initial();

	// ������ݿ����
	void AddSql(string& INsql);

	// ����������ݿ����
	void AddSql(list<string>& INsqlList);

	// ��ȡsql��������
	void GetSqlDeque(SqlDeque& INsqlDeque);

	// ��ѯ
	DBEngine* Query(const string& INsql);

	// ���ݿ��߳���ѭ��
	/*static*/ void Run(/*DBManager* INpDBManager*/);

	// ����״̬
	void Exit(){ m_runState = false; };

	// ִ������
	void ExecuteAll();

	// ����ִ��
	bool ExecuteAtOnce(const string& INsql);

	// ����
	void Clear();
private:
	// ���ݿ�SQL��������
	SqlDeque m_sqlDeque;
	// ���ݿ�SQL����������
	std::mutex m_sqlDequeMutex;
	// ���ݿ��߳�״̬
	bool m_runState;
	// ��ѯ����
	DBEngine m_queryEngine;
	// ִ������
	DBEngine m_executeEngine;
	// ��������
	UInt32 m_heartBeatCount;
	// �����������ʱ���
	UInt32 m_heartBeatCountTime;
	// ���ݿ�
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