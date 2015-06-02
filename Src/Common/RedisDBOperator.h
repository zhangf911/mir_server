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
	// ��ʼ��
	bool Initial(const string& INhost, UInt16 INport);

	// �л��ֿ�
	void ChangeRepertory(UInt32 INindex);

	// ���ü�ֵ
	void Set(const string& INkey, const string& INvalue);

	// ��ȡ��ֵ
	string Get(const string& INkey);
	
	// ����ֵ�Ƿ����
	bool CheckIsExists(const string& INkey);

	// ģʽƥ���ȡkey�б�
	UInt32 GetKeys(const string& INkey, vector<string>& OUTkeyVector);

	// �����µļ�ֵͬʱ��ȡ�ϵļ�ֵ
	string GetSet(const string& INkey, const string& INvalue);

	// ������ȡ
	void MultiGet(const vector<string>& INkeyVector, vector<string>& OUTvalueVector);

	// ���ü�ֵ����key������ʱ
	bool SetNX(const string& INkey, const string& INvalue);

	// ������ֵ
	Int32 Incr(const string& INkey);

	// �Լ���ֵ
	Int32 Decr(const string& INkey);

	// ���Ӽ�ֵ
	Int32 IncrBy(const string& INkey, UInt32 INnumber);

	// ���ټ�ֵ
	Int32 DecrBy(const string& INkey, UInt32 INnumber);

	// ɾ����
	bool Del(const string& INkey);

	// ��ȡ������
	UInt32 GetType(const string& INkey);

	// ��ȡ�����
	string GetRandomKey();

	// ���ü���
	void Rename(const string& INkey, const string& INnewKey);

	// ���ü��������µļ���������
	void RenameNX(const string& INkey, const string& INnewKey);

	// ��ȡ��ǰ�ֿ������
	UInt32 GetKeyCount();

	// ���ü�ʣ��ʱ��
	void SetKeyRemainTime(const string& INkey, UInt32 INsecond);

	// ת�Ƽ�ֵ,index �ֿ������ţ������ظ�ʱ�����쳣
	void Move(const string& INkey, UInt32 INindex);
	
	// ����Set��
	void InsertToSet(const string& INkey, const string& INvalue);

	// �Լ�ֵ���򲢻�ȡ������
	void SortAscending(const string& INkey, vector<string>& OUTvalueVector);

	// �Լ�ֵ���򲢻�ȡ������
	void SortDescending(const string& INkey, vector<string>& OUTvalueVector);

	// �����ֵ�б��β
	Int32 PushBack(const string& INkey, const string& INvalue);

	// �����ֵ�б��ͷ
	Int32 PushFront(const string& INkey, const string& INvalue);

	// ��ȡ�б�����
	Int32 GetListSize(const string& INkey);

	// ��ȡ�б��index��ֵ -1��ʾ���һ��
	string GetListIndexValue(const string& INkey, Int32 INindex);

	// ����,���ػ�ȡ -1��ʾ���һ��
	Int32 GetRangeValue(const string& INkey, Int32 INstartIndex, Int32 INendIndex, vector<string>& OUTvalueVector);

	// ��ȡlist���ͼ�ֵ
	Int32 GetList(const string& INkey, vector<string>& OUTvalueVector);

	// �ü�list���ͼ�ֵ -1��ʾ���һ��
	void TrimList(const string& INkey, Int32 INstartIndex, Int32 INendIndex);

	// �����б��е�indexֵ
	void SetListIndexValue(const string& INkey, Int32 INindex, const string& INvalue);

	// ���б���ɾ��������0������ʼɾ����С��0������ұ߿�ʼɾ����
	Int32 DeleteFromList(const string& INkey, Int32 INcount, const string& INvalue);

	// ���б�ͷɾ��
	string PopFront(const string& INkey);

	// ���б�βɾ��
	string PopBack(const string& INkey);

	// �������
	void AddToSet(const string& INkey, const string& INvalue);

	// ����ɾ��
	void DeleteFromSet(const string& INkey, const string& INvalue);

	// ����Ƿ��ڼ�����
	bool IsSetMember(const string& INkey, const string& INvalue);
	
	// ����Ԫ���ƶ�
	void SetMemberMove(const string& INkey, const string& INtargetKey, const string& INvalue);

	// ��ȡ���ϳ�Ա����
	Int32 GetSetMemberCount(const string& INkey);

	// ��ȡ�������г�Ա
	Int32 GetSetMember(const string& INkey, set<string>& OUTvalueSet);

	// ���Ͻ���
	Int32 GetSetIntersection(const vector<string>& INkeyVector, set<string>& OUTvalueSet);

	// ���Ͻ����洢���µļ�����
	Int32 SetSetIntersection(const string& INkey, const vector<string>& INkeyVector);

	// �ϲ�����
	Int32 MergeSet(const vector<string>& INkeyVector, set<string>& OUTvalueSet);

	// ���Ϻϲ����µļ�����
	Int32 MergeSet(const string& INkey, const vector<string>& INkeyVector);

	// ��ӵ�����ļ����У�����Ѿ����������
	void AddToSortedSet(const string& INkey, double INscore, const string& INvalue);

	// ��������ļ�����ɾ��
	void DeleteFromSortedSet(const string& INkey, const string& INvalue);

	// ��ȡ�����򼯺ϵĳ�Ա����
	Int32 GetSortedSetMemberCount(const string& INkey);

	// ���������򼯺ϳ�Ա��ֵ
	double IncrSortedSetBy(const string& INkey, const string& INvalue, Int32 INscore);

	// ��ȡ�����򼯺ϳ�Ա��ֵ
	double GetSortedSetScore(const string& INkey, const string& INvalue);

	// ��ȡԪ���������򼯺��еĴ���
	Int32 GetIndexInSortedSet(const string& INkey, const string& INvalue);

	// ��ȡԪ���������򼯺��еĴ��򣬼���score�Ӹߵ�������
	Int32 GetHighIndexInSortedSet(const string& INkey, const string& INvalue);

	// ���������򼯺�
	void GetSortedSetRange(const string& INkey, Int32 INstartIndex, Int32 INendIndex, vector<string>& OUTvalueVector);

	// ������������򼯺�
	void GetSortedSetRevRange(const string& INkey, Int32 INstartIndex, Int32 INendIndex, vector<string>& OUTvalueVector);

	// ���ݻ��ֱ��������򼯺� INFINITY �����
	void GetSortedSetRangeByScore(const string& INkey, double INstartScore, double INendScore, vector<string>& OUTvalueVector);

	// ��ȡָ������ֵ��Χ��Ԫ������ INexclue �Ƿ�����䣬���Ƿ�������޻�����
	Int32 GetSortedSetRangeMemberCount(const string& INkey, double INstartScore, double INendScore, UInt32 INexclude);

	// �������򼯺��������Ƴ�ָ����Χ�ڵ�index
	Int32 MultiRemoveFromSortedSetByIndex(const string& INkey, Int32 INstartIndex, Int32 INendIndex);

	// �������򼯺��������Ƴ�ָ����Χ�ڵ�score
	Int32 MultiRemoveFromSortedSetByScore(const string& INkey, double INstartScore, double INendScore);

	// �������򼯺��������Ƴ�ָ����Χ�ڵ�score
	Int32 MultiRemoveFromSortedSetByScoreFromMin(const string& INkey, double INendScore);

	// �������򼯺��������Ƴ�ָ����Χ�ڵ�score
	Int32 MultiRemoveFromSortedSetByScoreToMax(const string& INkey, double INstartScore);

	// �ϲ������򼯺�
	Int32 MergeSortedSet(const string& INkey, const vector<string>& INkeyVector);

	// ���������򼯺ϵĽ������µļ�����
	Int32 SetSortedSetIntersection(const string& INkey, const vector<string>& INkeyVector);

	// ��ӵ���ϣ��
	bool AddToHash(const string& INkey, const string& INhashKey, const string& INvalue);

	// ��ȡ��ϣ��Ԫ������
	Int32 GetHashMemberCount(const string& INkey);

	// ��ȡ��ϣԪ��ֵ
	string GetHashMember(const string& INkey, const string& INhashKey);

	// ���ù�ϣԪ��ֵ��������ϣ��������ʱ
	bool SetHashMember(const string& INkey, const string& INhashKey, const string& INvalue);

	// ������ӹ�ϣ��ֵ��
	void MultiAddHashMember(const string& INkey, const vector<std::pair<string, string>>& INpairVector);

	// ������ȡ��ϣֵ
	void MultiGetHashMember(const string& INkey, const vector<string>& INhashKeyVector, vector<string>& OUTvalueVector);

	// ���ӹ�ϣԪ��ֵ
	Int32 IncrHashMemberBy(const string& INkey, const string& INhashKey, Int32 INvalue);

	// ����Ƿ��й�ϣ��
	bool CheckHasHashMember(const string& INkey, const string& INhaskKey);

	// ɾ����ϣ��
	bool DeleteHashMember(const string& INkey, const string& INhashKey);

	// ��ȡ���й�ϣ��
	void GetAllHashKey(const string& INkey, vector<string>& INhashKeyVector);

	// ��ȡ���й�ϣ��ֵ
	void GetAllHashValue(const string& INkey, vector<string>& INhashValueVector);

	// ��ȡ�������й�ϣ��ֵ
	void GetAllHashKV(const string& INkey, vector<std::pair<string, string>>& OUTpairVector);

public:
	// ��������
	void Save();
	
	// �첽����
	void BGSave();

	// ��ȡ�ϴα���ʱ��
	time_t GetLastSaveTime();

	// �رշ�����
	void ShutDown();
public:
	// ���redis server��Ϣ
	void PrintRedisClientInfo();

private:
	// ����
	redis::client* m_redisClient;
};

#endif