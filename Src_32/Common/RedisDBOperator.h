#ifndef GAMESERVER_REDISDBOPERATOR_H
#define GAMESERVER_REDISDBOPERATOR_H

#include "Type.h"
#include "redisclient.h"

class RedisDBOperator
{
public:
	RedisDBOperator();

	~RedisDBOperator();

public:
	// 初始化
	bool Initial(const string& INhost, UInt16 INport);

	// 切换仓库
	void ChangeRepertory(UInt32 INindex);

	// 设置键值
	void Set(const string& INkey, const string& INvalue);

	// 获取键值
	string Get(const string& INkey);
	
	// 检查键值是否存在
	bool CheckIsExists(const string& INkey);

	// 模式匹配获取key列表
	UInt32 GetKeys(const string& INkey, vector<string>& OUTkeyVector);

	// 设置新的键值同时获取老的键值
	string GetSet(const string& INkey, const string& INvalue);

	// 批量获取
	void MultiGet(const vector<string>& INkeyVector, vector<string>& OUTvalueVector);

	// 设置键值仅当key不存在时
	bool SetNX(const string& INkey, const string& INvalue);

	// 自增键值
	Int32 Incr(const string& INkey);

	// 自减键值
	Int32 Decr(const string& INkey);

	// 增加键值
	Int32 IncrBy(const string& INkey, UInt32 INnumber);

	// 减少键值
	Int32 DecrBy(const string& INkey, UInt32 INnumber);

	// 删除键
	bool Del(const string& INkey);

	// 获取键类型
	UInt32 GetType(const string& INkey);

	// 获取随机键
	string GetRandomKey();

	// 重置键名
	void Rename(const string& INkey, const string& INnewKey);

	// 重置键名仅当新的键名不存在
	void RenameNX(const string& INkey, const string& INnewKey);

	// 获取当前仓库键数量
	UInt32 GetKeyCount();

	// 设置键剩余时间
	void SetKeyRemainTime(const string& INkey, UInt32 INsecond);

	// 转移键值,index 仓库索引号，当键重复时会抛异常
	void Move(const string& INkey, UInt32 INindex);
	
	// 插入Set集
	void InsertToSet(const string& INkey, const string& INvalue);

	// 对键值排序并获取（增序）
	void SortAscending(const string& INkey, vector<string>& OUTvalueVector);

	// 对键值排序并获取（减序）
	void SortDescending(const string& INkey, vector<string>& OUTvalueVector);

	// 加入键值列表队尾
	Int32 PushBack(const string& INkey, const string& INvalue);

	// 加入键值列表队头
	Int32 PushFront(const string& INkey, const string& INvalue);

	// 获取列表数量
	Int32 GetListSize(const string& INkey);

	// 获取列表第index个值 -1表示最后一个
	string GetListIndexValue(const string& INkey, Int32 INindex);

	// 遍历,返回获取 -1表示最后一个
	Int32 GetRangeValue(const string& INkey, Int32 INstartIndex, Int32 INendIndex, vector<string>& OUTvalueVector);

	// 获取list类型键值
	Int32 GetList(const string& INkey, vector<string>& OUTvalueVector);

	// 裁剪list类型键值 -1表示最后一个
	void TrimList(const string& INkey, Int32 INstartIndex, Int32 INendIndex);

	// 设置列表中第index值
	void SetListIndexValue(const string& INkey, Int32 INindex, const string& INvalue);

	// 从列表中删除（大于0，从左开始删除；小于0，则从右边开始删除）
	Int32 DeleteFromList(const string& INkey, Int32 INcount, const string& INvalue);

	// 从列表头删除
	string PopFront(const string& INkey);

	// 从列表尾删除
	string PopBack(const string& INkey);

	// 集合添加
	void AddToSet(const string& INkey, const string& INvalue);

	// 集合删除
	void DeleteFromSet(const string& INkey, const string& INvalue);

	// 检测是否在集合中
	bool IsSetMember(const string& INkey, const string& INvalue);
	
	// 集合元素移动
	void SetMemberMove(const string& INkey, const string& INtargetKey, const string& INvalue);

	// 获取集合成员数量
	Int32 GetSetMemberCount(const string& INkey);

	// 获取集合所有成员
	Int32 GetSetMember(const string& INkey, set<string>& OUTvalueSet);

	// 集合交集
	Int32 GetSetIntersection(const vector<string>& INkeyVector, set<string>& OUTvalueSet);

	// 集合交集存储到新的集合中
	Int32 SetSetIntersection(const string& INkey, const vector<string>& INkeyVector);

	// 合并集合
	Int32 MergeSet(const vector<string>& INkeyVector, set<string>& OUTvalueSet);

	// 集合合并到新的集合中
	Int32 MergeSet(const string& INkey, const vector<string>& INkeyVector);

	// 添加到排序的集合中，如果已经存在则更新
	void AddToSortedSet(const string& INkey, double INscore, const string& INvalue);

	// 从已排序的集合中删除
	void DeleteFromSortedSet(const string& INkey, const string& INvalue);

	// 获取已排序集合的成员数量
	Int32 GetSortedSetMemberCount(const string& INkey);

	// 增加已排序集合成员的值
	double IncrSortedSetBy(const string& INkey, const string& INvalue, Int32 INscore);

	// 获取已排序集合成员的值
	double GetSortedSetScore(const string& INkey, const string& INvalue);

	// 获取元素在已排序集合中的次序
	Int32 GetIndexInSortedSet(const string& INkey, const string& INvalue);

	// 获取元素在已排序集合中的次序，集合score从高到低排序
	Int32 GetHighIndexInSortedSet(const string& INkey, const string& INvalue);

	// 遍历已排序集合
	void GetSortedSetRange(const string& INkey, Int32 INstartIndex, Int32 INendIndex, vector<string>& OUTvalueVector);

	// 逆序遍历已排序集合
	void GetSortedSetRevRange(const string& INkey, Int32 INstartIndex, Int32 INendIndex, vector<string>& OUTvalueVector);

	// 根据积分遍历已排序集合 INFINITY 无穷大
	void GetSortedSetRangeByScore(const string& INkey, double INstartScore, double INendScore, vector<string>& OUTvalueVector);

	// 获取指定积分值范围内元素数量 INexclue 是否半区间，即是否包含上限或下限
	Int32 GetSortedSetRangeMemberCount(const string& INkey, double INstartScore, double INendScore, UInt32 INexclude);

	// 从已排序集合中批量移除指定范围内的index
	Int32 MultiRemoveFromSortedSetByIndex(const string& INkey, Int32 INstartIndex, Int32 INendIndex);

	// 从已排序集合中批量移除指定范围内的score
	Int32 MultiRemoveFromSortedSetByScore(const string& INkey, double INstartScore, double INendScore);

	// 从已排序集合中批量移除指定范围内的score
	Int32 MultiRemoveFromSortedSetByScoreFromMin(const string& INkey, double INendScore);

	// 从已排序集合中批量移除指定范围内的score
	Int32 MultiRemoveFromSortedSetByScoreToMax(const string& INkey, double INstartScore);

	// 合并已排序集合
	Int32 MergeSortedSet(const string& INkey, const vector<string>& INkeyVector);

	// 设置已排序集合的交集到新的集合中
	Int32 SetSortedSetIntersection(const string& INkey, const vector<string>& INkeyVector);

	// 添加到哈希表
	bool AddToHash(const string& INkey, const string& INhashKey, const string& INvalue);

	// 获取哈希表元素数量
	Int32 GetHashMemberCount(const string& INkey);

	// 获取哈希元素值
	string GetHashMember(const string& INkey, const string& INhashKey);

	// 设置哈希元素值，仅当哈希键不存在时
	bool SetHashMember(const string& INkey, const string& INhashKey, const string& INvalue);

	// 批量添加哈希键值对
	void MultiAddHashMember(const string& INkey, const vector<std::pair<string, string>>& INpairVector);

	// 批量获取哈希值
	void MultiGetHashMember(const string& INkey, const vector<string>& INhashKeyVector, vector<string>& OUTvalueVector);

	// 增加哈希元素值
	Int32 IncrHashMemberBy(const string& INkey, const string& INhashKey, Int32 INvalue);

	// 检测是否有哈希键
	bool CheckHasHashMember(const string& INkey, const string& INhaskKey);

	// 删除哈希键
	bool DeleteHashMember(const string& INkey, const string& INhashKey);

	// 获取所有哈希键
	void GetAllHashKey(const string& INkey, vector<string>& INhashKeyVector);

	// 获取所有哈希键值
	void GetAllHashValue(const string& INkey, vector<string>& INhashValueVector);

	// 获取所有所有哈希键值
	void GetAllHashKV(const string& INkey, vector<std::pair<string, string>>& OUTpairVector);

public:
	// 保存数据
	void Save();
	
	// 异步保存
	void BGSave();

	// 获取上次保存时间
	time_t GetLastSaveTime();

	// 关闭服务器
	void ShutDown();
public:
	// 输出redis server信息
	void PrintRedisClientInfo();

private:
	// 连接
	redis::client* m_redisClient;
};

#endif