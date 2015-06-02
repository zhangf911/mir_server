#include "DBEngine.h"
#include "Log.h"
#include "CommDef.h"
#include <cstdlib>
#include <stdlib.h>

DBEngine::DBEngine()
{
	m_dbConnect = NULL;
	m_result = NULL;
	m_state = NULL;
	m_db = "";
}

DBEngine::~DBEngine()
{
	delete m_state;
	delete m_dbConnect;
}

bool DBEngine::Connect(const string& INserver, unsigned short INport, const string& INuser, const string& INpassword, const string& INdb)
{
	mysql::MySQL_Driver *driver = NULL;

	// 初始化驱动
	driver = sql::mysql::get_mysql_driver_instance();
	if(!driver)
	{
		//EXCEPTION_LOG("驱动实例异常");
		return false;
	}
	//std::map<std::string, sql::ConnectPropertyVal> connection_properties;
	//connection_properties.erase("OPT_SET_CHARSET_NAME");
	//logMsg("... testing OPT_SET_CHARSET_NAME");
	//std::string charset("utf8");
	//sql::ConnectPropertyVal tmp;
	///* C-API does not care about the actual value */
	//tmp.str.val=charset.c_str();
	//tmp.str.len=charset.length();
	//connection_properties[std::string("OPT_SET_CHARSET_NAME")]=tmp;

	char intValueBuf[10] = "\0";

	string connectstring = "tcp://";
	connectstring += INserver;
	connectstring += ":";
#ifdef WIN32
	connectstring += _itoa(INport, intValueBuf, 10);
#else
	//connectstring += itoa(INport, intValueBuf, 10);
	sprintf(intValueBuf, "%d", INport);
	connectstring += intValueBuf;
#endif

	char sqllinkBuf[256] = "";
	sprintf(sqllinkBuf, "tcp://%s:%d",
		INserver.c_str(), INport);
	connectstring = sqllinkBuf;
	//DEBUG_LOG("连接字符串: %s, 用户名: %s, 密码: %s",
	//	connectstring.c_str(), INuser.c_str(), INpassword.c_str());
	m_connectstring = connectstring;
	m_user = INuser;
	m_password = INpassword;
	m_db = INdb;

	try
	{
		// 建立链接
		m_dbConnect = driver->connect(SQLString(m_connectstring.c_str())/*"tcp://192.168.0.9:3306"*/, m_user.c_str(), m_password.c_str());
		if(!m_dbConnect)
		{
			//EXCEPTION_LOG("连接异常");
			return false;
		}
		m_dbConnect->setClientOption("OPT_SET_CHARSET_NAME", "utf8");
		bool myTrue = true;  
		m_dbConnect->setClientOption("OPT_RECONNECT", &myTrue);  
	}
	catch(sql::SQLException& e)
	{
		//cout << "DBEngine::Connect Exception, ErrorCode : " << e.getErrorCode() << " Statu : " << e.getSQLState() << " Note : " << e.what() << endl;
		DEBUG_LOG("DBEngine::Connect Exception, ErrorCode : %d Statu : %s Note : %s",
			e.getErrorCode(), e.getSQLState().c_str(), e.what());
		return false;
	}
	m_state = m_dbConnect->createStatement();
	// state->execute("SET CHARSET GB2312");
	return true;
}

bool DBEngine::UseDB(const char* INdbName)
{
	char buf[40];
#ifdef WIN32
	sprintf_s(buf, 40, "use %s", INdbName);
#else
	sprintf(buf, "use %s", INdbName);
#endif
	m_state->execute(buf);

	return true;
}

bool DBEngine::CheckConnectState()
{
	mysql::MySQL_Driver *driver = NULL;

	// 初始化驱动
	driver = sql::mysql::get_mysql_driver_instance();
	if(!driver)
	{
		//EXCEPTION_LOG("驱动实例异常");
		return false;
	}

	if (m_dbConnect && m_dbConnect->isClosed())
	{
		//m_dbConnect->close();
		// 建立链接
		m_dbConnect = driver->connect(SQLString(m_connectstring.c_str())/*"tcp://192.168.0.9:3306"*/, m_user.c_str(), m_password.c_str());
		if(!m_dbConnect)
		{
			//EXCEPTION_LOG("连接异常");
			return false;
		}
		m_state->close();
		m_state = m_dbConnect->createStatement();

		UseDB(m_db.c_str());

		NOTE_LOG("数据库重新连接成功");
	}

	return true;
}

bool DBEngine::Query(const string& INsql)
{
	try
	{
		CheckConnectState();

		m_result = m_state->executeQuery(INsql);
	}
	catch(sql::SQLException& e)
	{
		//cout << "DBEngine::Query Exception : " << e.what() << endl;
		DEBUG_LOG("DBEngine::Connect Exception, ErrorCode : %d Statu : %s Note : %s",
			e.getErrorCode(), e.getSQLState().c_str(), e.what());
		return false;
	}
	
	return true;
}

bool DBEngine::Execute(const string& INsql)
{
	try
	{
		CheckConnectState();
		UInt32 count = m_state->executeUpdate(INsql);
		//return count > 0 ? true : false;
		return true;
	}
	catch(sql::SQLException& e)
	{
		//cout << "DBEngine::Query Exception : " << e.what() << endl;
		DEBUG_LOG("DBEngine::Connect Exception, ErrorCode : %d Statu : %s Note : %s",
			e.getErrorCode(), e.getSQLState().c_str(), e.what());
		return false;
	}
}

bool DBEngine::ExcuteProcedure()
{
	return true;
}

bool DBEngine::IsOpen()
{
	if(m_dbConnect == NULL)
	{
		return false;
	}
	return true;
}

bool DBEngine::CommitTransaction()
{
	return true;
}

bool DBEngine::RollbackTransaction()
{
	return true;
}

unsigned int DBEngine::GetRecordCount()
{
	return static_cast<UInt32>(m_result->rowsCount());
}

unsigned int DBEngine::GetFieldCount()
{
	// 尚未验证方法的正确性
	return 0;
}

bool DBEngine::IsEof()
{
	return m_result->isAfterLast();
}

bool DBEngine::IsBof()
{
	return m_result->isBeforeFirst();
}

bool DBEngine::IsFirst()
{
	return m_result->isFirst();
}

bool DBEngine::IsLast()
{
	return m_result->isLast();
}

bool DBEngine::MoveFirst()
{
	return m_result->first();
}

bool DBEngine::MoveNext()
{
	return m_result->next();
}

bool DBEngine::MovePrevious()
{
	return m_result->previous();
}

bool DBEngine::MoveLast()
{
	return m_result->last();
}

bool DBEngine::GetFieldValue(const char* INfieldName, char* IOvalue)
{
	*IOvalue = m_result->getInt(INfieldName);
	return true;
}

bool DBEngine::GetFieldValue(const char* INfieldName, unsigned char* IOvalue)
{
	*IOvalue = m_result->getUInt(INfieldName);
	return true;
}

bool DBEngine::GetFieldValue(const char* INfieldName, short* IOvalue)
{
	*IOvalue = m_result->getInt(INfieldName);
	return true;
}

bool DBEngine::GetFieldValue(const char* INfieldName, unsigned short* IOvalue)
{
	*IOvalue = m_result->getUInt(INfieldName);
	return true;
}

bool DBEngine::GetFieldValue(const char* INfieldName, int* IOvalue)
{
	*IOvalue = m_result->getInt(INfieldName);
	return true;
}

bool DBEngine::GetFieldValue(const char* INfieldName, unsigned int* IOvalue)
{
	*IOvalue = m_result->getUInt(INfieldName);
	return true;
}

bool DBEngine::GetFieldValue(const char* INfieldName, long* IOvalue)
{
	*IOvalue = m_result->getInt(INfieldName);
	return true;
}

bool DBEngine::GetFieldValue(const char* INfieldName, unsigned long* IOvalue)
{
	*IOvalue = m_result->getUInt(INfieldName);
	return true;
}

#ifdef WIN32
bool DBEngine::GetFieldValue(const char* INfieldName, __int64* IOvalue)
{
	*IOvalue = m_result->getInt64(INfieldName);
	return true;
}
#else
bool DBEngine::GetFieldValue(const char* INfieldName, long long* IOvalue)
{
	*IOvalue = m_result->getInt64(INfieldName);
	return true;
}
#endif

#ifdef WIN32
bool DBEngine::GetFieldValue(const char* INfieldName, unsigned __int64* IOvalue)
{
	*IOvalue = m_result->getUInt64(INfieldName);
	return true;
}
#else
bool DBEngine::GetFieldValue(const char* INfieldName, unsigned long long* IOvalue)
{
	*IOvalue = m_result->getUInt64(INfieldName);
	return true;
}
#endif

bool DBEngine::GetFieldValue(const char* INfieldName, char*& IOvalue, unsigned int* IOlength)
{
	SQLString ret = m_result->getString(INfieldName).c_str();
	IOvalue = new char[ret->size() + 1];
	memcpy(IOvalue, ret->c_str(), ret->size());
	IOvalue[ret->size()] = '\0';
	*IOlength = static_cast<UInt32>(ret->size());
	return true;
}

bool DBEngine::GetFieldValue(const char* INfieldName, string& IOvalue)
{
	IOvalue = m_result->getString(INfieldName).c_str();
	return true;
}
