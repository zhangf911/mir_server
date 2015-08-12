#ifndef LIBRARY_RANDOMWEIGHT_H
#define LIBRARY_RANDOMWEIGHT_H

#include "Type.h"

class RandomWeight
{
public:
	struct WeightItem
	{
		UInt32 key;
		UInt32 weight;

		WeightItem(UInt32 INkey, UInt32 INweight)
		{
			key = INkey;
			weight = INweight;
		}
	};
public:
	RandomWeight();

	~RandomWeight();

public:
	bool Empty();

	// ���Ȩ��
	void AddWeight(UInt32 INkey, UInt32 INweight);

	// ɾ��ĳ��Ȩ��
	void RemoveWeight(UInt32 INkey);

	// ���
	UInt32 GetRandomWeight();

private:
	// Ȩ��
	vector<WeightItem> m_weightVector;
};

#endif