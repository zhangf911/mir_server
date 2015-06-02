#ifndef GAMESERVER_DB_OBJECT_H_
#define GAMESERVER_DB_OBJECT_H_

#include "Type.h"
#include "json/json.h"

class JsonDB
{
public:
	JsonDB()
	{
		m_DBObject.clear();
	}
	~JsonDB(){}


	void				LoadFromDatabase(string INtableName, string INkey);
	void				LoadFromDatabase(string INtableName, UInt32 INkey);

	void				PackageSqlList(string INtableName, UInt32 INkey, list<string>& INsqlStringList);	
	Json::Value			m_DBObject;

};
#endif