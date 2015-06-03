#include "RedisKeyManager.h"
#include "CommDef.h"

RedisKeyManager::RedisKeyManager()
{

}

RedisKeyManager::~RedisKeyManager()
{

}

bool RedisKeyManager::Initial()
{

	return true;
}

string RedisKeyManager::GetRedisKey(UInt32 INkeyType, const string& INparam)
{
	switch (INkeyType)
	{
	case ERedisKeyType_AccountGUID:
	{
		return "account:id";
	}
	case ERedisKeyType_AccountID:
	{
		return "account:" + INparam + ":id";
	}
	case ERedisKeyType_AccountInfo:
	{
		return "account:" + INparam + ":info";
	}
	case ERedisKeyType_AccountPlayer:
	{
		return "account:" + INparam + ":player";
	}
	case ERedisKeyType_OnlineAccountSet:
	{
		return "account:online:set";
	}
	case ERedisKeyType_PlayerAccount:
	{
		SJ_ASSERT(INparam != "");
		return "player:" + INparam + ":account";
	}
	case ERedisKeyType_PlayerGUID:
	{
		return "player:id";
	}
	case ERedisKeyType_PlayerID:
	{
		SJ_ASSERT(INparam != "");
		return "player:" + INparam + ":id";
	}
	case ERedisKeyType_PlayerBaseInfo:
	{
		SJ_ASSERT(INparam != "");
		return "player:" + INparam + ":info";
	}
	case ERedisKeyType_PlayerExt:
	{
		SJ_ASSERT(INparam != "");
		return "player:" + INparam + ":ext";
	}
	case ERedisKeyType_SocialInfo:
	{
		return "social:" + INparam + ":info";
	}
	case ERedisKeyType_SocialRequest:
	{
		return "social:" + INparam + ":Request";
	}
	// ½ÇÉ«¾µÏñ
	case ERedisKeyType_PlayerMirror:
	{
		SJ_ASSERT(INparam != "");
		return "player:" + INparam + ":mirror";
	}
	case ERedisKeyType_MirrorPlayer:
	{
		return "mirror:" + INparam + ":player";
	}
	case ERedisKeyType_ArenaRank:
	{
		return "arena:rank";
	}
	case ERedisKeyType_PlayerHeroMirror:
	{
		return "hero:" + INparam + ":mirror";
	}
	case ERedisKeyType_ArenaScore:
	{
		return "arena:" + INparam + ":score";
	}
	case ERedisKeyType_ArenaDefanceInfo:
	{
		return "arena:" + INparam + ":defance";
	}
	case ERedisKeyType_ArenaLog:
	{
		return "arena:" + INparam + ":log";
	}
	case ERedisKeyType_MonsterHillRank:
	{
		return "monsterhill:" + INparam + ":rank";
	}
	case ERedisKeyType_MonsterKiller:
	{
		return "monsterhill:" + INparam + ":killer";
	}
	case ERedisKeyType_MonsterHillInfo:
	{
		return "monsterhill:" + INparam + ":info";
	}
	case ERedisKeyType_SilveroreReserves:
	{
		return "silverore:reserves";
	}
	case ERedisKeyType_SilveroreGatherCount:
	{
		return "silverore:" + INparam + ":gather";
	}
	case ERedisKeyType_SilveroreStar:
	{
		return "silverore:" + INparam + ":star";
	}
	case ERedisKeyType_SocialGatherGoldOre:
	{
		return "silverore:" + INparam + ":socialGather";
	}
	case ERedisKeyType_OutSideSilverore:
	{
		return "silverore:" + INparam + ":outSide";
	}
	case ERedisKeyType_PlayerOutSideIsland:
	{
		return "silverore:playerOutSideIsland";
	}
	case ERedisKeyType_OutSideIslandDefance:
	{
		return "silverore:" + INparam + ":defance";
	}
	case ERedisKeyType_PlayerLevelRank:
	{
		return "player:level:rank";
	}
	case ERedisKeyType_PlayerWealthRank:
	{
		return "player:wealth:rank";
	}
	case ERedisKeyType_PlayerFightPowerRank:
	{
		return "player:fightpower:rank";
	}
	case ERedisKeyType_MsgInfo:
	{
		return "msg:" + INparam + ":info";
	}
	case ERedisKeyType_RunePage:
	{
		return "runepage:info";
	}
	case ERedisKeyType_RunePageDefanceInfo:
	{
		return "runepage:" + INparam + ":Defanceinfo";
	}
	case ERedisKeyType_PlaerTower:
	{
		return "tower:" + INparam + ":info";
	}
	default:
	{
		SJ_ASSERT(0);
		break;
	}
	}
	return "";
}