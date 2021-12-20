#include "pch.h"

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}

Weapon* Weapon::Copy()
{
	Weapon* copy = new Weapon();
	copy->Name = Name;
	copy->AttackPow = AttackPow;
	copy->BrokenRate = BrokenRate;
	copy->GradeType = GradeType;
	copy->WeaponType = WeaponType;
	copy->SkillNum = SkillNum;
	copy->SkillFunc = SkillFunc;
	copy->BlessCount = 0;// 카피시엔 가호 다 때고?
	copy->Desc = Desc;
	copy->SkillDesc = SkillDesc;
	copy->FileName = FileName;
	return copy;
}

void Weapon::PrintWeaponInfo()
{
	wcout<< endl << L"----------------------------------------------------------------------" << endl;
	wcout<< L"[Power : " << AttackPow << L"]\t[Destroy : " << BrokenRate << L"% ]"
		<<L"\t[Bless : "<<BlessCount<<L"]"<<endl<< L"[" << (const wchar_t*)Name <<L"]"<< endl << (const wchar_t*)Desc <<endl;
	wcout << L"----------------------------------------------------------------------" << endl;
}
