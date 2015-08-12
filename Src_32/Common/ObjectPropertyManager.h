#ifndef COMMON_OBJECTPROPERTY_MANAGER_H
#define COMMON_OBJECTPROPERTY_MANAGER_H

#include "CommDef.h"
#include "ObjectProperty.h"

class ObjectPropertyManager
{
public:
	template<typename PropertyValue>
	bool AddObjectProperty(const string& INname, PropertyValue INvalue)
	{
		auto it = m_objectPropertyMap.find(INname);
		if(it == m_objectPropertyMap.end())
		{
			m_objectPropertyMap[INname] = ObjectProperty(INvalue);

			return true;
		}
		return false;
	};

	boost::optional<ObjectProperty&> GetObjectProperty(const string& INname)
	{
		auto it = m_objectPropertyMap.find(INname);
		if(it != m_objectPropertyMap.end())
		{
			return it->second;
		}

		return boost::none;
	};

private:
	map<string, ObjectProperty> m_objectPropertyMap;
};

#endif