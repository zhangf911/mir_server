#ifndef LIBRARY_DBENGINE_H
#define LIBRARY_DBENGINE_H

#include "mysql_connection.h"
#include "mysql_driver.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"

using namespace sql;

#include <string>
using std::string;

/**
* @brief 数据库访问引擎
**/
class DBEngine
{
private:
	/** 数据库连接 **/
	Connection* m_dbConnect;
	/**  **/
	Statement* m_state;
	/** 记录集 **/
	ResultSet* m_result;
	/** 连接字符串 **/
	string m_connectstring;
	/** 用户名 **/
	string m_user;
	/** 密码 **/
	string m_password;
	// 数据库名
	string m_db;
public:
	/**
	* @brief 构造函数
	**/
	DBEngine();

	/**
	* @brief 析构函数
	**/
	~DBEngine();

public:
	/**
	* @brief 连接数据库
	* @param INserver : 服务器地址
	* @param INport : 端口
	* @param INuser : 用户名
	* @param INpassword : 密码
	**/
	bool Connect(const string& INserver, unsigned short INport, const string& INuser, const string& INpassword, const string& INdb);

	/**
	* @brief 使用数据库
	**/
	bool UseDB(const char* INdbName);

	// 重连
	bool CheckConnectState();

	/**
	* @brief 执行查询语句
	* @
	**/
	bool Query(const string& INsql);

	/**
	* @brief 执行插入、删除、更新查询
	**/
	bool Execute(const string& INsql);

	/**
	* @brief 执行存储过程
	**/
	bool ExcuteProcedure();

	/**
	* @brief 关闭连接
	**/
	void Close();

	/**
	* @brief 是否已打开连接
	**/
	bool IsOpen();

	// 事务处理
public:
	/**
	* @brief 提交事务
	**/
	bool CommitTransaction();

	/**
	* @brief 回滚事务
	**/
	bool RollbackTransaction();

	// 记录操作接口
public:
	/**
	* @brief 获取记录数
	**/
	unsigned int GetRecordCount();

	/**
	* @brief 获取字段数
	**/
	unsigned int GetFieldCount();

	/**
	* @brief 当前位置是否没有记录了
	**/
	bool IsEof();
	
	/**
	* @brief 当前位置是否是记录底
	**/
	bool IsBof();
		
	/**
	* @brief 当前位置是否是首个记录
	**/
	bool IsFirst();
		
	/**
	* @brief 当前位置是否是最后一个记录
	**/
	bool IsLast();

	/**
	* @brief 移动迭代器到第一条记录
	**/
	bool MoveFirst();

	/**
	* @brief 移动迭代器到下一条记录
	**/
	bool MoveNext();
	
	/**
	* @brief 移动迭代器到上一条记录
	**/
	bool MovePrevious();
	
	/**
	* @brief 移动迭代器到最后记录
	**/
	bool MoveLast();

	/**
	* @brief 获取有符号字符型字段值
	* @param IOvalue : 字段值
	* @note  执行成功则将字段值存储到IOvalue参数中
	**/
	bool GetFieldValue(const char* INfieldName, char* IOvalue);
	
	/**
	* @brief 获取无符号字符型字段值
	* @param IOvalue : 字段值
	* @note  执行成功则将字段值存储到IOvalue参数中
	**/
	bool GetFieldValue(const char* INfieldName, unsigned char* IOvalue);
	
	/**
	* @brief 获取有符号短整型字段值
	* @param IOvalue : 字段值
	* @note  执行成功则将字段值存储到IOvalue参数中
	**/
	bool GetFieldValue(const char* INfieldName, short* IOvalue);
	
	/**
	* @brief 获取无符号短整型字段值
	* @param IOvalue : 字段值
	* @note  执行成功则将字段值存储到IOvalue参数中
	**/
	bool GetFieldValue(const char* INfieldName, unsigned short* IOvalue);
	
	/**
	* @brief 获取有符号整型字段值
	* @param IOvalue : 字段值
	* @note  执行成功则将字段值存储到IOvalue参数中
	**/
	bool GetFieldValue(const char* INfieldName, int* IOvalue);
	
	/**
	* @brief 获取无符号整型字段值
	* @param IOvalue : 字段值
	* @note  执行成功则将字段值存储到IOvalue参数中
	**/
	bool GetFieldValue(const char* INfieldName, unsigned int* IOvalue);
	
	/**
	* @brief 获取有符号长整型字段值
	* @param IOvalue : 字段值
	* @note  执行成功则将字段值存储到IOvalue参数中
	**/
	bool GetFieldValue(const char* INfieldName, long* IOvalue);
	
	/**
	* @brief 获取无符号长整型字段值
	* @param IOvalue : 字段值
	* @note  执行成功则将字段值存储到IOvalue参数中
	**/
	bool GetFieldValue(const char* INfieldName, unsigned long* IOvalue);
	
	/**
	* @brief 获取64位有符号整型字段值
	* @param IOvalue : 字段值
	* @note  执行成功则将字段值存储到IOvalue参数中
	**/
#ifdef WIN32
	bool GetFieldValue(const char* INfieldName, __int64* IOvalue);
#else
	bool GetFieldValue(const char* INfieldName, long long* IOvalue);
#endif

	/**
	* @brief 获取64位无符号整型字段值
	* @param IOvalue : 字段值
	* @note  执行成功则将字段值存储到IOvalue参数中
	**/
#ifdef WIN32
	bool GetFieldValue(const char* INfieldName, unsigned __int64* IOvalue);
#else
	bool GetFieldValue(const char* INfieldName, unsigned long long* IOvalue);
#endif

	/**
	* @brief 获取字符串字段值
	* @param IOvalue : 字段值
	* @note  执行成功则将字段值存储到IOvalue参数中
	**/
	bool GetFieldValue(const char* INfieldName, char*& IOvalue, unsigned int* IOlength);
	
	/**
	* @brief 获取字符串字段值
	* @param IOvalue : 字段值
	* @note  执行成功则将字段值存储到IOvalue参数中
	**/
	bool GetFieldValue(const char* INfieldName, string& IOvalue);
	
	/**
	* @brief 获取日期类型字段值
	* @param IOvalue : 字段值
	* @note  执行成功则将字段值存储到IOvalue参数中
	**/
	//bool GetFieldValue(const char* INfieldName, DataTime* IOvalue);

};

#endif