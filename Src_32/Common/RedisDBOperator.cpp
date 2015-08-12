#include "RedisDBOperator.h"
#include "CommDef.h"

RedisDBOperator::RedisDBOperator()
{
	m_redisClient = nullptr;
}

RedisDBOperator::~RedisDBOperator()
{
	delete m_redisClient;
}

bool RedisDBOperator::Initial(const string& INhost, UInt16 INport)
{
	const char* c_host = getenv("REDIS_HOST");
	string host = INhost;
	if(c_host)
		host = c_host;
	m_redisClient = new redis::client(host);
	
	NOTE_LOG("连接redis服务器, IP : %s",
		host.c_str());
	return true;
}

void RedisDBOperator::ChangeRepertory(UInt32 INindex)
{
	m_redisClient->select(INindex);
}

void RedisDBOperator::Set(const string& INkey, const string& INvalue)
{
	m_redisClient->set(INkey, INvalue);
}

string RedisDBOperator::Get(const string& INkey)
{
	return m_redisClient->get(INkey);
}

bool RedisDBOperator::CheckIsExists(const string& INkey)
{
	return m_redisClient->exists(INkey);
}

UInt32 RedisDBOperator::GetKeys(const string& INkey, vector<string>& OUTkeyVector)
{
	return m_redisClient->keys(INkey, OUTkeyVector);
}

string RedisDBOperator::GetSet(const string& INkey, const string& INvalue)
{
	return m_redisClient->getset(INkey, INvalue);
}

void RedisDBOperator::MultiGet(const vector<string>& INkeyVector, vector<string>& OUTvalueVector)
{
	m_redisClient->mget(INkeyVector, OUTvalueVector);
}

bool RedisDBOperator::SetNX(const string& INkey, const string& INvalue)
{
	return m_redisClient->setnx(INkey, INvalue);
}

Int32 RedisDBOperator::Incr(const string& INkey)
{
	return m_redisClient->incr(INkey);
}

Int32 RedisDBOperator::Decr(const string& INkey)
{
	return m_redisClient->decr(INkey);
}

Int32 RedisDBOperator::IncrBy(const string& INkey, UInt32 INnumber)
{
	return m_redisClient->incrby(INkey, INnumber);
}

Int32 RedisDBOperator::DecrBy(const string& INkey, UInt32 INnumber)
{
	return m_redisClient->decrby(INkey, INnumber);
}

bool RedisDBOperator::Del(const string& INkey)
{
	return m_redisClient->del(INkey);
}

UInt32 RedisDBOperator::GetType(const string& INkey)
{
	return m_redisClient->type(INkey);
}

string RedisDBOperator::GetRandomKey()
{
	return m_redisClient->randomkey();
}

void RedisDBOperator::Rename(const string& INkey, const string& INnewKey)
{
	m_redisClient->rename(INkey, INnewKey);
}

void RedisDBOperator::RenameNX(const string& INkey, const string& INnewKey)
{
	m_redisClient->renamenx(INkey, INnewKey);
}

UInt32 RedisDBOperator::GetKeyCount()
{
	return m_redisClient->dbsize();
}

void RedisDBOperator::SetKeyRemainTime(const string& INkey, UInt32 INsecond)
{
	m_redisClient->expire(INkey, INsecond);
}

void RedisDBOperator::Move(const string& INkey, UInt32 INindex)
{
	m_redisClient->move(INkey, INindex);
}

void RedisDBOperator::InsertToSet(const string& INkey, const string& INvalue)
{
	m_redisClient->sadd(INkey, INvalue);
}

void RedisDBOperator::SortAscending(const string& INkey, vector<string>& OUTvalueVector)
{
	m_redisClient->sort(INkey, OUTvalueVector, redis::client::sort_order_ascending);
}

void RedisDBOperator::SortDescending(const string& INkey, vector<string>& OUTvalueVector)
{
	m_redisClient->sort(INkey, OUTvalueVector, redis::client::sort_order_descending);
}

Int32 RedisDBOperator::PushBack(const string& INkey, const string& INvalue)
{
	return m_redisClient->rpush(INkey, INvalue);
}

Int32 RedisDBOperator::PushFront(const string& INkey, const string& INvalue)
{
	return m_redisClient->lpush(INkey, INvalue);
}

Int32 RedisDBOperator::GetListSize(const string& INkey)
{
	return m_redisClient->llen(INkey);
}

string RedisDBOperator::GetListIndexValue(const string& INkey, Int32 INindex)
{
	return m_redisClient->lindex(INkey, INindex);
}

Int32 RedisDBOperator::GetRangeValue(const string& INkey, Int32 INstartIndex, Int32 INendIndex, vector<string>& OUTvalueVector)
{
	return m_redisClient->lrange(INkey, INstartIndex, INendIndex, OUTvalueVector);
}

Int32 RedisDBOperator::GetList(const string& INkey, vector<string>& OUTvalueVector)
{
	return m_redisClient->get_list(INkey, OUTvalueVector);
}

void RedisDBOperator::TrimList(const string& INkey, Int32 INstartIndex, Int32 INendIndex)
{
	m_redisClient->ltrim(INkey, INstartIndex, INendIndex);
}

void RedisDBOperator::SetListIndexValue(const string& INkey, Int32 INindex, const string& INvalue)
{
	m_redisClient->lset(INkey, INindex, INvalue);
}

Int32 RedisDBOperator::DeleteFromList(const string& INkey, Int32 INcount, const string& INvalue)
{
	return m_redisClient->lrem(INkey, INcount, INvalue);
}

string RedisDBOperator::PopFront(const string& INkey)
{
	return m_redisClient->lpop(INkey);
}

string RedisDBOperator::PopBack(const string& INkey)
{
	return m_redisClient->rpop(INkey);
}

void RedisDBOperator::AddToSet(const string& INkey, const string& INvalue)
{
	m_redisClient->sadd(INkey, INvalue);
}

void RedisDBOperator::DeleteFromSet(const string& INkey, const string& INvalue)
{
	m_redisClient->srem(INkey, INvalue);
}

bool RedisDBOperator::IsSetMember(const string& INkey, const string& INvalue)
{
	return m_redisClient->sismember(INkey, INvalue);
}

void RedisDBOperator::SetMemberMove(const string& INkey, const string& INtargetKey, const string& INvalue)
{
	m_redisClient->smove(INkey, INtargetKey, INvalue);
}

Int32 RedisDBOperator::GetSetMemberCount(const string& INkey)
{
	return m_redisClient->scard(INkey);
}

Int32 RedisDBOperator::GetSetMember(const string& INkey, set<string>& OUTvalueSet)
{
	return m_redisClient->smembers(INkey, OUTvalueSet);
}

Int32 RedisDBOperator::GetSetIntersection(const vector<string>& INkeyVector, set<string>& OUTvalueSet)
{
	return m_redisClient->sinter(INkeyVector, OUTvalueSet);
}

Int32 RedisDBOperator::SetSetIntersection(const string& INkey, const vector<string>& INkeyVector)
{
	return m_redisClient->sinterstore(INkey, INkeyVector);
}

Int32 RedisDBOperator::MergeSet(const string& INkey, const vector<string>& INkeyVector)
{
	return m_redisClient->sunionstore(INkey, INkeyVector);
}

Int32 RedisDBOperator::MergeSet(const vector<string>& INkeyVector, set<string>& OUTvalueSet)
{
	return m_redisClient->sunion(INkeyVector, OUTvalueSet);
}

void RedisDBOperator::AddToSortedSet(const string& INkey, double INscroe, const string& INvalue)
{
	return m_redisClient->zadd(INkey, INscroe, INvalue);
}

void RedisDBOperator::DeleteFromSortedSet(const string& INkey, const string& INvalue)
{
	m_redisClient->zrem(INkey, INvalue);
}

Int32 RedisDBOperator::GetSortedSetMemberCount(const string& INkey)
{
	return m_redisClient->zcard(INkey);
}

double RedisDBOperator::IncrSortedSetBy(const string& INkey, const string& INvalue, Int32 INscore)
{
	return m_redisClient->zincrby(INkey, INvalue, INscore);
}

double RedisDBOperator::GetSortedSetScore(const string& INkey, const string& INvalue)
{
	return m_redisClient->zscore(INkey, INvalue);
}

Int32 RedisDBOperator::GetIndexInSortedSet(const string& INkey, const string& INvalue)
{
	return m_redisClient->zrank(INkey, INvalue);
}

Int32 RedisDBOperator::GetHighIndexInSortedSet(const string& INkey, const string& INvalue)
{
	return m_redisClient->zrevrank(INkey, INvalue);
}

void RedisDBOperator::GetSortedSetRange(const string& INkey, Int32 INstartIndex, Int32 INendIndex, vector<string>& OUTvalueVector)
{
	m_redisClient->zrange(INkey, INstartIndex, INendIndex, OUTvalueVector);
}

void RedisDBOperator::GetSortedSetRevRange(const string& INkey, Int32 INstartIndex, Int32 INendIndex, vector<string>& OUTvalueVector)
{
	m_redisClient->zrevrange(INkey, INstartIndex, INendIndex, OUTvalueVector);
}

void RedisDBOperator::GetSortedSetRangeByScore(const string& INkey, double INstartScore, double INendScore, vector<string>& OUTvalueVector)
{
	m_redisClient->zrangebyscore(INkey, INstartScore, INendScore, OUTvalueVector);
}

Int32 RedisDBOperator::GetSortedSetRangeMemberCount(const string& INkey, double INstartScore, double INendScore, UInt32 INexclude)
{
	return m_redisClient->zcount(INkey, INstartScore, INendScore, INexclude);
}

Int32 RedisDBOperator::MultiRemoveFromSortedSetByIndex(const string& INkey, Int32 INstartIndex, Int32 INendIndex)
{
	return m_redisClient->zremrangebyrank(INkey, INstartIndex, INendIndex);
}

Int32 RedisDBOperator::MultiRemoveFromSortedSetByScore(const string& INkey, double INstartScore, double INendScore)
{
	return m_redisClient->zremrangebyscore(INkey, INstartScore, INendScore);
}

Int32 RedisDBOperator::MultiRemoveFromSortedSetByScoreFromMin(const string& INkey, double INendScore)
{
	return m_redisClient->zremrangebyscorefrommin(INkey, INendScore);
}

Int32 RedisDBOperator::MultiRemoveFromSortedSetByScoreToMax(const string& INkey, double INstartScore)
{
	return m_redisClient->zremrangebyscoretomax(INkey, INstartScore);
}

Int32 RedisDBOperator::MergeSortedSet(const string& INkey, const vector<string>& INkeyVector)
{
	return m_redisClient->zunionstore(INkey, INkeyVector);
}

Int32 RedisDBOperator::SetSortedSetIntersection(const string& INkey, const vector<string>& INkeyVector)
{
	return m_redisClient->zinterstore(INkey, INkeyVector);
}

bool RedisDBOperator::AddToHash(const string& INkey, const string& INhashKey, const string& INvalue)
{
	return m_redisClient->hset(INkey, INhashKey, INvalue);
}

Int32 RedisDBOperator::GetHashMemberCount(const string& INkey)
{
	return m_redisClient->hlen(INkey);
}

string RedisDBOperator::GetHashMember(const string& INkey, const string& INhashKey)
{
	return m_redisClient->hget(INkey, INhashKey);
}

bool RedisDBOperator::SetHashMember(const string& INkey, const string& INhashKey, const string& INvalue)
{
	return m_redisClient->hsetnx(INkey, INhashKey, INvalue);
}

void RedisDBOperator::MultiAddHashMember(const string& INkey, const vector<std::pair<string, string>>& INpairVector)
{
	m_redisClient->hmset(INkey, INpairVector);
}

void RedisDBOperator::MultiGetHashMember(const string& INkey, const vector<string>& INhashKeyVector, vector<string>& OUTvalueVector)
{
	m_redisClient->hmget(INkey, INhashKeyVector, OUTvalueVector);
}

Int32 RedisDBOperator::IncrHashMemberBy(const string& INkey, const string& INhashKey, Int32 INvalue)
{
	return m_redisClient->hincrby(INkey, INhashKey, INvalue);
}

bool RedisDBOperator::CheckHasHashMember(const string& INkey, const string& INhaskKey)
{
	return m_redisClient->hexists(INkey, INhaskKey);
}

bool RedisDBOperator::DeleteHashMember(const string& INkey, const string& INhashKey)
{
	return m_redisClient->hdel(INkey, INhashKey);
}

void RedisDBOperator::GetAllHashKey(const string& INkey, vector<string>& INhashKeyVector)
{
	m_redisClient->hkeys(INkey, INhashKeyVector);
}

void RedisDBOperator::GetAllHashValue(const string& INkey, vector<string>& INhashValueVector)
{
	m_redisClient->hvals(INkey, INhashValueVector);
}

void RedisDBOperator::GetAllHashKV(const string& INkey, vector<std::pair<string, string>>& OUTpairVector)
{
	m_redisClient->hgetall(INkey, OUTpairVector);
}

void RedisDBOperator::Save()
{
	m_redisClient->save();
}

void RedisDBOperator::BGSave()
{
	m_redisClient->bgsave();
}

time_t RedisDBOperator::GetLastSaveTime()
{
	return m_redisClient->lastsave();
}

void RedisDBOperator::ShutDown()
{
	m_redisClient->shutdown();
}

void RedisDBOperator::PrintRedisClientInfo()
{
	redis::server_info info;
	m_redisClient->info(info);
}