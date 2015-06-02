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
* @brief ���ݿ��������
**/
class DBEngine
{
private:
	/** ���ݿ����� **/
	Connection* m_dbConnect;
	/**  **/
	Statement* m_state;
	/** ��¼�� **/
	ResultSet* m_result;
	/** �����ַ��� **/
	string m_connectstring;
	/** �û��� **/
	string m_user;
	/** ���� **/
	string m_password;
	// ���ݿ���
	string m_db;
public:
	/**
	* @brief ���캯��
	**/
	DBEngine();

	/**
	* @brief ��������
	**/
	~DBEngine();

public:
	/**
	* @brief �������ݿ�
	* @param INserver : ��������ַ
	* @param INport : �˿�
	* @param INuser : �û���
	* @param INpassword : ����
	**/
	bool Connect(const string& INserver, unsigned short INport, const string& INuser, const string& INpassword, const string& INdb);

	/**
	* @brief ʹ�����ݿ�
	**/
	bool UseDB(const char* INdbName);

	// ����
	bool CheckConnectState();

	/**
	* @brief ִ�в�ѯ���
	* @
	**/
	bool Query(const string& INsql);

	/**
	* @brief ִ�в��롢ɾ�������²�ѯ
	**/
	bool Execute(const string& INsql);

	/**
	* @brief ִ�д洢����
	**/
	bool ExcuteProcedure();

	/**
	* @brief �ر�����
	**/
	void Close();

	/**
	* @brief �Ƿ��Ѵ�����
	**/
	bool IsOpen();

	// ������
public:
	/**
	* @brief �ύ����
	**/
	bool CommitTransaction();

	/**
	* @brief �ع�����
	**/
	bool RollbackTransaction();

	// ��¼�����ӿ�
public:
	/**
	* @brief ��ȡ��¼��
	**/
	unsigned int GetRecordCount();

	/**
	* @brief ��ȡ�ֶ���
	**/
	unsigned int GetFieldCount();

	/**
	* @brief ��ǰλ���Ƿ�û�м�¼��
	**/
	bool IsEof();
	
	/**
	* @brief ��ǰλ���Ƿ��Ǽ�¼��
	**/
	bool IsBof();
		
	/**
	* @brief ��ǰλ���Ƿ����׸���¼
	**/
	bool IsFirst();
		
	/**
	* @brief ��ǰλ���Ƿ������һ����¼
	**/
	bool IsLast();

	/**
	* @brief �ƶ�����������һ����¼
	**/
	bool MoveFirst();

	/**
	* @brief �ƶ�����������һ����¼
	**/
	bool MoveNext();
	
	/**
	* @brief �ƶ�����������һ����¼
	**/
	bool MovePrevious();
	
	/**
	* @brief �ƶ�������������¼
	**/
	bool MoveLast();

	/**
	* @brief ��ȡ�з����ַ����ֶ�ֵ
	* @param IOvalue : �ֶ�ֵ
	* @note  ִ�гɹ����ֶ�ֵ�洢��IOvalue������
	**/
	bool GetFieldValue(const char* INfieldName, char* IOvalue);
	
	/**
	* @brief ��ȡ�޷����ַ����ֶ�ֵ
	* @param IOvalue : �ֶ�ֵ
	* @note  ִ�гɹ����ֶ�ֵ�洢��IOvalue������
	**/
	bool GetFieldValue(const char* INfieldName, unsigned char* IOvalue);
	
	/**
	* @brief ��ȡ�з��Ŷ������ֶ�ֵ
	* @param IOvalue : �ֶ�ֵ
	* @note  ִ�гɹ����ֶ�ֵ�洢��IOvalue������
	**/
	bool GetFieldValue(const char* INfieldName, short* IOvalue);
	
	/**
	* @brief ��ȡ�޷��Ŷ������ֶ�ֵ
	* @param IOvalue : �ֶ�ֵ
	* @note  ִ�гɹ����ֶ�ֵ�洢��IOvalue������
	**/
	bool GetFieldValue(const char* INfieldName, unsigned short* IOvalue);
	
	/**
	* @brief ��ȡ�з��������ֶ�ֵ
	* @param IOvalue : �ֶ�ֵ
	* @note  ִ�гɹ����ֶ�ֵ�洢��IOvalue������
	**/
	bool GetFieldValue(const char* INfieldName, int* IOvalue);
	
	/**
	* @brief ��ȡ�޷��������ֶ�ֵ
	* @param IOvalue : �ֶ�ֵ
	* @note  ִ�гɹ����ֶ�ֵ�洢��IOvalue������
	**/
	bool GetFieldValue(const char* INfieldName, unsigned int* IOvalue);
	
	/**
	* @brief ��ȡ�з��ų������ֶ�ֵ
	* @param IOvalue : �ֶ�ֵ
	* @note  ִ�гɹ����ֶ�ֵ�洢��IOvalue������
	**/
	bool GetFieldValue(const char* INfieldName, long* IOvalue);
	
	/**
	* @brief ��ȡ�޷��ų������ֶ�ֵ
	* @param IOvalue : �ֶ�ֵ
	* @note  ִ�гɹ����ֶ�ֵ�洢��IOvalue������
	**/
	bool GetFieldValue(const char* INfieldName, unsigned long* IOvalue);
	
	/**
	* @brief ��ȡ64λ�з��������ֶ�ֵ
	* @param IOvalue : �ֶ�ֵ
	* @note  ִ�гɹ����ֶ�ֵ�洢��IOvalue������
	**/
#ifdef WIN32
	bool GetFieldValue(const char* INfieldName, __int64* IOvalue);
#else
	bool GetFieldValue(const char* INfieldName, long long* IOvalue);
#endif

	/**
	* @brief ��ȡ64λ�޷��������ֶ�ֵ
	* @param IOvalue : �ֶ�ֵ
	* @note  ִ�гɹ����ֶ�ֵ�洢��IOvalue������
	**/
#ifdef WIN32
	bool GetFieldValue(const char* INfieldName, unsigned __int64* IOvalue);
#else
	bool GetFieldValue(const char* INfieldName, unsigned long long* IOvalue);
#endif

	/**
	* @brief ��ȡ�ַ����ֶ�ֵ
	* @param IOvalue : �ֶ�ֵ
	* @note  ִ�гɹ����ֶ�ֵ�洢��IOvalue������
	**/
	bool GetFieldValue(const char* INfieldName, char*& IOvalue, unsigned int* IOlength);
	
	/**
	* @brief ��ȡ�ַ����ֶ�ֵ
	* @param IOvalue : �ֶ�ֵ
	* @note  ִ�гɹ����ֶ�ֵ�洢��IOvalue������
	**/
	bool GetFieldValue(const char* INfieldName, string& IOvalue);
	
	/**
	* @brief ��ȡ���������ֶ�ֵ
	* @param IOvalue : �ֶ�ֵ
	* @note  ִ�гɹ����ֶ�ֵ�洢��IOvalue������
	**/
	//bool GetFieldValue(const char* INfieldName, DataTime* IOvalue);

};

#endif