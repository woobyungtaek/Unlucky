#pragma once

enum class EEnemyGrade
{
	Normal = 0,
	Veteran,
	Hero,
	GradeCount
};

enum class EEnemyAction
{
	Attack = 0,
	Defence,
	ActionCount
};

class Enemy : public BattleObject
{
public:
	Enemy();
	Enemy(EEnemyGrade grade, int hp, int weaponCount);
	~Enemy();

public:
	// 몬스터 등급
	EEnemyGrade Grade;

	// 몬스터 이름
	CString Name;
	CString FileName;

	int BlessWeaponIndex;

	vector<int> WeaponIndexVec;

	vector<int> SkillIndexVec;

	// 몬스터 패턴
	int phaseIndex;
	int patternIndex;
	vector<vector<int>> PatternVec;
	vector<float> PhaseHPVec;

	vector<void(*)(BattleObject* pCaster, BattleObject* pTarget)> PhaseSkillVec;

	//전투 진행 값S
	EEnemyAction CurrentAction;

public:
	//몬스터 실행할 패턴
	int GetCurrentPattern();

	bool SetPhaseIndex();

	void GetBlessWeapon();

	void UsePhaseSkill(BattleObject* pTarget);

	//복사
	Enemy* Copy();
};

