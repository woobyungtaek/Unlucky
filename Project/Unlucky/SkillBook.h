#pragma once

class SkillBook
{
private:
	static void (*SkillArray[])(BattleObject* pCaster, BattleObject* pTarget);
public:
	// ��ų �迭 ���� �Լ�
	static void CreateSkillArray();

	// ��ų�� Weapon�� SkillNum ���� ������ �Լ�
	static void SetSkillAtWeapon(Weapon* weapon);

	// ��ų�� Enemy�� Phase ��ų�� �߰�
	static void SetPhaseSkillAtEnemy(Enemy* enemy);

	static bool IsSuccess(float rate);

	// 000�� ���� ��ų�Լ�
	static void EmptySkill(BattleObject* pCaster, BattleObject* pTarget);

	/// ��ų��� ����
	// 01�� ���� ������ ����ϰ�, �ش� ������ ���� �ı� Ȯ���� 20% ����
	static void Defense(BattleObject* pCaster, BattleObject* pTarget);
	
	// 02�� [50% Ȯ��] �ڽ��� ���� ������, ������ ���� ��������ŭ�� ���ظ� ��뿡�� �ش�
	static void CounterAttack(BattleObject* pCaster, BattleObject* pTarget);

	// 03�� [�̹� ��] �ڽ��� ���濡�� �ִ� �������� 120% ����
	static void IncreaseAttackPower_20(BattleObject* pCaster, BattleObject* pTarget);

	// 04�� [�̹� ��] �ڽ��� ���濡�� �ִ� �������� 150% ����
	static void IncreaseAttackPower_50(BattleObject* pCaster, BattleObject* pTarget);

	// 05�� [50%�� Ȯ��] ���� ������ ���� �ı� Ȯ���� 5% ����
	static void IncreaseBrokenRate_5(BattleObject* pCaster, BattleObject* pTarget);

	// 06�� [50%�� Ȯ��] ���� ������ ���� �ı� Ȯ���� 10% ����
	static void IncreaseBrokenRate_10(BattleObject* pCaster, BattleObject* pTarget);

	// 07�� ������ �޴� �������� 120% ����
	static void IncreaseAttackPow_120(BattleObject* pCaster, BattleObject* pTarget);

	// 08�� ������ �޴� �������� 150% ����
	static void IncreaseAttackPow_150(BattleObject* pCaster, BattleObject* pTarget);

	// 09�� [�̹� ��] �ڽ��� ���濡�� ���� ��������ŭ �ڽ��� HP�� ȸ��
	static void DrainHPByAttackPower(BattleObject* pCaster, BattleObject* pTarget);

	// 10�� ������ ���� ������ 30% ����
	static void DecreaseTargetAttackPow_30(BattleObject* pCaster, BattleObject* pTarget);

	// 11�� ������ ���� ������ 50% ����
	static void DecreaseTargetAttackPow_50(BattleObject* pCaster, BattleObject* pTarget);

	// 12�� [50%�� Ȯ��] �ڽ��� ���� �ı� Ȯ���� 10% ����
	static void DecreaseMyWeaponDestroyPercent_10(BattleObject* pCaster, BattleObject* pTarget);

	// 13�� [50%�� Ȯ��] �ڽ��� ���� �ı� Ȯ���� 20% ����
	static void DecreaseMyWeaponDestroyPercent_20(BattleObject* pCaster, BattleObject* pTarget);

	// 14�� [�̹� ��] [50% Ȯ��] �ڽ��� HP�� 10% �����Ѵ�
	static void DecreaseHP_10(BattleObject* pCaster, BattleObject* pTarget);

	// 15�� [�̹� ��] [50% Ȯ��] �ڽ��� HP�� 20% �����Ѵ�
	static void DecreaseHP_20(BattleObject* pCaster, BattleObject* pTarget);

	static void StealWeaponBase(float rate, BattleObject* pCaster, BattleObject* pTarget);

	// 16�� [10% Ȯ��] ������ ������ ���� �߿��� �ϳ��� �����´�.
	static void StealWeapon_10(BattleObject* pCaster, BattleObject* pTarget);

	// 17�� [20% Ȯ��] ������ ������ ���� �߿��� �ϳ��� �����´�.
	static void StealWeapon_20(BattleObject* pCaster, BattleObject* pTarget);

	// 18�� [�̹� ��] [10% Ȯ��] ��ü ���� ����Ʈ �߿��� �ϳ��� �����´�.
	static void GetRandomWeapon_10(BattleObject* pCaster, BattleObject* pTarget);

	static void IncreaseBrokenRateAttackPowerBase(float brokenRate, float powerRate, BattleObject* pCaster, BattleObject* pTarget);

	// 19�� �ڽ��� ���� �ı� Ȯ���� 20% �����ϰ�, �ڽ��� ���� �������� 150% �����Ѵ�
	static void Increase_BrokenRate_20_AttackPower_50(BattleObject* pCaster, BattleObject* pTarget);

	// 20�� �ڽ��� ���� �ı� Ȯ���� 30% �����ϰ�, �ڽ��� ���� �������� 200% �����Ѵ�
	static void Increase_BrokenRate_30_AttackPower_100(BattleObject* pCaster, BattleObject* pTarget);

	// 21�� [50% Ȯ��] �ڽ��� �޴� �������� 20% ����
	static void IncreaseTargetAttackPow_20(BattleObject* pCaster, BattleObject* pTarget);

	static void DirectDamage(float damage, BattleObject* pCaster, BattleObject* pTarget);

	// 22�� ���� ������ 100
	static void DirectDamage_100(BattleObject* pCaster, BattleObject* pTarget);

	// 22�� ���� ������ 150
	static void DirectDamage_150(BattleObject* pCaster, BattleObject* pTarget);


	/// �����Ͽ� ����� ��ų �˷���
	// 00�� ���� �Ͽ� 100% Ȯ���� ���� ������ ����ϰ�, �ش� ������ ���� �ı� Ȯ���� 20% ����
	static void Next_Defense(BattleObject* pCaster, BattleObject* pTarget);

	// 01�� ���� �Ͽ� 50% Ȯ���� �ڽ��� ���� ������, ������ ���� ��������ŭ�� ���ظ� ��뿡�� �ش�
	static void Next_CounterAttack(BattleObject* pCaster, BattleObject* pTarget);

	// 04�� ���� �Ͽ� 5%�� Ȯ���� ���� ������ ���� �ı� Ȯ���� 5% ����
	static void Next_IncreaseBrokenRate_5(BattleObject* pCaster, BattleObject* pTarget);
	
	// 06�� ���� �Ͽ� 10%�� Ȯ���� ���� ������ ���� �ı� Ȯ���� 10% ����
	static void Next_IncreaseBrokenRate_10(BattleObject* pCaster, BattleObject* pTarget);
	
	// 07�� ���� �Ͽ� ������ �޴� �������� 120% ����
	static void Next_IncreaseAttackPower_20(BattleObject* pCaster, BattleObject* pTarget);

	// 08�� ���� �Ͽ� ������ �޴� �������� 150% ����
	static void Next_IncreaseAttackPower_50(BattleObject* pCaster, BattleObject* pTarget);

	// 10�� ���� �Ͽ� ������ ���ݷ� 30% ����
	static void Next_DecreaseTargetAttackPow_30(BattleObject* pCaster, BattleObject* pTarget);

	// 11�� ���� �Ͽ� ������ ���ݷ� 50% ����
	static void Next_DecreaseTargetAttackPow_50(BattleObject* pCaster, BattleObject* pTarget);

	// 12�� ���� �Ͽ� 50%�� Ȯ���� �ڽ��� ���� �ı� Ȯ���� 10% ����
	static void Next_DecreaseMyWeaponDestroyPercent_10(BattleObject* pCaster, BattleObject* pTarget);

	// 13�� ���� �Ͽ� 30%�� Ȯ���� �ڽ��� ���� �ı� Ȯ���� 20% ����
	static void Next_DecreaseMyWeaponDestroyPercent_20(BattleObject* pCaster, BattleObject* pTarget);

	// 16�� ���� �Ͽ� 5%�� Ȯ���� ������ ������ ���� �߿��� �ϳ��� �����´�.
	static void Next_GetLandomTargetWeapon_10(BattleObject* pCaster, BattleObject* pTarget);

	// 17�� ���� �Ͽ� 3%�� Ȯ���� ������ ������ ���� �߿��� �ϳ��� �����´�.
	static void Next_GetLandomTargetWeapon_20(BattleObject* pCaster, BattleObject* pTarget);

	// 19�� ���� �Ͽ� �ڽ��� ���� �ı� Ȯ���� 20% �����ϰ�, �ڽ��� ���� �������� 150% �����Ѵ�
	static void Next_IncreaseBrokenRate_20_AttackPower_50(BattleObject* pCaster, BattleObject* pTarget);

	// 20�� ���� �Ͽ� �ڽ��� ���� �ı� Ȯ���� 30% �����ϰ�, �ڽ��� ���� �������� 200% �����Ѵ�
	static void Next_IncreaseBrokenRate_30_AttackPower_100(BattleObject* pCaster, BattleObject* pTarget);

	// 21�� ���� �Ͽ� �ڽ��� �޴� �������� 20% ����
	static void Next_IncreaseTargetAttackPow_20(BattleObject* pCaster, BattleObject* pTarget);
};