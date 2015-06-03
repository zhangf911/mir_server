#ifndef REDIS_KEY_MANAGER_H
#define REDIS_KEY_MANAGER_H

#include "Type.h"

enum RedisKeyType
{
	ERedisKeyType_AccountGUID = 1,
	ERedisKeyType_AccountID,
	ERedisKeyType_AccountInfo,
	ERedisKeyType_AccountPlayer,
	ERedisKeyType_OnlineAccountSet,
	ERedisKeyType_PlayerAccount,
	ERedisKeyType_PlayerGUID,
	ERedisKeyType_PlayerID,
	ERedisKeyType_PlayerBaseInfo,
	ERedisKeyType_PlayerExt,
	ERedisKeyType_SocialInfo,
	ERedisKeyType_SocialRequest,
	ERedisKeyType_MirrorPlayer,
	ERedisKeyType_PlayerMirror,
	ERedisKeyType_ArenaRank,
	ERedisKeyType_ArenaDefanceInfo,
	ERedisKeyType_ArenaLog,
	ERedisKeyType_PlayerHeroMirror,
	ERedisKeyType_ArenaScore,
	ERedisKeyType_MonsterHillRank,
	ERedisKeyType_MonsterKiller,
	ERedisKeyType_MonsterHillInfo,
	ERedisKeyType_SilveroreReserves,
	ERedisKeyType_SilveroreGatherCount,
	ERedisKeyType_SilveroreStar,
	ERedisKeyType_SocialGatherGoldOre,
	ERedisKeyType_OutSideSilverore,
	ERedisKeyType_PlayerOutSideIsland,
	ERedisKeyType_OutSideIslandDefance,
	ERedisKeyType_PlayerLevelRank,
	ERedisKeyType_PlayerWealthRank,
	ERedisKeyType_PlayerFightPowerRank,
	ERedisKeyType_RunePage,
	ERedisKeyType_MsgInfo,
	ERedisKeyType_RunePageDefanceInfo,
	ERedisKeyType_PlaerTower,
};

class RedisKeyManager
{
public:
	RedisKeyManager();

	~RedisKeyManager();

public:
	// 初始化
	bool Initial();

	// 获取key
	static string GetRedisKey(UInt32 INkeyType, const string& INparam = "");

private:
	// 键表
	map<UInt32, string> m_keyMap;
};

#endif