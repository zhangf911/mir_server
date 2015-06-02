#ifndef COMMON_OBJECT_PROPERTY_H
#define COMMON_OBJECT_PROPERTY_H

#include "CommDef.h"
#include <boost/any.hpp>
#include <boost/variant.hpp>
#include <functional>

class ObjectProperty
{
public:
	typedef std::function<void(ObjectProperty&)> PropertyCallBack;
public:
	ObjectProperty(bool INvalue) : m_value(INvalue){};

	ObjectProperty(int INvalue) : m_value(INvalue) {};

	ObjectProperty(float INvalue) : m_value(INvalue) {};

	ObjectProperty(const string& INvalue) : m_value(INvalue) {};

public:
	template <typename T>
	void Set(T INvalue)
	{
		auto value_type = m_value.type();
		m_value = INvalue;

		OnValueChange();
	};

	void OnValueChange();

	void RegisterCallBack(PropertyCallBack INcallBack);

public:
	bool AsBool(){ return boost::get<bool>(m_value); };

	int AsInt(){ return boost::get<int>(m_value); };

	float AsFloat(){ return boost::get<float>(m_value); };

	string AsString(){ return boost::get<std::string>(m_value); };
private:
	boost::variant<bool, int, float, string> m_value;
	list<PropertyCallBack> m_callbackList;
};

#endif