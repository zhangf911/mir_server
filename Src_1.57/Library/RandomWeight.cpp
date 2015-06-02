#include "RandomWeight.h"
#include "Random.h"

RandomWeight::RandomWeight()
{
	m_weightVector.clear();
}

RandomWeight::~RandomWeight()
{
	m_weightVector.clear();
}

bool RandomWeight::Empty()
{
	return m_weightVector.empty();
}

void RandomWeight::AddWeight(UInt32 INkey, UInt32 INweight)
{
	m_weightVector.push_back(WeightItem(INkey, INweight));
}

void RandomWeight::RemoveWeight(UInt32 INkey)
{
	for(auto it = m_weightVector.begin(); it != m_weightVector.end(); ++it)
	{
		if(it->key == INkey)
		{
			m_weightVector.erase(it);
			break;
		}
	}
}

UInt32 RandomWeight::GetRandomWeight()
{
	UInt32 totalWeight = 0;
	for(auto it = m_weightVector.begin(); it != m_weightVector.end(); ++it)
	{
		totalWeight += it->weight;
	}

	vector<WeightItem> cdf = m_weightVector;
	for(UInt32 i = 1; i < cdf.size(); ++i)
	{
		cdf[i].weight += cdf[i - 1].weight;
	}

	UInt32 weight = Library::RandomNumber::GetRandom(0, totalWeight - 1);

	for(UInt32 i = 0; i < cdf.size(); ++i)
	{
		if(weight < cdf[i].weight)
		{
			return cdf[i].key;
		}
	}

	return 0;
}