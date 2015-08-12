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

	// 添加权重
	void AddWeight(UInt32 INkey, UInt32 INweight);

	// 删除某个权重
	void RemoveWeight(UInt32 INkey);

	// 随机
	UInt32 GetRandomWeight();

private:
	// 权重
	vector<WeightItem> m_weightVector;
};

#endif