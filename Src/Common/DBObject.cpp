#include "DBObject.h"
#include "DBEngine.h"
#include "CommDef.h"
#include "json/json.h"
#include "DBManager.h"

void JsonDB::LoadFromDatabase(string INtableName, string INkey)
{
	m_DBObject.clear();

	string sql ="select * from " + INtableName + " where ID = '" + INkey + "';";

	string data;
	UInt32 recordCount = DBQueryHelper::QueryHandler(sql, [this, &data](DBEngine& INdbEngine){
		INdbEngine.GetFieldValue("Data", data);
	});

	Json::Reader reader;
	reader.parse(data.c_str(), m_DBObject);
}

void JsonDB::LoadFromDatabase(string INtableName, UInt32 INkey)
{
	m_DBObject.clear();

	string sqlformat = "select * from %s where ID = %d;";
	char sqlbuf[256] = "\0";
	sprintf(sqlbuf, sqlformat.c_str(), INtableName.c_str(), INkey);

	string data;
	UInt32 recordCount = DBQueryHelper::QueryHandler(sqlbuf, [this, &data](DBEngine& INdbEngine){
		INdbEngine.GetFieldValue("Data", data);
	});

	Json::Reader reader;
	reader.parse(data.c_str(), m_DBObject);
}

void JsonDB::PackageSqlList(string INtableName, UInt32 INkey, list<string>& INsqlStringList )
{
	Json::FastWriter write;
	std::string fieldVal = write.write(m_DBObject);
	string sql = "insert into " + INtableName + " (ID, Data) values(" + std::to_string(INkey) + ",'"+ fieldVal + "')on duplicate key update Data='" + fieldVal + "'";
	INsqlStringList.push_back( std::move(sql));
}