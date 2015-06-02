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
	// ��ɫ���
	UInt32 playerID ;
	// ��ɫ�˺�
	UInt32 accountID ;
	// ��ɫ����
	string playerName;
	// ��������
	string unionName;
	// ��ɫ�ȼ�
	UInt8 level;
	// ����
	UInt32 exp;
	// ���
	UInt32 gold;
	// ��ʯ
	UInt32 diamond;
	// ����
	UInt32 physicalStrength;
	// ���ܵ�
	UInt32  skillPoint;
	// VIP����
	UInt32 vipExp;
	// VIP�ȼ�
	UInt8 vipLv;
	// ���˱��
	UInt32 unionIndex;
	// �ϴ��˳�ʱ��
	string loginoutTime;
	// ����ʱ��
	string creationTime;
	// ��½ʱ��
	string loginTime ;
	// ���ͷ��ID
	UInt32 photoID;
	// ����ֵ
	UInt32 refineValue ;
	// ��һ����������ʱ��
	time_t addStaminaTime;
	// ��һ�μ��ܵ�����ʱ��
	time_t addSkillPointTime;
	// ���ս����
	UInt32 fightingValue;
	// ����ʹ�õ���ִ���
	UInt32 buyGoldCount;
	// ���칺����������
	UInt32 buyStaminaCount;
	// ���е�Կ��
	UInt32 towerKeyNum;
	// �´�Կ�����ӵ�ʱ��
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
	// �������
	UInt32 copyMapID = 0;
	// ��ʼʱ��
	UInt32 startTime = 0;
	// �������￪ʼʱ��
	UInt32 itemStartTime = 0;
};

AJSON(RedisDataCopyMapGJ, (copyMapID)(startTime)(itemStartTime));

#endif