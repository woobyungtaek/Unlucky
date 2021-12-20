#include "pch.h"
#include "Player.h"
#include "Enemy.h"
#include "BattleManager.h"

BattleManager::BattleManager()
{
	mCurrentState = EBattleState::Entry;

	BattleFunction[(int)EBattleState::Entry] = &BattleManager::Entry;
	BattleFunction[(int)EBattleState::StartUserTurn] = &BattleManager::StartUserTurn;
	BattleFunction[(int)EBattleState::UserTurn] = &BattleManager::UserTurn;
	BattleFunction[(int)EBattleState::StartSelectWeapon] = &BattleManager::StartSelectWeapon;
	BattleFunction[(int)EBattleState::SelectWeapon] = &BattleManager::SelectWeapon;
	BattleFunction[(int)EBattleState::EnemyTurn] = &BattleManager::EnemyTurn;
	BattleFunction[(int)EBattleState::StartBattle] = &BattleManager::StartBattle;

	// 유저 턴 스타트 업데이트 
	BattleFunction[(int)EBattleState::UserBattleStart] = &BattleManager::UserBattleStart;
	BattleFunction[(int)EBattleState::UserBattleUpdate] = &BattleManager::UserBattleUpdate;

	// 적 턴 스타트 업데이트
	BattleFunction[(int)EBattleState::EnemyBattleStart] = &BattleManager::EnemyBattleStart;
	BattleFunction[(int)EBattleState::EnemyBattleUpdate] = &BattleManager::EnemyBattleUpdate;


	BattleFunction[(int)EBattleState::Battle] = &BattleManager::Battle;
	BattleFunction[(int)EBattleState::Result] = &BattleManager::Result;
	BattleFunction[(int)EBattleState::BattleEnd] = &BattleManager::BattleEnd;

	screenSize.x = GetSystemMetrics(SM_CXSCREEN);
	screenSize.y = GetSystemMetrics(SM_CYSCREEN);

	mPlayerImage	  = new ImageObject();
	mEnemyImage		  = new ImageObject();
	mEnemySubImage	  = new ImageObject();
	mEnemyWeaponImage = new ImageObject();

	// 플레이어 게이지바 생성
	PlayerHPBar = new HPBar(Vector2(screenSize.x * 0.06, screenSize.y * 0.45)); //0.06 , 0.45
	PlayerHPBar->IsActive = true;

	// 에너미 게이지바 생성
	EnemyHPBar = new HPBar(Vector2(screenSize.x * 0.57, screenSize.y * 0.01));// 0.57, 0.01
	EnemyHPBar->IsActive = true;

	// 불운스택 게이지바 생성
	UnluckyStackBar = new UnLuckyStackBar(Vector2(screenSize.x * 0.06, screenSize.y * 0.50));
	UnluckyStackBar->IsActive = true;

	ResultUI = new ResultPopUp(Vector2(screenSize.x / 2, screenSize.y / 2));
	ResultUI->IsActive = false;
}

BattleManager::~BattleManager()
{
}

// 초기화 : 플레이어 셋팅 ( 플레이어를 밖에서 받는 이유 : 로드)
void BattleManager::Init(Player* player)
{
	ResultUI->IsActive = false;
	mCurrentState = EBattleState::Entry;
	mpPlayer = player;
	UnluckyStackBar->SetBattleObject(mpPlayer);
	mScrollNum = 0;

}

// 업데이트
bool BattleManager::Update()
{
	return (this->*BattleFunction[(int)mCurrentState])();
}

// 전투 진입
bool BattleManager::Entry()
{
	wcout << L"*******************************************************************************************************" << endl;
	wcout << endl << L"[Unlucky] 전투에 진입합니다." << endl;
	mBattleResult = EBattleResult::None;

	// 적을 생성, 배치합니다.
	mpEnemyParty = EnemyManager::GetInstance()->GetEnemyPartyByIndex(mpPlayer->CurrentEnemy);
	Enemy* pEnemy = mpEnemyParty->GetEnemyByIndex(0);
	wcout << L"[Unlucky] " << pEnemy->Name << L" [HP : " << pEnemy->HP << L"] 적 출현!!!!!!!!!" << endl;

	mPlayerImage->SetPosition(Vector2((screenSize.x * 0.14), (screenSize.y * 0.75)));
	mPlayerImage->SetImageName(_T("..\\Data\\Mimic_Final.png"));

	mEnemyImage->SetPosition(Vector2((screenSize.x * 0.67), (screenSize.y * 0.3)));
	CString filepath;
	filepath.Format(_T("..\\Data\\Monster\\%s"), pEnemy->FileName);
	mEnemyImage->SetImageName(filepath);

	if (mpPlayer->CurrentEnemy == 3)
	{
		mEnemySubImage->SetPosition(Vector2(mPlayerImage->GetPosition().x, mPlayerImage->GetPosition().y));
		mEnemySubImage->SetImageName(_T("..\\Data\\Monster\\hero_woman_cape_0.png"));
	}
	else
	{
		mEnemySubImage->SetImageName(_T(""));
	}

	PlayerHPBar->SetBattleObject(mpPlayer);
	EnemyHPBar->SetBattleObject(pEnemy);

	// 상태를 변경합니다.
	mCurrentState = EBattleState::EnemyTurn;
	return false;
}

// 행동 결정 : 적
bool BattleManager::EnemyTurn()
{
	wcout << endl;
	wcout << endl;

	//적 그룹중 남은 적의 수를 확인
	int enemyCount = mpEnemyParty->GetEnemyCount();
	for (int index = 0; index < enemyCount; index++)
	{
		Enemy* pEnemy = mpEnemyParty->GetEnemyByIndex(index);

		// 현재 적의 페이즈 확인
		bool bChangePhase = pEnemy->SetPhaseIndex();
		if (bChangePhase)
		{
			//페이즈 변화 표시
		}

		//현재 적의 행동 결정
		int actionNum = pEnemy->GetCurrentPattern();
		if (actionNum == 0)
		{
			wcout << L"[System] 적 [ 공격 ]을 선택!";

			//적 공격 선택

			//무기가 없는 경우 : 가호 무기 사용
			if (pEnemy->pWeaponVec.size() <= 0)
			{
				//가호 무기를 뽑아서 인벤토리에 넣는다.
				pEnemy->GetBlessWeapon();
			}

			// 무기 중에 1개를 선택
			int weaponCount = pEnemy->pWeaponVec.size();
			pEnemy->SelectWeaponIndex = rand() % weaponCount;
			pEnemy->CurrentAction = EEnemyAction::Attack;


			mEnemyWeaponImage->SetPosition(mEnemyImage->GetPosition() - Vector2(100,0));
			mEnemyWeaponImage->SetScale(Vector2(0.25,0.25));
			CString filepath;
			filepath.Format(_T("..\\Data\\Weapon\\%s"), pEnemy->pWeaponVec[pEnemy->SelectWeaponIndex]->FileName);
			mEnemyWeaponImage->SetImageName(filepath);

			wcout << endl << L"[Weapon" << index + 1 << L"]";
			pEnemy->pWeaponVec[pEnemy->SelectWeaponIndex]->PrintWeaponInfo();
		}
		else
		{
			//적 방어 선택 
			wcout << L"[System] 적 [ 방어 ]를 선택!" << endl;
			mEnemyWeaponImage->SetImageName(_T(""));
			pEnemy->CurrentAction = EEnemyAction::Defence;
		}

		pEnemy->patternIndex += 1;
	}

	wcout << endl;

	// 상태를 변경합니다.
	mCurrentState = EBattleState::StartUserTurn;

	return false;
}

// 유저 턴 시작
bool BattleManager::StartUserTurn()
{
	wcout << L"[Select] 플레이어 행동 선택 현재 [HP : " << mpPlayer->HP << L"]" << endl;
	wcout << L"[Select] 1. 공격 4. 턴종료" << endl;

	// 상태를 변경합니다.
	mCurrentState = EBattleState::UserTurn;
	return false;
}

// 행동 결정 : 유저
bool BattleManager::UserTurn()
{
	mpPlayer->CurrentAction = EPlayerAction::Attack;
	mCurrentState = EBattleState::StartSelectWeapon;

	return false;
}


// 유저 무기 결정 시작
bool BattleManager::StartSelectWeapon()
{
	wcout << endl;
	wcout << L"[Select] 무기를 선택하세요." << endl;

	mpPlayer->SelectWeaponIndex = 0;
	// 플레이어 무기 개수 확인
	int loopCount = mpPlayer->pWeaponVec.size();
	for (int index = 0; index < loopCount; index++)
	{
		wcout << L"[Weapon" << index + 1 << L"]";
		mpPlayer->pWeaponVec[index]->PrintWeaponInfo();
	}

	//wcout << L"[Select] 번호 : 무기선택(1 ~ 7)  /  BackSpace : 이전으로  / ←→ 무기 페이지 변경(미구현)" << endl;
	mCurrentState = EBattleState::SelectWeapon;
	return false;
}

// 무기 결정 : 유저
bool BattleManager::SelectWeapon()
{
	if (InputKeyDown(VK_BACK))
	{
		//유저 행동 선택으로 돌아간다.
		mCurrentState = EBattleState::StartUserTurn;
		return false;
	}

	short index = -1;
	if (InputKeyDown(VK_1)) { index = 0; }
	if (InputKeyDown(VK_2)) { index = 1; }
	if (InputKeyDown(VK_3)) { index = 2; }
	if (InputKeyDown(VK_4)) { index = 3; }
	if (InputKeyDown(VK_5)) { index = 4; }
	if (InputKeyDown(VK_6)) { index = 5; }
	if (InputKeyDown(VK_7)) { index = 6; }

	if (index >= mpPlayer->pWeaponVec.size())
	{
		index = -1;
	}

	if (index < 0)
	{
		return false;
	}

	mpPlayer->SelectWeaponIndex = index;
	wcout << L"[System] 선택한 무기는 [Weapon " << index + 1 << L"][" << (const wchar_t*)(mpPlayer->pWeaponVec[index]->Name) << L"]" << endl << endl;
	mCurrentState = EBattleState::StartUserTurn;
	return false;
}

void BattleManager::SelectWeaponByButton(int slotIndex)
{
	if (mCurrentState != EBattleState::SelectWeapon) { return; }
	if (slotIndex + mScrollNum >= mpPlayer->pWeaponVec.size()) { return; }

	mpPlayer->SelectWeaponIndex = slotIndex + mScrollNum;
	wcout << L"[System] 선택한 무기는 [Weapon " << slotIndex + mScrollNum << L"][" << (const wchar_t*)(mpPlayer->pWeaponVec[slotIndex + mScrollNum]->Name) << L"]" << endl << endl;

}

Weapon* BattleManager::GetWeaponByButton(int slotIndex)
{
	if (mCurrentState != EBattleState::SelectWeapon) { return nullptr; }
	if (slotIndex + mScrollNum >= mpPlayer->pWeaponVec.size()) { return nullptr; }

	return mpPlayer->pWeaponVec[slotIndex + mScrollNum];
}

void BattleManager::PlayerTurnEnd()
{
	if (mCurrentState != EBattleState::SelectWeapon) { return; }
	mCurrentState = EBattleState::StartBattle;
}

// 전투 시작
bool BattleManager::StartBattle()
{
	wcout << L">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	wcout << L"[System] 전투가 시작됩니다." << endl << endl;

	//플레이어가 전투에서 사용할 값 shortcut
	playerAction = mpPlayer->CurrentAction;
	playerSelectWeaponIndex = 0;
	playerSelectWeapon = nullptr;

	currentEnemy = nullptr;
	enemyCount = 0;
	enemySelectWeaponIndex = 0;
	enemySelectWeapon = nullptr;


	wcout << L"---------이전 턴에서 적용된 스킬---------" << endl;
	// 이전 턴 스킬 : 플레이어
	if (mpPlayer->NextSkillFunction != nullptr)
	{
		wcout << L"[System] 유저 전 턴 스킬 : ";
		currentEnemy = mpEnemyParty->GetEnemyByIndex(0);
		mpPlayer->NextSkillFunction(mpPlayer, currentEnemy);
		mpPlayer->NextSkillFunction = nullptr;
	}

	// 이전 턴 스킬 : 적
	enemyCount = mpEnemyParty->GetEnemyCount();
	for (int index = 0; index < enemyCount; index++)
	{
		currentEnemy = mpEnemyParty->GetEnemyByIndex(index);
		if (currentEnemy->NextSkillFunction != nullptr)
		{
			wcout << L"[System] 적 전 턴 스킬 : ";
			currentEnemy->NextSkillFunction(currentEnemy, mpPlayer);
			currentEnemy->NextSkillFunction = nullptr;
		}

		// 페이즈 스킬 사용
		currentEnemy->UsePhaseSkill(mpPlayer);

		// 플레이어의 HP를 검사해야한다.
		if (mpPlayer->HP <= 0)
		{
			mCurrentState = EBattleState::Battle;
			return false;
		}
	}

	// 상태를 변경합니다.
	mCurrentState = EBattleState::UserBattleStart;
	return false;
}

bool BattleManager::UserBattleStart()
{
	wcout << L"[System] UserBattleStart" << endl;

	wcout << endl;
	wcout << L"--------------플레이어 턴-----------------" << endl;
	// 전투 판정 : 플레이어 선 행동 (공격, 적 방어)
	if (playerAction == EPlayerAction::Attack)
	{
		playerSelectWeaponIndex = mpPlayer->SelectWeaponIndex;
		playerSelectWeapon = mpPlayer->pWeaponVec[playerSelectWeaponIndex];
		currentEnemy = mpEnemyParty->GetEnemyByIndex(0);

		// 확률 확인 : 공격 실패
		if (IsSuccess(playerSelectWeapon->BrokenRate + mpPlayer->AdditionalBrokenRate))
		{
			// 마왕의 가호 확인
			if (playerSelectWeapon->BlessCount > 0)
			{
				playerSelectWeapon->BlessCount -= 1;
				wcout << L"[System] 마왕의 가호 -1  무기파괴를 막았습니다." << endl;
			}
			else
			{
				//무기 파괴
				wcout << L"[System] 무기가 부셔졌습니다. 공격에 실패했습니다." << endl;
				mpPlayer->DestroyWeaponByIndex(playerSelectWeaponIndex);
				mpPlayer->IncreaseUnluckyStack(1);
			}
		}
		// 확률 확인 : 공격 성공
		else
		{
			wcout << L"[System] 플레이어가 적을 공격합니다." << endl;
			bool bAttack = true;

			// 무기 : 스킬 사용
			mpPlayer->UseWeaponSkill(currentEnemy);

			//mpPlayer HP 검사가 한번 더 들어가야함 

			// 전투 판정 : 적 선 행동 (방어) 
			if (currentEnemy->CurrentAction == EEnemyAction::Defence)
			{
				// 확률 확인 : 방어 성공 
				if (currentEnemy->IsBlock)
				{
					bAttack = false;
					wcout << L"[System] 적 방어 플래그 발동, 방어 성공" << endl;
				}
				else
				{
					if (IsSuccess(50))
					{
						bAttack = false;

						wcout << L"[System] 적이 방어에 성공했습니다." << endl;
					}
				}

			}

			// 전투 판정 : 적 방어 실패
			if (bAttack)
			{
				int damage = playerSelectWeapon->AttackPow * (mpPlayer->AdditionalPowerRate + 1);

				currentEnemy->HP -= damage;
				wcout << L"[System] " << damage << L"의 데미지를 주었다." << endl;
				wcout << L"[System] " << currentEnemy->Name << L"의 체력이 " << currentEnemy->HP << L"가 되었다." << endl;

				// 적 반격 (이미 50% 적용)
				if (currentEnemy->IsCounter)
				{
					wcout << L"[System] 적이 " << damage << L"의 [반격] 데미지를 주었다." << endl;
					mpPlayer->HP -= damage;
				}

				// 플레이어 흡혈
				if (mpPlayer->IsDrain)
				{
					wcout << L"[System] " << damage << L"의 HP를 흡수했다." << endl;
					wcout << L"[System] 플레이어의 ";
					mpPlayer->RecoveryHP(damage);
				}

				if (currentEnemy->HP <= 0)
				{
					// 파티내 인덱스로 적을 제거
					KillEnemyByIndex(0);
				}
			}
		}
		//방어자 값 초기화
		currentEnemy->ResetDefenceValues();

		// 공격자 값 초기화
		mpPlayer->ResetAttackValues();
	}

	mCurrentState = EBattleState::UserBattleUpdate;
	return false;
}

bool BattleManager::UserBattleUpdate()
{
	wcout << L"[System] UserBattleUpdate" << endl;


	//미믹 애니메이션하고 다음으로 넘어가세요
	ID2D1Bitmap* Pweapon = SpriteManager::GetInstance()->GetSpriteByPath(playerSelectWeapon->FileName);
	//DrawImage(Pweapon,)
		

	mCurrentState = EBattleState::EnemyBattleStart;
	return false;
}

bool BattleManager::EnemyBattleStart()
{
	wcout << L"[System] EnemyBattleStart" << endl;

	wcout << endl;
	wcout << L"-----------------적 턴 -------------------" << endl;
	// 전투 판정 : 적 후 행동 (공격, 스킬)
	enemyCount = mpEnemyParty->GetEnemyCount();
	for (int index = 0; index < enemyCount; index++)
	{
		bool bAttackSuccess = true;
		currentEnemy = mpEnemyParty->GetEnemyByIndex(index);

		// 전투 판정 : 뒤진 적은 행동 안함
		if (currentEnemy->HP <= 0) { continue; }

		// 전투 판정 : 적 공격
		if (currentEnemy->CurrentAction == EEnemyAction::Attack)
		{
			wcout << L"[System] 적이 공격하였습니다." << endl;

			// 선택 무기 확인 
			enemySelectWeaponIndex = currentEnemy->SelectWeaponIndex;
			enemySelectWeapon = currentEnemy->pWeaponVec[enemySelectWeaponIndex];

			// 확률 판정 : 적 공격 실패
			if (IsSuccess(enemySelectWeapon->BrokenRate + currentEnemy->AdditionalBrokenRate))
			{
				// 적의 무기가 부셔졌습니다.
				wcout << L"[System] 적의 무기가 부셔졌습니다." << endl;
				currentEnemy->DestroyWeaponByIndex(enemySelectWeaponIndex);
				bAttackSuccess = false;
			}

			// 플레이어 방어 성공 
			if (mpPlayer->IsBlock)
			{
				bAttackSuccess = false;
				wcout << L"[System] 플레이어가 방어했습니다." << endl;
			}

			// 행동 판정 : 적 공격 성공
			if (bAttackSuccess)
			{
				// 무기 : 스킬 사용
				currentEnemy->UseWeaponSkill(mpPlayer);

				//적 데미지 증가
				int damage = enemySelectWeapon->AttackPow * (currentEnemy->AdditionalPowerRate + 1);

				mpPlayer->HP -= damage;
				wcout << L"[System] " << damage << L"의 피해를 입었습니다. 남은 HP " << mpPlayer->HP << endl;

				// 적 카운터
				if (mpPlayer->IsCounter)
				{
					//상대 데미지로 상대 공격
					//현재 체력이 0보다 낮으면 실행하지 않는다. 
					currentEnemy->HP -= damage;
					wcout << L"[System] " << damage << L"만큼 적에게 데미지! 적의 남은 HP " << currentEnemy->HP << endl;
				}

				// 적 흡혈
				if (currentEnemy->IsDrain)
				{
					wcout << L"[System] " << damage << L"의 HP를 흡수했다." << endl;
					wcout << L"[System] 적의 ";
					currentEnemy->RecoveryHP(damage);
				}
			}
		}
		// 공격자 값 초기화
		currentEnemy->ResetAttackValues();
	}

	// 방어자 값 초기화 ( 플레이어의 방어, 회복, 공격력등 여러 상대에게 적용[만약 적이 여러명인 경우])
	mpPlayer->ResetDefenceValues();

	mCurrentState = EBattleState::EnemyBattleUpdate;
	return false;
}

bool BattleManager::EnemyBattleUpdate()
{
	wcout << L"[System] EnemyBattleUpdate" << endl;


	//적 애니메이션하고 다음으로 넘어가세요


	mCurrentState = EBattleState::Battle;
	return false;
}

// 전투 중
bool BattleManager::Battle()
{
	// 상태를 변경합니다.
	mpPlayer->CurrentListUI->RefreshUI();
	mCurrentState = EBattleState::Result;
	return false;
}

// 결과
bool BattleManager::Result()
{
	if (mpPlayer->HP <= 0)
	{
		//게임 오버 ( HP Zero )
		wcout << L"[System] HP 0 !! 게임 오버!!" << endl;
		mCurrentState = EBattleState::BattleEnd;
		mBattleResult = EBattleResult::GameOver_HP;
		return false;
	}
	if (mpPlayer->pWeaponVec.size() <= 0)
	{
		//게임 오버 ( 무기 없음 )
		wcout << L"[System] 더 이상 사용 가능한 무기가 없습니다! 게임 오버!" << endl;
		mCurrentState = EBattleState::BattleEnd;
		mBattleResult = EBattleResult::GameOver_WEAPON;
		return false;
	}
	wcout << L"[System] 남은 적의 수 " << mpEnemyParty->GetEnemyCount() << endl;

	if (mpEnemyParty->GetEnemyCount() <= 0)
	{
		//전투 승리
		mpPlayer->CurrentStage++;

		mpPlayer->RecoveryHP(50);
		//총 스테이지 수만큼
		if (mpPlayer->CurrentStage >= 5)
		{
			wcout << L"[System] 모든 적 격파, 게임 엔딩" << endl;

			mCurrentState = EBattleState::BattleEnd;
			mBattleResult = EBattleResult::PlayerWin;
			return false;
		}

		//스테이지 선택 창으로 가야한다.
		mCurrentState = EBattleState::BattleEnd;
		mBattleResult = EBattleResult::BattleWin;
		return false;
	}

	// 상태를 변경합니다.
	mCurrentState = EBattleState::EnemyTurn;
	return false;
}

// 전투 종료 : 배틀 매니저 빠져나감
bool BattleManager::BattleEnd()
{
	//ResultUI Popup
	if (!ResultUI->IsActive && mBattleResult == EBattleResult::BattleWin)
	{
		mbExit = false;
		ResultUI->IsActive = true;
	}
	switch (mBattleResult)
	{
	case EBattleResult::GameOver_HP:
	case EBattleResult::GameOver_WEAPON:
	case EBattleResult::PlayerWin:
		mbExit = true;
	}
	return mbExit;
}

EBattleResult BattleManager::GetBattleResult()
{
	return mBattleResult;
}


// 확률 확인
bool BattleManager::IsSuccess(float rate)
{
	//소수점 2자리 확률
	float result;
	result = (float)(rand() % 10000);
	result /= 100;

	wcout << L"[System][확률 결과] 뽑은 숫자 : " << result << L" / 확률 : " << rate << endl;
	if (result <= rate)
	{
		//성공
		return true;
	}

	//실패
	return false;
}

// 적 죽였음
void BattleManager::KillEnemyByIndex(int index)
{
	Enemy* currentEnemy = mpEnemyParty->GetEnemyByIndex(index);

	ResultUI->ReseWeaponVec();

	wcout << L"[System] 적을 물리쳤다!" << endl;

	wcout << L"[System] 기본 보상 weapon box + 2" << endl;
	mpPlayer->WeaponBoxCount += 2;

	int lootCnt = 0;
	for (int weaponIdx = 0; weaponIdx < currentEnemy->pWeaponVec.size(); weaponIdx++)
	{
		if (currentEnemy->pWeaponVec[weaponIdx]->BlessCount > 0) { continue; }
		lootCnt++;

		// 죽은 몬스터가 가지고 있는 무기를 가호 무기를 제외하고 획득
		wcout << L"[System] [ " << (const wchar_t*)(currentEnemy->pWeaponVec[weaponIdx]->Name) << L" ] 을 획득 했습니다." << endl;
		mpPlayer->pWeaponVec.push_back(currentEnemy->pWeaponVec[weaponIdx]->Copy());
		ResultUI->SetWeapon(currentEnemy->pWeaponVec[weaponIdx]);
	}

	//띄워줄 무기 따로 가지고 있어야 한다.
	mpEnemyParty->EraseEnemyInPartyByIndex(0);
}

// 현재 플레이어의 무기를 받아온다.
Weapon* BattleManager::GetPlayerWeaponByIndex(int index)
{
	if (index < 0 || index >= mpPlayer->pWeaponVec.size())
	{
		return nullptr;
	}
	return mpPlayer->pWeaponVec[index];
}

BattleObject* BattleManager::GetEnemy()
{
	return mpEnemyParty->GetEnemyByIndex(0);
}

void BattleManager::SetExitState(bool value)
{
	mbExit = true;
}
