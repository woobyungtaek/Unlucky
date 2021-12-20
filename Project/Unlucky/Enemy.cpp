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
		//다시 처음 패턴으로 간다.
		patternIndex = 0;
	}

	return PatternVec[phaseIndex][patternIndex];
}

bool Enemy::SetPhaseIndex()
{
	//현재의 HP에 따라서 페이즈를 변경한다. 
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
		wcout << L"[System] " << PhaseHPVec[phaseIndex] << L"% 이하 페이즈 발동" << endl;
		phaseIndex = checkPhase;
		patternIndex = 0;

		//페이즈 함수 교체

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
	wcout << endl << L"[System] 여신의 가호 무기를 뽑음" << endl;
}

void Enemy::UsePhaseSkill(BattleObject* pTarget)
{
	if (phaseIndex <= 0 || phaseIndex >= this->PhaseSkillVec.size()) { return; }
	wcout << L"[System] 적 "<< phaseIndex <<L"페이즈 스킬 : ";
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
