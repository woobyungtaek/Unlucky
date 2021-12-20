#pragma once

class SkillBook
{
private:
	static void (*SkillArray[])(BattleObject* pCaster, BattleObject* pTarget);
public:
	// 스킬 배열 설정 함수
	static void CreateSkillArray();

	// 스킬을 Weapon의 SkillNum 으로 묶어줄 함수
	static void SetSkillAtWeapon(Weapon* weapon);

	// 스킬을 Enemy에 Phase 스킬을 추가
	static void SetPhaseSkillAtEnemy(Enemy* enemy);

	static bool IsSuccess(float rate);

	// 000번 공백 스킬함수
	static void EmptySkill(BattleObject* pCaster, BattleObject* pTarget);

	/// 스킬사용 구현
	// 01번 상대방 공격을 방어하고, 해당 무기의 무기 파괴 확률이 20% 증가
	static void Defense(BattleObject* pCaster, BattleObject* pTarget);
	
	// 02번 [50% 확률] 자신이 피해 입으면, 상대방의 무기 데미지만큼의 피해를 상대에게 준다
	static void CounterAttack(BattleObject* pCaster, BattleObject* pTarget);

	// 03번 [이번 턴] 자신이 상대방에게 주는 데미지가 120% 증가
	static void IncreaseAttackPower_20(BattleObject* pCaster, BattleObject* pTarget);

	// 04번 [이번 턴] 자신이 상대방에게 주는 데미지가 150% 증가
	static void IncreaseAttackPower_50(BattleObject* pCaster, BattleObject* pTarget);

	// 05번 [50%의 확률] 상대방 무기의 무기 파괴 확률이 5% 증가
	static void IncreaseBrokenRate_5(BattleObject* pCaster, BattleObject* pTarget);

	// 06번 [50%의 확률] 상대방 무기의 무기 파괴 확률이 10% 증가
	static void IncreaseBrokenRate_10(BattleObject* pCaster, BattleObject* pTarget);

	// 07번 상대방이 받는 데미지가 120% 증가
	static void IncreaseAttackPow_120(BattleObject* pCaster, BattleObject* pTarget);

	// 08번 상대방이 받는 데미지가 150% 증가
	static void IncreaseAttackPow_150(BattleObject* pCaster, BattleObject* pTarget);

	// 09번 [이번 턴] 자신이 상대방에게 입힌 데미지만큼 자신의 HP를 회복
	static void DrainHPByAttackPower(BattleObject* pCaster, BattleObject* pTarget);

	// 10번 상대방의 무기 데미지 30% 감소
	static void DecreaseTargetAttackPow_30(BattleObject* pCaster, BattleObject* pTarget);

	// 11번 상대방의 무기 데미지 50% 감소
	static void DecreaseTargetAttackPow_50(BattleObject* pCaster, BattleObject* pTarget);

	// 12번 [50%의 확률] 자신의 무기 파괴 확률이 10% 감소
	static void DecreaseMyWeaponDestroyPercent_10(BattleObject* pCaster, BattleObject* pTarget);

	// 13번 [50%의 확률] 자신의 무기 파괴 확률이 20% 감소
	static void DecreaseMyWeaponDestroyPercent_20(BattleObject* pCaster, BattleObject* pTarget);

	// 14번 [이번 턴] [50% 확률] 자신의 HP가 10% 감소한다
	static void DecreaseHP_10(BattleObject* pCaster, BattleObject* pTarget);

	// 15번 [이번 턴] [50% 확률] 자신의 HP가 20% 감소한다
	static void DecreaseHP_20(BattleObject* pCaster, BattleObject* pTarget);

	static void StealWeaponBase(float rate, BattleObject* pCaster, BattleObject* pTarget);

	// 16번 [10% 확률] 상대방이 소유한 무기 중에서 하나를 가져온다.
	static void StealWeapon_10(BattleObject* pCaster, BattleObject* pTarget);

	// 17번 [20% 확률] 상대방이 소유한 무기 중에서 하나를 가져온다.
	static void StealWeapon_20(BattleObject* pCaster, BattleObject* pTarget);

	// 18번 [이번 턴] [10% 확률] 전체 무기 리스트 중에서 하나를 가져온다.
	static void GetRandomWeapon_10(BattleObject* pCaster, BattleObject* pTarget);

	static void IncreaseBrokenRateAttackPowerBase(float brokenRate, float powerRate, BattleObject* pCaster, BattleObject* pTarget);

	// 19번 자신의 무기 파괴 확률이 20% 증가하고, 자신의 무기 데미지가 150% 증가한다
	static void Increase_BrokenRate_20_AttackPower_50(BattleObject* pCaster, BattleObject* pTarget);

	// 20번 자신의 무기 파괴 확률이 30% 증가하고, 자신의 무기 데미지가 200% 증가한다
	static void Increase_BrokenRate_30_AttackPower_100(BattleObject* pCaster, BattleObject* pTarget);

	// 21번 [50% 확률] 자신이 받는 데미지가 20% 증가
	static void IncreaseTargetAttackPow_20(BattleObject* pCaster, BattleObject* pTarget);

	static void DirectDamage(float damage, BattleObject* pCaster, BattleObject* pTarget);

	// 22번 직접 데미지 100
	static void DirectDamage_100(BattleObject* pCaster, BattleObject* pTarget);

	// 22번 직접 데미지 150
	static void DirectDamage_150(BattleObject* pCaster, BattleObject* pTarget);


	/// 다음턴에 사용할 스킬 알려줌
	// 00번 다음 턴에 100% 확률로 상대방 공격을 방어하고, 해당 무기의 무기 파괴 확률이 20% 증가
	static void Next_Defense(BattleObject* pCaster, BattleObject* pTarget);

	// 01번 다음 턴에 50% 확률로 자신이 피해 입으면, 상대방의 무기 데미지만큼의 피해를 상대에게 준다
	static void Next_CounterAttack(BattleObject* pCaster, BattleObject* pTarget);

	// 04번 다음 턴에 5%의 확률로 상대방 무기의 무기 파괴 확률이 5% 증가
	static void Next_IncreaseBrokenRate_5(BattleObject* pCaster, BattleObject* pTarget);
	
	// 06번 다음 턴에 10%의 확률로 상대방 무기의 무기 파괴 확률이 10% 증가
	static void Next_IncreaseBrokenRate_10(BattleObject* pCaster, BattleObject* pTarget);
	
	// 07번 다음 턴에 상대방이 받는 데미지가 120% 증가
	static void Next_IncreaseAttackPower_20(BattleObject* pCaster, BattleObject* pTarget);

	// 08번 다음 턴에 상대방이 받는 데미지가 150% 증가
	static void Next_IncreaseAttackPower_50(BattleObject* pCaster, BattleObject* pTarget);

	// 10번 다음 턴에 상대방의 공격력 30% 감소
	static void Next_DecreaseTargetAttackPow_30(BattleObject* pCaster, BattleObject* pTarget);

	// 11번 다음 턴에 상대방의 공격력 50% 감소
	static void Next_DecreaseTargetAttackPow_50(BattleObject* pCaster, BattleObject* pTarget);

	// 12번 다음 턴에 50%의 확률로 자신의 무기 파괴 확률이 10% 감소
	static void Next_DecreaseMyWeaponDestroyPercent_10(BattleObject* pCaster, BattleObject* pTarget);

	// 13번 다음 턴에 30%의 확률로 자신의 무기 파괴 확률이 20% 감소
	static void Next_DecreaseMyWeaponDestroyPercent_20(BattleObject* pCaster, BattleObject* pTarget);

	// 16번 다음 턴에 5%의 확률로 상대방이 소유한 무기 중에서 하나를 가져온다.
	static void Next_GetLandomTargetWeapon_10(BattleObject* pCaster, BattleObject* pTarget);

	// 17번 다음 턴에 3%의 확률로 상대방이 소유한 무기 중에서 하나를 가져온다.
	static void Next_GetLandomTargetWeapon_20(BattleObject* pCaster, BattleObject* pTarget);

	// 19번 다음 턴에 자신의 무기 파괴 확률이 20% 증가하고, 자신의 무기 데미지가 150% 증가한다
	static void Next_IncreaseBrokenRate_20_AttackPower_50(BattleObject* pCaster, BattleObject* pTarget);

	// 20번 다음 턴에 자신의 무기 파괴 확률이 30% 증가하고, 자신의 무기 데미지가 200% 증가한다
	static void Next_IncreaseBrokenRate_30_AttackPower_100(BattleObject* pCaster, BattleObject* pTarget);

	// 21번 다음 턴에 자신이 받는 데미지가 20% 증가
	static void Next_IncreaseTargetAttackPow_20(BattleObject* pCaster, BattleObject* pTarget);
};