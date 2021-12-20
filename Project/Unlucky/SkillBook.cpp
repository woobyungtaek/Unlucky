#include "pch.h"
#define  SKILL_COUNT 24

class Weapon;
class Enemy;

void (*SkillBook::SkillArray[22])(BattleObject* pCaster, BattleObject* pTarget);

// ��ų �迭 ���� �Լ�
void SkillBook::CreateSkillArray()
{
	SkillArray[0]  = &EmptySkill;
	SkillArray[1]  = &Next_Defense;
	SkillArray[2]  = &Next_CounterAttack;
	SkillArray[3]  = &IncreaseAttackPower_20;
	SkillArray[4]  = &IncreaseAttackPower_50;
	SkillArray[5]  = &Next_IncreaseBrokenRate_5;
	SkillArray[6]  = &Next_IncreaseBrokenRate_10;
	SkillArray[7]  = &Next_IncreaseAttackPower_20;
	SkillArray[8]  = &Next_IncreaseAttackPower_50;
	SkillArray[9]  = &DrainHPByAttackPower;
	SkillArray[10] = &Next_DecreaseTargetAttackPow_30;
	SkillArray[11] = &Next_DecreaseTargetAttackPow_50;
	SkillArray[12] = &Next_DecreaseMyWeaponDestroyPercent_10;
	SkillArray[13] = &Next_DecreaseMyWeaponDestroyPercent_20;
	SkillArray[14] = &DecreaseHP_10;
	SkillArray[15] = &DecreaseHP_20;
	SkillArray[16] = &Next_GetLandomTargetWeapon_10;
	SkillArray[17] = &Next_GetLandomTargetWeapon_20;
	SkillArray[18] = &GetRandomWeapon_10;
	SkillArray[19] = &Next_IncreaseBrokenRate_20_AttackPower_50;
	SkillArray[20] = &Next_IncreaseBrokenRate_30_AttackPower_100;
	SkillArray[21] = &Next_IncreaseTargetAttackPow_20;

	//SkillArray[22] = &��� �ߵ� ������ 100; // ���濡�� 100 ������
	//SkillArray[23] = &��� �ߵ� ������ 150; // ���濡�� 150 ������
}

// ��ų ���� �Լ� : ����
void SkillBook::SetSkillAtWeapon(Weapon* mWeapon)
{
	// Weapon �� �ν��Ͻ� �����( ���ʴ�� ��������...����? �ƴѵ� �ѹ����� ���ָ� �ɰŰ�����)
	if (mWeapon->SkillNum < 0 || mWeapon->SkillNum >= SKILL_COUNT)
	{
		mWeapon->SkillFunc = *(&SkillArray[0]);
		return;
	}
	mWeapon->SkillFunc = *(&SkillArray[mWeapon->SkillNum]);
}

// ��ų ���� �Լ� : ��
void SkillBook::SetPhaseSkillAtEnemy(Enemy* enemy)
{
	enemy->PhaseSkillVec.push_back(SkillArray[0]);
	int loopCount = enemy->SkillIndexVec.size();
	for (int index = 0; index < loopCount; index++)
	{
		int idxNum = enemy->SkillIndexVec[index];
		enemy->PhaseSkillVec.push_back(SkillArray[idxNum]);
	}
}

// ��ų ���� Ȯ�� üũ
bool SkillBook::IsSuccess(float rate)
{
	//�Ҽ��� 2�ڸ� Ȯ��
	float result;
	result = (float)(rand() % 10000);
	result /= 100;

	wcout << endl << L"[System][Ȯ�� ���][��ų] ���� ���� : " << result << L" / Ȯ�� : " << rate;
	if (result <= rate)
	{
		//����
		wcout << L"[����]"<<endl;
		return true;
	}
	
	//����
	wcout << L"[����]" << endl;
	return false;
}

#pragma region ��ų : ����

// 000�� ���� ��ų�Լ�
void SkillBook::EmptySkill(BattleObject* pCaster, BattleObject* pTarget)
{
	//wcout << L"�ƹ��ϵ� �Ͼ�� ����" << endl;
}


/// �̹� �Ͽ� ��� �� ��ų ����

// 01�� ���
void SkillBook::Defense(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"��� �÷��� On" << endl;

	// ��� �÷���On
	pCaster->IsBlock = true;
}

// 02�� �ݰ�
void SkillBook::CounterAttack(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"�ݰ� �÷��� On" << endl;

	//ī���� �÷���(50%�� Ȯ�� ����)
	pCaster->IsCounter = true;
}

// 03�� [�̹� ��] ���ݷ� ���� 20%
void SkillBook::IncreaseAttackPower_20(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"���ݷ� 20% ����" << endl;

	// ���� ���⿡ 20%�� ���ݷ� �߰�
	pCaster->AdditionalPowerRate += 0.2;
}

// 04�� [�̹� ��] ���ݷ� ���� 50%
void SkillBook::IncreaseAttackPower_50(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"���ݷ� 50% ����" << endl;

	// ���� ���⿡ 50%�� ���ݷ� �߰�
	pCaster->AdditionalPowerRate += 0.5;

}

// 05�� [50% Ȯ��] ��� ���� �ı� Ȯ�� +5%
void SkillBook::IncreaseBrokenRate_5(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"��� ���� �ı� Ȯ�� 5% ����" << endl;

	// ������ �ı�Ȯ�� 5% ���� ����
	pTarget->AdditionalBrokenRate +=  5;
}

// 06�� [50% Ȯ��] ��� ���� �ı� Ȯ�� +10%
void SkillBook::IncreaseBrokenRate_10(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"��� ���� �ı� Ȯ�� 10% ����" << endl;

	// ������ �ı�Ȯ�� 10% ���� ����
	pTarget->AdditionalBrokenRate += 10;
}

// 7, 8 �� ������ ��ų > 3, 4�� �ߺ� ����

// 09�� [�̹� ��] ����
void SkillBook::DrainHPByAttackPower(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"���� ���� On" << endl;

	// ���� ������ ������ ��ŭ ȸ���̱� ������
	pCaster->IsDrain = true;
}

// 10�� ������ ���ݷ� 30% ����
void SkillBook::DecreaseTargetAttackPow_30(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"������ ���ݷ� 30% ����" << endl;

	// ���������� ������ ���ݷ¿� 30% ����
	pTarget->AdditionalPowerRate -= 0.3;
}

// 11�� ������ ���ݷ� 50% ����
void SkillBook::DecreaseTargetAttackPow_50(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"������ ���ݷ� 50% ����" << endl;

	// ������ ���������� ������ ���ݷ¿� 50% ����
	pTarget->AdditionalPowerRate -= 0.5;
}

// 12�� [50% Ȯ��] �ڽ��� ���� �ı� Ȯ���� 10% ����
void SkillBook::DecreaseMyWeaponDestroyPercent_10(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"���� �ı� Ȯ�� 10% ����" << endl;

	pCaster->AdditionalBrokenRate -= 10;
}

// 13�� [50% Ȯ��] �ڽ��� ���� �ı� Ȯ���� 20% ����
void SkillBook::DecreaseMyWeaponDestroyPercent_20(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"���� �ı� Ȯ�� 20% ����" << endl;

	pCaster->AdditionalBrokenRate -= 20;
}

// 14�� [�̹� ��][50% Ȯ��] HP�� 10% �����Ѵ�
void SkillBook::DecreaseHP_10(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"HP 10% ����" << endl;

	// ��Ʋ�Ŵ������� ü�� ���ҽ����ֱ�
	pCaster->IncreaseHPValue -= (pCaster->HP * 0.1);
}

// 15�� [�̹� ��][50% Ȯ��] HP�� 20% �����Ѵ�
void SkillBook::DecreaseHP_20(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"HP 20% ����" << endl;

	// ��Ʋ�Ŵ������� ü�� ���ҽ����ֱ�
	pCaster->IncreaseHPValue -= (pCaster->HP * 0.2);
}

// ���� ��ġ�� Base��ų
void SkillBook::StealWeaponBase(float rate, BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(rate)) { return; }

	wcout << rate <<L"% Ȯ�� ���� ��ġ��" << endl;

	int weaponCnt = pTarget->pWeaponVec.size();

	vector<int> selectVec;
	for (int index = 0; index < weaponCnt; index++)
	{
		// ���� ���� ���� ������
		if (index == pTarget->SelectWeaponIndex) { continue; }

		// ��ȣ �ɸ� ���� ������
		if (pTarget->pWeaponVec[index]->BlessCount > 0) { continue; }

		selectVec.push_back(index);
	}

	if (selectVec.size() <= 0)
	{
		wcout << L"[System] ��ĥ �� �ִ� ���Ⱑ �����ϴ�." << endl;
		return;
	}

	// ������ ���� ����
	int randNum = rand() % selectVec.size();
	int weaponIndex = selectVec[randNum];
	Weapon* pWeapon = pTarget->pWeaponVec[weaponIndex];
	pWeapon->PrintWeaponInfo();

	pCaster->LootWeapon(pWeapon->Copy());
	pTarget->DestroyWeaponByIndex(weaponIndex);

	// ���⸦ �������� �ε����� �ٲ��.
	// ������ ���Ⱑ ������ ���⺸�� �տ� �ִ� ���
	// ������ ������ �ε����� -1 �Ѵ�.
	if (pTarget->SelectWeaponIndex > weaponIndex)
	{
		pTarget->SelectWeaponIndex -= 1;
	}
}

// 16�� [10% Ȯ��] ���� ��ġ��
void SkillBook::StealWeapon_10(BattleObject* pCaster, BattleObject* pTarget)
{
	StealWeaponBase(10, pCaster, pTarget);
}

// 17�� [20% Ȯ��] ���� ��ġ��
void SkillBook::StealWeapon_20(BattleObject* pCaster, BattleObject* pTarget)
{
	StealWeaponBase(20, pCaster, pTarget);
}

// 18�� [�̹� ��] [10% Ȯ��] ��ü ������ ���� 1�� ȹ��
void SkillBook::GetRandomWeapon_10(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(10)) { return; }
	wcout << L"10% Ȯ�� ���� �̱�" << endl;

	// ���� �� ���� �߿��� �Ѱ� �̱�
	int randNum = rand() % WeaponManager::GetInstance()->GetAllWeaponCount();
	Weapon* weapon = WeaponManager::GetInstance()->GetWeaponCopyByIndex(randNum);
	pCaster->pWeaponVec.push_back(weapon);
	weapon->PrintWeaponInfo();
}

// �ı� Ȯ��, ���ⵥ���� ���� ��ų Base
void SkillBook::IncreaseBrokenRateAttackPowerBase(float brokenRate, float powerRate, BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"�ı� Ȯ��"<< brokenRate <<L" % ���� ������ "<< powerRate * 100 <<L"% ����" << endl;
	pCaster->AdditionalBrokenRate += brokenRate;
	pCaster->AdditionalPowerRate += powerRate;
}

// 19�� �ı� Ȯ���� 20% ����, ���� �������� 50% ����
void SkillBook::Increase_BrokenRate_20_AttackPower_50(BattleObject* pCaster, BattleObject* pTarget)
{
	IncreaseBrokenRateAttackPowerBase(20, 0.5, pCaster, pTarget);
}

// 20�� �ڽ��� ���� �ı� Ȯ���� 30% �����ϰ�, �ڽ��� ���� �������� 100% �����Ѵ�
void SkillBook::Increase_BrokenRate_30_AttackPower_100(BattleObject* pCaster, BattleObject* pTarget)
{
	IncreaseBrokenRateAttackPowerBase(30,1, pCaster, pTarget);
}

// 21�� [50% Ȯ��] �ڽ��� �޴� �������� 20% ����
void SkillBook::IncreaseTargetAttackPow_20(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"�޴� ������ 20% ����" << endl;

	// Ÿ���� ���� ���� ���ݷ� 20% ����
	pTarget->AdditionalPowerRate += 0.2;
}

void SkillBook::DirectDamage(float damage, BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"���� ������ "<< damage << endl;
	pTarget->HP -= damage;
}

// 22�� ���� ������ 100
void SkillBook::DirectDamage_100(BattleObject* pCaster, BattleObject* pTarget)
{
	DirectDamage(100, pCaster, pTarget);
}

// 23�� ���� ������ 150
void SkillBook::DirectDamage_150(BattleObject* pCaster, BattleObject* pTarget)
{
	DirectDamage(100, pCaster, pTarget);
}


/// ���� �Ͽ� ��� �� ��ų �˷���
// 01�� �����Ͽ� 100% Ȯ���� ���� ������ ����ϰ�, �ش� ������ ���� �ı� Ȯ���� 20% ����
void SkillBook::Next_Defense(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[���� ��] ���� ������ ���, ���� ������ �ı� Ȯ���� 20%���� �Ѵ�." << endl;
	pCaster->NextSkillFunction = &Defense;
	pCaster->pWeaponVec[pCaster->SelectWeaponIndex]->BrokenRate += 20;
}

// 02�� ���� �Ͽ� 50% Ȯ���� ī���� ����
void SkillBook::Next_CounterAttack(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50))
	{
		pCaster->NextSkillFunction = nullptr;
		return;
	}
	wcout << L"[���� ��] 50% Ȯ�� ī���� ����" << endl;
	pCaster->NextSkillFunction = &CounterAttack;
}

// 05�� ���� �Ͽ� 50%�� Ȯ���� ���� ������ ���� �ı� Ȯ���� 5% ����
void SkillBook::Next_IncreaseBrokenRate_5(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[���� ��] 50% ��빫�� �ı�Ȯ�� 5% ����" << endl;

	pCaster->NextSkillFunction = &IncreaseBrokenRate_5;
}

// 06�� ���� �Ͽ� 50%�� Ȯ���� ���� ������ ���� �ı� Ȯ���� 10% ����
void SkillBook::Next_IncreaseBrokenRate_10(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[���� ��] 50% ��빫�� �ı�Ȯ�� 10% ����" << endl;

	pCaster->NextSkillFunction = &IncreaseBrokenRate_10;
}

// 07�� ���� �Ͽ� ������ �޴� �������� 20% ����
void SkillBook::Next_IncreaseAttackPower_20(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[���� ��] ���ݷ� 20% ����" << endl;

	pCaster->NextSkillFunction = &IncreaseAttackPower_20;
}

// 08�� ���� �Ͽ� ������ �޴� �������� 50% ����
void SkillBook::Next_IncreaseAttackPower_50(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[���� ��] ���ݷ� 50% ����" << endl;

	pCaster->NextSkillFunction = &IncreaseAttackPower_50;
}

// 10�� ���� �Ͽ� ������ ���ݷ� 30% ����
void SkillBook::Next_DecreaseTargetAttackPow_30(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[���� ��] ����� ���ݷ� 30% ����" << endl;

	pCaster->NextSkillFunction = &DecreaseTargetAttackPow_30;
}

// 11�� ���� �Ͽ� ������ ���ݷ� 50% ����
void SkillBook::Next_DecreaseTargetAttackPow_50(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[���� ��] ����� ���ݷ� 50% ����" << endl;

	pCaster->NextSkillFunction = &DecreaseTargetAttackPow_50;
}

// 12�� ���� �Ͽ� 50%�� Ȯ���� �ڽ��� ���� �ı� Ȯ���� 10% ����
void SkillBook::Next_DecreaseMyWeaponDestroyPercent_10(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[���� ��] ���� �ı� Ȯ�� 10% ����" << endl;

	pCaster->NextSkillFunction = &DecreaseMyWeaponDestroyPercent_10;
}

// 13�� ���� �Ͽ� 50%�� Ȯ���� �ڽ��� ���� �ı� Ȯ���� 20% ����
void SkillBook::Next_DecreaseMyWeaponDestroyPercent_20(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[���� ��] �����ı�Ȯ�� 20% ����" << endl;

	pCaster->NextSkillFunction = &DecreaseMyWeaponDestroyPercent_20;
}

// 16�� ���� �Ͽ� 50%�� Ȯ���� ������ ������ ���� �߿��� �ϳ��� �����´�.
void SkillBook::Next_GetLandomTargetWeapon_10(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[���� ��] ������ ���� �� �ϳ� ��ƿ!" << endl;

	pCaster->NextSkillFunction = &StealWeapon_10;
}

// 17�� ���� �Ͽ� 20%�� Ȯ���� ������ ������ ���� �߿��� �ϳ��� �����´�.
void SkillBook::Next_GetLandomTargetWeapon_20(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[���� ��] ������ ���� �� �ϳ� ��ƿ!" << endl;

	pCaster->NextSkillFunction = &StealWeapon_20;
}

// 19�� ���� �Ͽ� �ڽ��� ���� �ı� Ȯ���� 20% �����ϰ�, �ڽ��� ���� �������� 150% �����Ѵ�
void SkillBook::Next_IncreaseBrokenRate_20_AttackPower_50(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[���� ��] ���� �ı� Ȯ�� 20% ���� & ���ݷ� 50% ����" << endl;

	pCaster->NextSkillFunction = &Increase_BrokenRate_20_AttackPower_50;
}

// 20�� ���� �Ͽ� �ڽ��� ���� �ı� Ȯ���� 30% �����ϰ�, �ڽ��� ���� �������� 200% �����Ѵ�
void SkillBook::Next_IncreaseBrokenRate_30_AttackPower_100(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[���� ��] ���� �ı� Ȯ�� 20% ���� & ���ݷ� 50% ����" << endl;

	pCaster->NextSkillFunction = &Increase_BrokenRate_30_AttackPower_100;
}

// 21�� ���� �Ͽ� �ڽ��� �޴� �������� 20% ����
void SkillBook::Next_IncreaseTargetAttackPow_20(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[���� ��] ����� ���ݷ� 20% ����" << endl;

	pCaster->NextSkillFunction = &IncreaseTargetAttackPow_20;
}

#pragma endregion
