#ifndef LOG_TYPE_H
#define LOG_TYPE_H
#include "Type.h"

enum AddPropUnifyType			// 统一获得类型
{
	// 通过邮件添加
	EAddPropType_Msg = 1,
	// 通过道具使用添加
	EAddPropType_ItemUse,
	// 通过GM命令获得
	EAddPropType_GM,
	// 通过每日任务获得
	EAddPropType_DayTask,
	// 奖励活动获得
	EAddPropType_PrizeCamp,
	// 通过充值获取
	EAddPropType_Recharge,
	// 首次充值赠送
	EAddPropType_Prize_RechargeFirst,
	// 日常充值赠送
	EAddPropType_Prize_RechargeDay,
	// 购买金币匣赠送
	EAddPropType_BuyMoneyBox,
	// 购买金币匣日常赠送
	EAddPropType_DayMoneyBox = 10,
	// 副本通关奖励	
	EAddPropType_ClearanceAward,
	// 成就任务奖励
	EAddPropType_Achievement,
	// 挑战肉山获得
	EAddPropType_ChallengeHill,
	// 副本掉落
	EAddPropType_CopyDrop,
	// 竞技场积分兑换
	EAddPropType_ExchangeItem,
	// 竞技场排名奖励
	EAddPropType_GainRankReward,

	EAddPropType_Last = 50,			
};

enum DecreaseUnifyType			// 统一消耗类型
{
	EDecreaseUnifyType_GM = 0,
	EDecreaseUnifyType_BuyMoneyBox = 1,  //活动购买金币匣

};

enum AddGoldType				// 金币增加类型
{	
	// 系统赠送
	EAddGoldType_Donate = EAddPropType_Last,
	// 野区阶段性奖励		
	EAddGoldType_OutSide,
};

enum DecreaseGoldType				// 金币减少类型
{
	// 购买守卫财富
	EDecreaseGoldType_BuyHlao_1 = 1,
	// 购买守卫魔法
	EDecreaseGoldType_BuyHlao_2,
	// 购买守卫荣誉	
	EDecreaseGoldType_BuyHlao_3,
	// 培养英雄	
	EDecreaseGoldType_TrainHero,
	// 建造生命泉水	
	EDecreaseGoldType_BuildLifeStream,
	// 重置泉水CD时间
	EDecreaseGoldType_ResetLifeCD,
	// 采集银矿	
	EDecreaseGoldType_SilverOre,	
	// 购买物品
	EDecreaseGoldType_BuyItem,		
	// 野店抽奖
	EDecreaseGoldType_JungleShopLottery,
	// 抽卡
	EDecreaseGoldType_RecruitHero,
	// 银矿掠夺消耗
	EDecreaseGoldType_SilverOreRob,
	// 攻打肉山买活
	EDecreaseGoldType_Hill,
	// 创建联盟
	EDecreaseGoldType_CreateUnion,
	// 购买体力消耗
	EDecreaseUnifyType_BuyStamina ,
	// 购买活力消耗
	EDecreaseUnifyType_BuyVitality ,
	// 购买竞技场次数
	EDecreaseUnifyType_Athletics ,
	// 重置竞技场挑战时间
	EDecreaseUnifyType_ClearAthleticsCD,
	// 重置银矿掠夺时间
	EDecreaseUnifyType_ClearSilverOreCD,
	// 更换头像
	DecreaseUnifyType_ChangePhoto,
	// 更换名字
	DecreaseUnifyType_ChangeName,
	// 鞭挞奴隶
	DecreaseUnifyType_ScourgingSlave,
};

enum AddSilverType					// 银币增加类型
{
	// 副本掉落
	EAddSilverType_Copy = EAddPropType_Last,
	// 采集银矿获得
	EAddSilverType_SilverOre,
	// 抢劫他人银矿活动
	EAddSilverType_RobSilverOre,	
	// 系统赠送
	EAddSilverType_Donate,			
	// 野区阶段性奖励
	EAddSilverType_OutSide,			
	// 装备出售
	EAddSilverType_SellEquip,		
};

enum DecreaseSilverType					// 银币减少类型
{
	// 培养英雄
	EDecreaseSilverType_TrainHero = 1,	
	// 使用生命泉水
	EDecreaseSilverType_UseLifeStream,
	// 购买物品
	EDecreaseSilverType_BuyItem,		
	// 强化装备
	EDecreaseSilverType_StrengthEquip,	
	// 银矿掠夺消耗
	EDecreaseSilverType_SilverOreRob,
};

enum AddItemType					// 物品获得类型			
{
	// 系统赠送
	EAddItemType_System = EAddPropType_Last,
	// 副本掉落
	EAddItemType_Drop,
	// 野区
	EAddItemType_OutSideDrop,	
	// 野区阶段性奖励
	EAddItemType_OutSideReward,
	// 竞技场积分兑换
	EAddItemType_ExchangeItem,	
	// 竞技场领取奖励
	EAddItemType_GainRankReward,
	// 购买获得
	EAddItemType_Buy,			
	// 野店抽奖
	EAddItemType_JungleShop,	
	// 合成获得
	EAddItemType_Compound,		
	// 领取培养药剂
	EAddItemType_ReceiveMedicine,
	// 怪物掉落获得
	EAddItemType_Monster,
};

enum DecreaseItemType					// 物品减少类型		
{
	// 出售
	EDecreaseItemType_Sell = 1,	 
	// 合成消耗
	EDecreaseItemType_Compound,
	// 道具使用
	EDecreaseItemType_ItemUse,	
	// 箭塔消耗
	EDecreaseItemType_Tower,
	// 副本消耗
	EDecreaseItemType_Copy,
	// 野区消耗
	EDecreaseItemType_OutSide,
};

enum AddSkillType						// 技能获得类型
{
	// 通过系统赠送获得
	EAddSkillType_System = EAddPropType_Last,
	// 通过魔法堂合成获得
	EAddSkillType_ComposeSkill,		
	// 通过技能强化获得
	EAddSkillType_StrengthSkill,	
};

enum DecreaseSkillType
{
	// 通过技能强化消耗
	EDecreaseSkillType_StrengthSkill,
};

enum AddHeroSoulType				// 英魂
{
	// 通过招募英雄获得
	EAddHeroSoulType_RecruitHero = EAddPropType_Last,
	// 通过系统赠送获得
	EAddHeroSoulType_System,
};

enum DecreaseHeroSoulType
{
	// 通过炼魂消耗
	EDecreaseHeroSoulType_TrainHeroSoul = 1,	
	// 通过合成英雄消耗
	EDecreaseHeroSoulType_RecruitHeroSoul,		
};

enum AddHeroType				// 英雄
{
	// 通过系统赠送获得
	EAddHeroType_System = EAddPropType_Last,
	// 通过招募英雄获得
	EAddHeroType_RecruitHero,		
	// 通过合成英魂获得
	EAddHeroType_RecruitHeroSoul,	
	// 通过邮件获得
	EAddHeroType_Msg,			
	// 道具使用	
	EAddHeroType_ItemUse,			
};

enum AddSkillChipType					// 技能碎片
{
	// 通过抢夺获得
	EAddSkillChipType_Rob = EAddPropType_Last,

};

enum DecreaseSkillChipType
{
	// 合成消耗
	EDecreaseSkillChipType_ComposeSkill = 1,
	// 被抢夺
	EDecreaseSkillChipType_Rob,
};

//活力
enum AddVigourType
{
	// 按时回复
	EAddVigourType_Recover = EAddPropType_Last,
	// 金币购买获得
	EAddVigourType_Gold,
};

enum DecreaseVigourType
{
	// 魔法堂抢夺技能碎片
	DecreaseVigourType_RobSkillChip = 1,
	// 挑战竞技场
	DecreaseVigourType_ChallengeAthletics,
	// 通过GM命令修改
	DecreaseVigourType_GM,
};

// 体力
enum AddStaminaType
{
	// 按时回复
	AddStaminaType_Recover = EAddPropType_Last,
	// 金币购买获得
	AddStaminaType_Gold,
};

enum DecreaseStaminaType
{
	// 副本
	DecreaseStaminaType_Copy = 1,
	// 挑战竞技场
	DecreaseStaminaType_ChallengeAthletics,
	// 通过GM命令修改
	DecreaseStaminaType_GM,
};

#endif