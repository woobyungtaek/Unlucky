#include "pch.h"
#define  SKILL_COUNT 24

class Weapon;
class Enemy;

void (*SkillBook::SkillArray[22])(BattleObject* pCaster, BattleObject* pTarget);

// 스킬 배열 설정 함수
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

	//SkillArray[22] = &즉시 발동 데미지 100; // 상대방에게 100 데미지
	//SkillArray[23] = &즉시 발동 데미지 150; // 상대방에게 150 데미지
}

// 스킬 설정 함수 : 무기
void SkillBook::SetSkillAtWeapon(Weapon* mWeapon)
{
	// Weapon 의 인스턴스 만들고( 차례대로 넣으려면...벡터? 아닌데 넘버링만 해주면 될거같은데)
	if (mWeapon->SkillNum < 0 || mWeapon->SkillNum >= SKILL_COUNT)
	{
		mWeapon->SkillFunc = *(&SkillArray[0]);
		return;
	}
	mWeapon->SkillFunc = *(&SkillArray[mWeapon->SkillNum]);
}

// 스킬 설정 함수 : 적
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

// 스킬 내부 확률 체크
bool SkillBook::IsSuccess(float rate)
{
	//소수점 2자리 확률
	float result;
	result = (float)(rand() % 10000);
	result /= 100;

	wcout << endl << L"[System][확률 결과][스킬] 뽑은 숫자 : " << result << L" / 확률 : " << rate;
	if (result <= rate)
	{
		//성공
		wcout << L"[성공]"<<endl;
		return true;
	}
	
	//실패
	wcout << L"[실패]" << endl;
	return false;
}

#pragma region 스킬 : 무기

// 000번 공백 스킬함수
void SkillBook::EmptySkill(BattleObject* pCaster, BattleObject* pTarget)
{
	//wcout << L"아무일도 일어나지 않음" << endl;
}


/// 이번 턴에 사용 할 스킬 설명

// 01번 방어
void SkillBook::Defense(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"방어 플래그 On" << endl;

	// 방어 플래그On
	pCaster->IsBlock = true;
}

// 02번 반격
void SkillBook::CounterAttack(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"반격 플래그 On" << endl;

	//카운터 플래그(50%의 확률 전제)
	pCaster->IsCounter = true;
}

// 03번 [이번 턴] 공격력 증가 20%
void SkillBook::IncreaseAttackPower_20(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"공격력 20% 증가" << endl;

	// 현재 무기에 20%의 공격력 추가
	pCaster->AdditionalPowerRate += 0.2;
}

// 04번 [이번 턴] 공격력 증가 50%
void SkillBook::IncreaseAttackPower_50(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"공격력 50% 증가" << endl;

	// 현재 무기에 50%의 공격력 추가
	pCaster->AdditionalPowerRate += 0.5;

}

// 05번 [50% 확률] 상대 무기 파괴 확률 +5%
void SkillBook::IncreaseBrokenRate_5(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"상대 무기 파괴 확률 5% 증가" << endl;

	// 무기의 파괴확률 5% 증가 적용
	pTarget->AdditionalBrokenRate +=  5;
}

// 06번 [50% 확률] 상대 무기 파괴 확률 +10%
void SkillBook::IncreaseBrokenRate_10(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"상대 무기 파괴 확률 10% 증가" << endl;

	// 무기의 파괴확률 10% 증가 적용
	pTarget->AdditionalBrokenRate += 10;
}

// 7, 8 은 다음턴 스킬 > 3, 4번 중복 내용

// 09번 [이번 턴] 흡혈
void SkillBook::DrainHPByAttackPower(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"흡혈 상태 On" << endl;

	// 최종 공격한 데미지 만큼 회복이기 때문에
	pCaster->IsDrain = true;
}

// 10번 상대방의 공격력 30% 감소
void SkillBook::DecreaseTargetAttackPow_30(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"상대방의 공격력 30% 감소" << endl;

	// 현재착용한 무기의 공격력에 30% 감소
	pTarget->AdditionalPowerRate -= 0.3;
}

// 11번 상대방의 공격력 50% 감소
void SkillBook::DecreaseTargetAttackPow_50(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"상대방의 공격력 50% 감소" << endl;

	// 상대방이 현재착용한 무기의 공격력에 50% 감소
	pTarget->AdditionalPowerRate -= 0.5;
}

// 12번 [50% 확률] 자신의 무기 파괴 확률이 10% 감소
void SkillBook::DecreaseMyWeaponDestroyPercent_10(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"무기 파괴 확률 10% 감소" << endl;

	pCaster->AdditionalBrokenRate -= 10;
}

// 13번 [50% 확률] 자신의 무기 파괴 확률이 20% 감소
void SkillBook::DecreaseMyWeaponDestroyPercent_20(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"무기 파괴 확률 20% 감소" << endl;

	pCaster->AdditionalBrokenRate -= 20;
}

// 14번 [이번 턴][50% 확률] HP가 10% 감소한다
void SkillBook::DecreaseHP_10(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"HP 10% 감소" << endl;

	// 배틀매니저에서 체력 감소시켜주기
	pCaster->IncreaseHPValue -= (pCaster->HP * 0.1);
}

// 15번 [이번 턴][50% 확률] HP가 20% 감소한다
void SkillBook::DecreaseHP_20(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"HP 20% 감소" << endl;

	// 배틀매니저에서 체력 감소시켜주기
	pCaster->IncreaseHPValue -= (pCaster->HP * 0.2);
}

// 무기 훔치기 Base스킬
void SkillBook::StealWeaponBase(float rate, BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(rate)) { return; }

	wcout << rate <<L"% 확률 무기 훔치기" << endl;

	int weaponCnt = pTarget->pWeaponVec.size();

	vector<int> selectVec;
	for (int index = 0; index < weaponCnt; index++)
	{
		// 착용 중인 무기 미포함
		if (index == pTarget->SelectWeaponIndex) { continue; }

		// 가호 걸린 무기 미포함
		if (pTarget->pWeaponVec[index]->BlessCount > 0) { continue; }

		selectVec.push_back(index);
	}

	if (selectVec.size() <= 0)
	{
		wcout << L"[System] 훔칠 수 있는 무기가 없습니다." << endl;
		return;
	}

	// 가져올 무기 선택
	int randNum = rand() % selectVec.size();
	int weaponIndex = selectVec[randNum];
	Weapon* pWeapon = pTarget->pWeaponVec[weaponIndex];
	pWeapon->PrintWeaponInfo();

	pCaster->LootWeapon(pWeapon->Copy());
	pTarget->DestroyWeaponByIndex(weaponIndex);

	// 무기를 가져오면 인덱스가 바뀐다.
	// 빼내온 무기가 선택한 무기보다 앞에 있는 경우
	// 선택한 무기의 인덱스를 -1 한다.
	if (pTarget->SelectWeaponIndex > weaponIndex)
	{
		pTarget->SelectWeaponIndex -= 1;
	}
}

// 16번 [10% 확률] 무기 훔치기
void SkillBook::StealWeapon_10(BattleObject* pCaster, BattleObject* pTarget)
{
	StealWeaponBase(10, pCaster, pTarget);
}

// 17번 [20% 확률] 무기 훔치기
void SkillBook::StealWeapon_20(BattleObject* pCaster, BattleObject* pTarget)
{
	StealWeaponBase(20, pCaster, pTarget);
}

// 18번 [이번 턴] [10% 확률] 전체 무기중 랜덤 1개 획득
void SkillBook::GetRandomWeapon_10(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(10)) { return; }
	wcout << L"10% 확률 무기 뽑기" << endl;

	// 무기 총 갯수 중에서 한개 뽑기
	int randNum = rand() % WeaponManager::GetInstance()->GetAllWeaponCount();
	Weapon* weapon = WeaponManager::GetInstance()->GetWeaponCopyByIndex(randNum);
	pCaster->pWeaponVec.push_back(weapon);
	weapon->PrintWeaponInfo();
}

// 파괴 확률, 무기데미지 증가 스킬 Base
void SkillBook::IncreaseBrokenRateAttackPowerBase(float brokenRate, float powerRate, BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"파괴 확률"<< brokenRate <<L" % 무기 데미지 "<< powerRate * 100 <<L"% 증가" << endl;
	pCaster->AdditionalBrokenRate += brokenRate;
	pCaster->AdditionalPowerRate += powerRate;
}

// 19번 파괴 확률이 20% 증가, 무기 데미지가 50% 증가
void SkillBook::Increase_BrokenRate_20_AttackPower_50(BattleObject* pCaster, BattleObject* pTarget)
{
	IncreaseBrokenRateAttackPowerBase(20, 0.5, pCaster, pTarget);
}

// 20번 자신의 무기 파괴 확률이 30% 증가하고, 자신의 무기 데미지가 100% 증가한다
void SkillBook::Increase_BrokenRate_30_AttackPower_100(BattleObject* pCaster, BattleObject* pTarget)
{
	IncreaseBrokenRateAttackPowerBase(30,1, pCaster, pTarget);
}

// 21번 [50% 확률] 자신이 받는 데미지가 20% 증가
void SkillBook::IncreaseTargetAttackPow_20(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50)) { return; }
	wcout << L"받는 데미지 20% 증가" << endl;

	// 타겟의 현재 무기 공격력 20% 증가
	pTarget->AdditionalPowerRate += 0.2;
}

void SkillBook::DirectDamage(float damage, BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"직접 데미지 "<< damage << endl;
	pTarget->HP -= damage;
}

// 22번 직접 데미지 100
void SkillBook::DirectDamage_100(BattleObject* pCaster, BattleObject* pTarget)
{
	DirectDamage(100, pCaster, pTarget);
}

// 23번 직접 데미지 150
void SkillBook::DirectDamage_150(BattleObject* pCaster, BattleObject* pTarget)
{
	DirectDamage(100, pCaster, pTarget);
}


/// 다음 턴에 사용 할 스킬 알려줌
// 01번 다음턴에 100% 확률로 상대방 공격을 방어하고, 해당 무기의 무기 파괴 확률이 20% 증가
void SkillBook::Next_Defense(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[다음 턴] 상대방 공격을 방어, 현재 무기의 파괴 확률이 20%증가 한다." << endl;
	pCaster->NextSkillFunction = &Defense;
	pCaster->pWeaponVec[pCaster->SelectWeaponIndex]->BrokenRate += 20;
}

// 02번 다음 턴에 50% 확률로 카운터 어택
void SkillBook::Next_CounterAttack(BattleObject* pCaster, BattleObject* pTarget)
{
	if (!IsSuccess(50))
	{
		pCaster->NextSkillFunction = nullptr;
		return;
	}
	wcout << L"[다음 턴] 50% 확률 카운터 어택" << endl;
	pCaster->NextSkillFunction = &CounterAttack;
}

// 05번 다음 턴에 50%의 확률로 상대방 무기의 무기 파괴 확률이 5% 증가
void SkillBook::Next_IncreaseBrokenRate_5(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[다음 턴] 50% 상대무기 파괴확률 5% 증가" << endl;

	pCaster->NextSkillFunction = &IncreaseBrokenRate_5;
}

// 06번 다음 턴에 50%의 확률로 상대방 무기의 무기 파괴 확률이 10% 증가
void SkillBook::Next_IncreaseBrokenRate_10(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[다음 턴] 50% 상대무기 파괴확률 10% 증가" << endl;

	pCaster->NextSkillFunction = &IncreaseBrokenRate_10;
}

// 07번 다음 턴에 상대방이 받는 데미지가 20% 증가
void SkillBook::Next_IncreaseAttackPower_20(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[다음 턴] 공격력 20% 증가" << endl;

	pCaster->NextSkillFunction = &IncreaseAttackPower_20;
}

// 08번 다음 턴에 상대방이 받는 데미지가 50% 증가
void SkillBook::Next_IncreaseAttackPower_50(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[다음 턴] 공격력 50% 증가" << endl;

	pCaster->NextSkillFunction = &IncreaseAttackPower_50;
}

// 10번 다음 턴에 상대방의 공격력 30% 감소
void SkillBook::Next_DecreaseTargetAttackPow_30(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[다음 턴] 상대의 공격력 30% 감소" << endl;

	pCaster->NextSkillFunction = &DecreaseTargetAttackPow_30;
}

// 11번 다음 턴에 상대방의 공격력 50% 감소
void SkillBook::Next_DecreaseTargetAttackPow_50(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[다음 턴] 상대의 공격력 50% 감소" << endl;

	pCaster->NextSkillFunction = &DecreaseTargetAttackPow_50;
}

// 12번 다음 턴에 50%의 확률로 자신의 무기 파괴 확률이 10% 감소
void SkillBook::Next_DecreaseMyWeaponDestroyPercent_10(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[다음 턴] 무기 파괴 확률 10% 감소" << endl;

	pCaster->NextSkillFunction = &DecreaseMyWeaponDestroyPercent_10;
}

// 13번 다음 턴에 50%의 확률로 자신의 무기 파괴 확률이 20% 감소
void SkillBook::Next_DecreaseMyWeaponDestroyPercent_20(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[다음 턴] 무기파괴확률 20% 감소" << endl;

	pCaster->NextSkillFunction = &DecreaseMyWeaponDestroyPercent_20;
}

// 16번 다음 턴에 50%의 확률로 상대방이 소유한 무기 중에서 하나를 가져온다.
void SkillBook::Next_GetLandomTargetWeapon_10(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[다음 턴] 상대소유 무기 중 하나 스틸!" << endl;

	pCaster->NextSkillFunction = &StealWeapon_10;
}

// 17번 다음 턴에 20%의 확률로 상대방이 소유한 무기 중에서 하나를 가져온다.
void SkillBook::Next_GetLandomTargetWeapon_20(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[다음 턴] 상대소유 무기 중 하나 스틸!" << endl;

	pCaster->NextSkillFunction = &StealWeapon_20;
}

// 19번 다음 턴에 자신의 무기 파괴 확률이 20% 증가하고, 자신의 무기 데미지가 150% 증가한다
void SkillBook::Next_IncreaseBrokenRate_20_AttackPower_50(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[다음 턴] 무기 파괴 확률 20% 증가 & 공격력 50% 증가" << endl;

	pCaster->NextSkillFunction = &Increase_BrokenRate_20_AttackPower_50;
}

// 20번 다음 턴에 자신의 무기 파괴 확률이 30% 증가하고, 자신의 무기 데미지가 200% 증가한다
void SkillBook::Next_IncreaseBrokenRate_30_AttackPower_100(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[다음 턴] 무기 파괴 확률 20% 증가 & 공격력 50% 증가" << endl;

	pCaster->NextSkillFunction = &Increase_BrokenRate_30_AttackPower_100;
}

// 21번 다음 턴에 자신이 받는 데미지가 20% 증가
void SkillBook::Next_IncreaseTargetAttackPow_20(BattleObject* pCaster, BattleObject* pTarget)
{
	wcout << L"[다음 턴] 상대의 공격력 20% 증가" << endl;

	pCaster->NextSkillFunction = &IncreaseTargetAttackPow_20;
}

#pragma endregion
