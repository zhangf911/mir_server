#ifndef GATESERVER_REDISDATA_ACCOUNT_H
#define GATESERVER_REDISDATA_ACCOUNT_H

#include "CommDef.h"
#include <ajson.hpp>
#include "Type.h"

using namespace boost::ajson;

struct RedisDataAccount
{
	string account = "";
	string token = "";
	UInt32 userID = 0;
	UInt32 playerID = 0;
	string playerName = "";
};

AJSON(RedisDataAccount, (account)(token)(userID)(playerID)(playerName));

struct RedisDataCharacter
{
	// 角色编号
	UInt32 playerID ;
	// 角色账号
	UInt32 accountID ;
	// 角色名称
	string playerName;
	// 联盟名称
	string unionName;
	// 角色等级
	UInt8 level;
	// 经验
	UInt32 exp;
	// 金币
	UInt32 gold;
	// 钻石
	UInt32 diamond;
	// 体力
	UInt32 physicalStrength;
	// 技能点
	UInt32  skillPoint;
	// VIP经验
	UInt32 vipExp;
	// VIP等级
	UInt8 vipLv;
	// 联盟编号
	UInt32 unionIndex;
	// 上次退出时间
	string loginoutTime;
	// 创建时间
	string creationTime;
	// 登陆时间
	string loginTime ;
	// 玩家头像ID
	UInt32 photoID;
	// 精炼值
	UInt32 refineValue ;
	// 下一次体力增加时间
	time_t addStaminaTime;
	// 下一次技能点增加时间
	time_t addSkillPointTime;
	// 玩家战斗力
	UInt32 fightingValue;
	// 当天使用点金手次数
	UInt32 buyGoldCount;
	// 当天购买体力次数
	UInt32 buyStaminaCount;
	// 已有的钥匙
	UInt32 towerKeyNum;
	// 下次钥匙增加的时间
	UInt32 addTowerKeyTime;
	RedisDataCharacter(const RedisDataCharacter& INright)
	{
		playerID = INright.playerID;
		accountID = INright.accountID;
		playerName = INright.playerName;
		unionName = INright.unionName;
		level = INright.level;
		exp = INright.exp;
		gold = INright.gold;
		diamond = INright.diamond;
		refineValue = INright.refineValue;
		physicalStrength = INright.physicalStrength;
		skillPoint = INright.skillPoint;
		vipExp = INright.vipExp;
		vipLv = INright.vipLv;
		unionIndex = INright.unionIndex;
		loginoutTime = INright.loginoutTime;
		unionIndex = INright.unionIndex;
		creationTime = INright.creationTime;
		loginTime = INright.loginTime;
		photoID = INright.photoID;
		addStaminaTime = INright.addStaminaTime;
		addSkillPointTime = INright.addSkillPointTime;
		fightingValue = INright.fightingValue;
		buyGoldCount = INright.buyGoldCount;
		buyStaminaCount = INright.buyStaminaCount;
		towerKeyNum = INright.towerKeyNum;
		addTowerKeyTime = INright.addTowerKeyTime;
	}

	RedisDataCharacter& operator=(const RedisDataCharacter& INright)
	{
		playerID = INright.playerID;
		accountID = INright.accountID;
		playerName = INright.playerName;
		unionName = INright.unionName;
		level = INright.level;
		exp = INright.exp;
		gold = INright.gold;
		diamond = INright.diamond;
		refineValue = INright.refineValue;
		physicalStrength = INright.physicalStrength;
		skillPoint = INright.skillPoint;
		vipExp = INright.vipExp;
		vipLv = INright.vipLv;
		unionIndex = INright.unionIndex;
		loginoutTime = INright.loginoutTime;
		unionIndex = INright.unionIndex;
		creationTime = INright.creationTime;
		loginTime = INright.loginTime;
		photoID = INright.photoID;
		addStaminaTime = INright.addStaminaTime;
		addSkillPointTime = INright.addSkillPointTime;
		fightingValue = INright.fightingValue;
		buyGoldCount = INright.buyGoldCount;
		buyStaminaCount = INright.buyStaminaCount;
		towerKeyNum = INright.towerKeyNum;
		addTowerKeyTime = INright.addTowerKeyTime;
		return *this;
	}

	RedisDataCharacter(RedisDataCharacter&& INright)
	{
		playerID = INright.playerID;
		accountID = INright.accountID;
		playerName = INright.playerName;
		unionName = INright.unionName;
		level = INright.level;
		exp = INright.exp;
		gold = INright.gold;
		diamond = INright.diamond;
		refineValue = INright.refineValue;
		physicalStrength = INright.physicalStrength;
		skillPoint = INright.skillPoint;
		vipExp = INright.vipExp;
		vipLv = INright.vipLv;
		unionIndex = INright.unionIndex;
		loginoutTime = INright.loginoutTime;
		unionIndex = INright.unionIndex;
		creationTime = INright.creationTime;
		loginTime = INright.loginTime;
		photoID = INright.photoID;
		addStaminaTime = INright.addStaminaTime;
		addSkillPointTime = INright.addSkillPointTime;
		fightingValue = INright.fightingValue;
		buyGoldCount = INright.buyGoldCount;
		buyStaminaCount = INright.buyStaminaCount;
		towerKeyNum = INright.towerKeyNum;
		addTowerKeyTime = INright.addTowerKeyTime;
	}

	RedisDataCharacter& operator=(RedisDataCharacter&& INright)
	{
		playerID = INright.playerID;
		accountID = INright.accountID;
		playerName = INright.playerName;
		unionName = INright.unionName;
		level = INright.level;
		exp = INright.exp;
		gold = INright.gold;
		diamond = INright.diamond;
		refineValue = INright.refineValue;
		physicalStrength = INright.physicalStrength;
		skillPoint = INright.skillPoint;
		vipExp = INright.vipExp;
		vipLv = INright.vipLv;
		unionIndex = INright.unionIndex;
		loginoutTime = INright.loginoutTime;
		unionIndex = INright.unionIndex;
		creationTime = INright.creationTime;
		loginTime = INright.loginTime;
		photoID = INright.photoID;
		addStaminaTime = INright.addStaminaTime;
		addSkillPointTime = INright.addSkillPointTime;
		fightingValue = INright.fightingValue;
		buyGoldCount = INright.buyGoldCount;
		buyStaminaCount = INright.buyStaminaCount;
		towerKeyNum = INright.towerKeyNum;
		addTowerKeyTime = INright.addTowerKeyTime;
		return *this;
	}
	RedisDataCharacter()
	{
		Reset();
	}

	void Reset()
	{
		playerID = 0;
		accountID = 0;
		playerName = "";
		unionName = "";
		level = 0;
		exp = 0;
		gold = 0;
		diamond = 0;
		refineValue = 0;
		physicalStrength = 0;
		skillPoint = 0;
		vipExp = 0;
		vipLv = 0;
		unionIndex = 0;
		loginoutTime = "";
		creationTime = "";
		loginTime = "";
		photoID = 0;
		addStaminaTime = 0;
		addSkillPointTime = 0;
		fightingValue = 0;
		buyGoldCount = 0;
		buyStaminaCount = 0;
		towerKeyNum = 5;
		addTowerKeyTime = 0;
	}
};

AJSON(RedisDataCharacter, (playerID)(accountID)(playerName)(unionName)
	(level)(exp)(gold)(diamond)(refineValue)(physicalStrength)(skillPoint)(vipExp)(vipLv)(unionIndex)
	(loginoutTime)(creationTime)(loginTime)(photoID)(addStaminaTime)(addSkillPointTime)(fightingValue)
	(buyGoldCount)(buyStaminaCount)(towerKeyNum)(addTowerKeyTime));


struct RedisDataCopyMapGJ 
{
	// 副本编号
	UInt32 copyMapID = 0;
	// 开始时间
	UInt32 startTime = 0;
	// 神秘礼物开始时间
	UInt32 itemStartTime = 0;
};

AJSON(RedisDataCopyMapGJ, (copyMapID)(startTime)(itemStartTime));

#endif