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
	EWeaponGrade	GradeType; //등급
	EWeaponType		WeaponType;
	int				SkillNum;	
	int				BlessCount; // 가호
	CString			Desc;		
	CString			SkillDesc;		
	CString			FileName;	//파일네임

	// 스킬 함수 포인터 들어가야 함
	void (*SkillFunc)(BattleObject* pCaster, BattleObject* pTarget);

public:
	Weapon* Copy();

	void PrintWeaponInfo();
};

