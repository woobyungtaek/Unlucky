#pragma once
using namespace std;

class BattleObject;

class Weapon
{
public:
	Weapon();
	~Weapon();

public:
	CString			Name;		//
	float			AttackPow;
	float			BrokenRate;
	EWeaponGrade	GradeType; //���
	EWeaponType		WeaponType;
	int				SkillNum;	
	int				BlessCount; // ��ȣ
	CString			Desc;		
	CString			SkillDesc;		
	CString			FileName;	//���ϳ���

	// ��ų �Լ� ������ ���� ��
	void (*SkillFunc)(BattleObject* pCaster, BattleObject* pTarget);

public:
	Weapon* Copy();

	void PrintWeaponInfo();
};

