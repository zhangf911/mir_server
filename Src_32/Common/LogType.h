#ifndef LOG_TYPE_H
#define LOG_TYPE_H
#include "Type.h"

enum AddPropUnifyType			// ͳһ�������
{
	// ͨ���ʼ����
	EAddPropType_Msg = 1,
	// ͨ������ʹ�����
	EAddPropType_ItemUse,
	// ͨ��GM������
	EAddPropType_GM,
	// ͨ��ÿ��������
	EAddPropType_DayTask,
	// ��������
	EAddPropType_PrizeCamp,
	// ͨ����ֵ��ȡ
	EAddPropType_Recharge,
	// �״γ�ֵ����
	EAddPropType_Prize_RechargeFirst,
	// �ճ���ֵ����
	EAddPropType_Prize_RechargeDay,
	// ������ϻ����
	EAddPropType_BuyMoneyBox,
	// ������ϻ�ճ�����
	EAddPropType_DayMoneyBox = 10,
	// ����ͨ�ؽ���	
	EAddPropType_ClearanceAward,
	// �ɾ�������
	EAddPropType_Achievement,
	// ��ս��ɽ���
	EAddPropType_ChallengeHill,
	// ��������
	EAddPropType_CopyDrop,
	// ���������ֶһ�
	EAddPropType_ExchangeItem,
	// ��������������
	EAddPropType_GainRankReward,

	EAddPropType_Last = 50,			
};

enum DecreaseUnifyType			// ͳһ��������
{
	EDecreaseUnifyType_GM = 0,
	EDecreaseUnifyType_BuyMoneyBox = 1,  //�������ϻ

};

enum AddGoldType				// �����������
{	
	// ϵͳ����
	EAddGoldType_Donate = EAddPropType_Last,
	// Ұ���׶��Խ���		
	EAddGoldType_OutSide,
};

enum DecreaseGoldType				// ��Ҽ�������
{
	// ���������Ƹ�
	EDecreaseGoldType_BuyHlao_1 = 1,
	// ��������ħ��
	EDecreaseGoldType_BuyHlao_2,
	// ������������	
	EDecreaseGoldType_BuyHlao_3,
	// ����Ӣ��	
	EDecreaseGoldType_TrainHero,
	// ��������Ȫˮ	
	EDecreaseGoldType_BuildLifeStream,
	// ����ȪˮCDʱ��
	EDecreaseGoldType_ResetLifeCD,
	// �ɼ�����	
	EDecreaseGoldType_SilverOre,	
	// ������Ʒ
	EDecreaseGoldType_BuyItem,		
	// Ұ��齱
	EDecreaseGoldType_JungleShopLottery,
	// �鿨
	EDecreaseGoldType_RecruitHero,
	// �����Ӷ�����
	EDecreaseGoldType_SilverOreRob,
	// ������ɽ���
	EDecreaseGoldType_Hill,
	// ��������
	EDecreaseGoldType_CreateUnion,
	// ������������
	EDecreaseUnifyType_BuyStamina ,
	// �����������
	EDecreaseUnifyType_BuyVitality ,
	// ���򾺼�������
	EDecreaseUnifyType_Athletics ,
	// ���þ�������սʱ��
	EDecreaseUnifyType_ClearAthleticsCD,
	// ���������Ӷ�ʱ��
	EDecreaseUnifyType_ClearSilverOreCD,
	// ����ͷ��
	DecreaseUnifyType_ChangePhoto,
	// ��������
	DecreaseUnifyType_ChangeName,
	// ��̢ū��
	DecreaseUnifyType_ScourgingSlave,
};

enum AddSilverType					// ������������
{
	// ��������
	EAddSilverType_Copy = EAddPropType_Last,
	// �ɼ�������
	EAddSilverType_SilverOre,
	// ������������
	EAddSilverType_RobSilverOre,	
	// ϵͳ����
	EAddSilverType_Donate,			
	// Ұ���׶��Խ���
	EAddSilverType_OutSide,			
	// װ������
	EAddSilverType_SellEquip,		
};

enum DecreaseSilverType					// ���Ҽ�������
{
	// ����Ӣ��
	EDecreaseSilverType_TrainHero = 1,	
	// ʹ������Ȫˮ
	EDecreaseSilverType_UseLifeStream,
	// ������Ʒ
	EDecreaseSilverType_BuyItem,		
	// ǿ��װ��
	EDecreaseSilverType_StrengthEquip,	
	// �����Ӷ�����
	EDecreaseSilverType_SilverOreRob,
};

enum AddItemType					// ��Ʒ�������			
{
	// ϵͳ����
	EAddItemType_System = EAddPropType_Last,
	// ��������
	EAddItemType_Drop,
	// Ұ��
	EAddItemType_OutSideDrop,	
	// Ұ���׶��Խ���
	EAddItemType_OutSideReward,
	// ���������ֶһ�
	EAddItemType_ExchangeItem,	
	// ��������ȡ����
	EAddItemType_GainRankReward,
	// ������
	EAddItemType_Buy,			
	// Ұ��齱
	EAddItemType_JungleShop,	
	// �ϳɻ��
	EAddItemType_Compound,		
	// ��ȡ����ҩ��
	EAddItemType_ReceiveMedicine,
	// ���������
	EAddItemType_Monster,
};

enum DecreaseItemType					// ��Ʒ��������		
{
	// ����
	EDecreaseItemType_Sell = 1,	 
	// �ϳ�����
	EDecreaseItemType_Compound,
	// ����ʹ��
	EDecreaseItemType_ItemUse,	
	// ��������
	EDecreaseItemType_Tower,
	// ��������
	EDecreaseItemType_Copy,
	// Ұ������
	EDecreaseItemType_OutSide,
};

enum AddSkillType						// ���ܻ������
{
	// ͨ��ϵͳ���ͻ��
	EAddSkillType_System = EAddPropType_Last,
	// ͨ��ħ���úϳɻ��
	EAddSkillType_ComposeSkill,		
	// ͨ������ǿ�����
	EAddSkillType_StrengthSkill,	
};

enum DecreaseSkillType
{
	// ͨ������ǿ������
	EDecreaseSkillType_StrengthSkill,
};

enum AddHeroSoulType				// Ӣ��
{
	// ͨ����ļӢ�ۻ��
	EAddHeroSoulType_RecruitHero = EAddPropType_Last,
	// ͨ��ϵͳ���ͻ��
	EAddHeroSoulType_System,
};

enum DecreaseHeroSoulType
{
	// ͨ����������
	EDecreaseHeroSoulType_TrainHeroSoul = 1,	
	// ͨ���ϳ�Ӣ������
	EDecreaseHeroSoulType_RecruitHeroSoul,		
};

enum AddHeroType				// Ӣ��
{
	// ͨ��ϵͳ���ͻ��
	EAddHeroType_System = EAddPropType_Last,
	// ͨ����ļӢ�ۻ��
	EAddHeroType_RecruitHero,		
	// ͨ���ϳ�Ӣ����
	EAddHeroType_RecruitHeroSoul,	
	// ͨ���ʼ����
	EAddHeroType_Msg,			
	// ����ʹ��	
	EAddHeroType_ItemUse,			
};

enum AddSkillChipType					// ������Ƭ
{
	// ͨ��������
	EAddSkillChipType_Rob = EAddPropType_Last,

};

enum DecreaseSkillChipType
{
	// �ϳ�����
	EDecreaseSkillChipType_ComposeSkill = 1,
	// ������
	EDecreaseSkillChipType_Rob,
};

//����
enum AddVigourType
{
	// ��ʱ�ظ�
	EAddVigourType_Recover = EAddPropType_Last,
	// ��ҹ�����
	EAddVigourType_Gold,
};

enum DecreaseVigourType
{
	// ħ�������Ἴ����Ƭ
	DecreaseVigourType_RobSkillChip = 1,
	// ��ս������
	DecreaseVigourType_ChallengeAthletics,
	// ͨ��GM�����޸�
	DecreaseVigourType_GM,
};

// ����
enum AddStaminaType
{
	// ��ʱ�ظ�
	AddStaminaType_Recover = EAddPropType_Last,
	// ��ҹ�����
	AddStaminaType_Gold,
};

enum DecreaseStaminaType
{
	// ����
	DecreaseStaminaType_Copy = 1,
	// ��ս������
	DecreaseStaminaType_ChallengeAthletics,
	// ͨ��GM�����޸�
	DecreaseStaminaType_GM,
};

#endif