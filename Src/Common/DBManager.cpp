#include "DBManager.h"
#include "DBEngine.h"
#include "Singleton.h"
#include "CommDef.h"
#include "IniFileReader.h"
#include "ThreadExitHelper.h"

#include <algorithm>
#include <thread>

DBManager::DBManager()
	: m_runState(false)
{
	Clear();
}

DBManager::~DBManager()
{
	DESTROY_INSTANCE_LOG(DBManager);
	Clear();
}

bool DBManager::Initial()
{
	IniFileReader iniFileReader;
	iniFileReader.LoadIniFile("../../Config/ini/GameServer.ini");

	string server = iniFileReader.ReadString("DataBase", "Host");
	unsigned port = iniFileReader.ReadInt("DataBase", "Port");
	string user = iniFileReader.ReadString("DataBase", "User");
	string password = iniFileReader.ReadString("DataBase", "Password");
	string db = iniFileReader.ReadString("DataBase", "DB");

	if (!m_queryEngine.Connect(server, port, user, password, db))
	{
		cout << "连接数据库失败!" << endl;
		return false;
	}
	cout << "Connect DB Succeed , Server : " << server << " Port :" << port << endl;

	m_queryEngine.UseDB(db.c_str());

	if (!m_executeEngine.Connect(server, port, user, password, db))
	{
		cout << "连接数据库失败!" << endl;
		return false;
	}
	cout << "Connect DB Succeed , Server : " << server << " Port :" << port << endl;

	m_executeEngine.UseDB(db.c_str());

	m_dbName = db;
	m_runState = true;

	m_heartBeatCount = 0;
	m_heartBeatCountTime = Library::DataTimeHelper::GetTime(nullptr);

	return true;
}

void DBManager::AddSql(string& INsql)
{
	std::lock_guard<std::mutex> guard(m_sqlDequeMutex);
	m_sqlDeque.push_back(std::move(INsql));
}

void DBManager::AddSql(list<string>& INsqlList)
{
	std::for_each(INsqlList.begin(), INsqlList.end(), [this](string& INsql){AddSql(INsql);});
}

void DBManager::GetSqlDeque(SqlDeque& INsqlDeque)
{
	std::lock_guard<std::mutex> guard(m_sqlDequeMutex);
	INsqlDeque = std::move(m_sqlDeque);
}

DBEngine* DBManager::Query(const string& INsql)
{
	if(m_queryEngine.Query(INsql))
	{
		return &m_queryEngine;
	}
	else
	{
		ERROR_LOG("%s, %d, DBEngine Process Query '%s' Failed!",
			__FUNCTION__, __LINE__, INsql.c_str());
	}
	return nullptr;
}

void DBManager::Run(/*DBManager* INpDBManager*/)
{
	NOTE_LOG("数据库操作线程, 线程编号 : %d",
		std::this_thread::get_id());

	while (/*INpDBManager->*/m_runState)
	{
		++m_heartBeatCount;

		UInt32 curTime = Library::DataTimeHelper::GetTime(nullptr);

		if (curTime > m_heartBeatCountTime + 60)
		{
			NOTE_LOG("DBManager HeartBeat Count : %d",
				m_heartBeatCount);
			m_heartBeatCountTime = curTime;
		}

		try
		{
			SqlDeque sqlDeque;
			/*INpDBManager->*/GetSqlDeque(sqlDeque);
			DBEngine& pDBEngine = /*INpDBManager->*/m_executeEngine;
			if (!sqlDeque.empty())
			{
				string startCommitSql = "start transaction;";
				sqlDeque.push_front(startCommitSql);
				string endCommitSql = "commit;";
				sqlDeque.push_back(endCommitSql);

				while (!sqlDeque.empty())
				{
					string sql = sqlDeque.front();
					if (!pDBEngine.Execute(sql))
					{
						ERROR_LOG("%s, %d, DBEngine Process Execute sql Failed! %s:",
							__FUNCTION__, __LINE__, sql.c_str());
					}
					sqlDeque.pop_front();
				}
			}

			std::chrono::milliseconds dura(40);
			std::this_thread::sleep_for(dura);
		}
		catch (...)
		{
			ERROR_LOG("数据库操作线程异常!!!");
		}
	}

	NOTE_LOG("退出数据库执行循环");

	std::unique_lock <std::mutex> lck(ThreadExitHelper::m_dbWorkThreadMutex);
	ThreadExitHelper::m_dbWorkThreadExitCV.notify_all();

	NOTE_LOG("退出数据库执行线程");
}

void DBManager::ExecuteAll()
{
	if(!m_executeEngine.IsOpen())
	{
		return;
	}
	std::lock_guard<std::mutex> guard(m_sqlDequeMutex);
	UInt32 count = static_cast<UInt32>(m_sqlDeque.size());
	if(!m_sqlDeque.empty())
	{
		string startCommitSql = "start transaction;";
		m_sqlDeque.push_front(startCommitSql);
		string endCommitSql = "commit;";
		m_sqlDeque.push_back(endCommitSql);
		while (!m_sqlDeque.empty())
		{
			string sql = m_sqlDeque.front();
			if (!m_executeEngine.Execute(sql))
			{
				ERROR_LOG("%s, %d, DBEngine Process Execute sql Failed!",
					__FUNCTION__, __LINE__);
			}
			m_sqlDeque.pop_front();
		}
	}

	NOTE_LOG("执行SQL %d 条",
		count);
}

bool DBManager::ExecuteAtOnce(const string& INsql)
{
	if (!m_executeEngine.Execute(INsql))
	{
		ERROR_LOG("%s, %d, DBEngine Process Execute sql Failed!",
			__FUNCTION__, __LINE__);

		return false;
	}

	return true;
}

void DBManager::Clear()
{
	m_sqlDeque.clear();
	m_dbName = "";
}