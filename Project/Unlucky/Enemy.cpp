#include "pch.h"

Enemy::Enemy()
{
}

Enemy::Enemy(EEnemyGrade grade, int hp, int weaponCount)
	: Grade(grade)
{
	HP = hp;
}

Enemy::~Enemy()
{
}

int Enemy::GetCurrentPattern()
{
	int phaseCount = PatternVec.size();

	if (phaseIndex >= phaseCount) { phaseIndex = phaseCount - 1; }

	int patternCount = PatternVec[phaseIndex].size();
	if (patternIndex >= patternCount)
	{
		//�ٽ� ó�� �������� ����.
		patternIndex = 0;
	}

	return PatternVec[phaseIndex][patternIndex];
}

bool Enemy::SetPhaseIndex()
{
	//������ HP�� ���� ����� �����Ѵ�. 
	int checkPhase = 0;
	int loopCount = PhaseHPVec.size();
	for (int index = 0; index < loopCount; index++)
	{
		float percent = PhaseHPVec[index] / 100;
		if (HP < MaxHP * percent)
		{
			checkPhase = index + 1;
		}
	}

	if (checkPhase <= phaseIndex)
	{
		return false;
	}

	if (checkPhase > phaseIndex)
	{
		wcout << L"[System] " << PhaseHPVec[phaseIndex] << L"% ���� ������ �ߵ�" << endl;
		phaseIndex = checkPhase;
		patternIndex = 0;

		//������ �Լ� ��ü

		return true;
	}

	return false;
}

void Enemy::GetBlessWeapon()
{
	Weapon* inst = WeaponManager::GetInstance()->GetWeaponCopyByIndex(BlessWeaponIndex);
	if (inst == nullptr) { return; }

	inst->BlessCount = 99999;

	pWeaponVec.push_back(inst);
	wcout << endl << L"[System] ������ ��ȣ ���⸦ ����" << endl;
}

void Enemy::UsePhaseSkill(BattleObject* pTarget)
{
	if (phaseIndex <= 0 || phaseIndex >= this->PhaseSkillVec.size()) { return; }
	wcout << L"[System] �� "<< phaseIndex <<L"������ ��ų : ";
	(this->PhaseSkillVec[phaseIndex])(this, pTarget);
}

Enemy* Enemy::Copy()
{
	Enemy* inst = new Enemy();
	inst->Grade = Grade;
	inst->Name = Name;
	inst->FileName = FileName;
	inst->HP = HP;
	inst->MaxHP = MaxHP;

	for (int index = 0; index < pWeaponVec.size(); index++)
	{
		inst->pWeaponVec.push_back(pWeaponVec[index]->Copy());
	}

	inst->SkillIndexVec = SkillIndexVec;
	inst->PhaseHPVec = PhaseHPVec;
	inst->PatternVec = PatternVec;

	inst->BlessWeaponIndex = BlessWeaponIndex;
	inst->PhaseSkillVec = PhaseSkillVec;

	return inst;
}
