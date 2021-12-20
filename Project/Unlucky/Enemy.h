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
	// ���� ���
	EEnemyGrade Grade;

	// ���� �̸�
	CString Name;
	CString FileName;

	int BlessWeaponIndex;

	vector<int> WeaponIndexVec;

	vector<int> SkillIndexVec;

	// ���� ����
	int phaseIndex;
	int patternIndex;
	vector<vector<int>> PatternVec;
	vector<float> PhaseHPVec;

	vector<void(*)(BattleObject* pCaster, BattleObject* pTarget)> PhaseSkillVec;

	//���� ���� ��S
	EEnemyAction CurrentAction;

public:
	//���� ������ ����
	int GetCurrentPattern();

	bool SetPhaseIndex();

	void GetBlessWeapon();

	void UsePhaseSkill(BattleObject* pTarget);

	//����
	Enemy* Copy();
};

