#include "ObjectProperty.h"
#include <algorithm>

void ObjectProperty::OnValueChange()
{
	std::for_each(std::begin(m_callbackList), std::end(m_callbackList), [this](PropertyCallBack INcallBack){
		INcallBack(*this);
	});
}

void ObjectProperty::RegisterCallBack(PropertyCallBack INcallBack)
{
	m_callbackList.push_back(INcallBack);
}