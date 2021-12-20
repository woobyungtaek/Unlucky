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

	// ���� �� ��ŸƮ ������Ʈ 
	BattleFunction[(int)EBattleState::UserBattleStart] = &BattleManager::UserBattleStart;
	BattleFunction[(int)EBattleState::UserBattleUpdate] = &BattleManager::UserBattleUpdate;

	// �� �� ��ŸƮ ������Ʈ
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

	// �÷��̾� �������� ����
	PlayerHPBar = new HPBar(Vector2(screenSize.x * 0.06, screenSize.y * 0.45)); //0.06 , 0.45
	PlayerHPBar->IsActive = true;

	// ���ʹ� �������� ����
	EnemyHPBar = new HPBar(Vector2(screenSize.x * 0.57, screenSize.y * 0.01));// 0.57, 0.01
	EnemyHPBar->IsActive = true;

	// �ҿ�� �������� ����
	UnluckyStackBar = new UnLuckyStackBar(Vector2(screenSize.x * 0.06, screenSize.y * 0.50));
	UnluckyStackBar->IsActive = true;

	ResultUI = new ResultPopUp(Vector2(screenSize.x / 2, screenSize.y / 2));
	ResultUI->IsActive = false;
}

BattleManager::~BattleManager()
{
}

// �ʱ�ȭ : �÷��̾� ���� ( �÷��̾ �ۿ��� �޴� ���� : �ε�)
void BattleManager::Init(Player* player)
{
	ResultUI->IsActive = false;
	mCurrentState = EBattleState::Entry;
	mpPlayer = player;
	UnluckyStackBar->SetBattleObject(mpPlayer);
	mScrollNum = 0;

}

// ������Ʈ
bool BattleManager::Update()
{
	return (this->*BattleFunction[(int)mCurrentState])();
}

// ���� ����
bool BattleManager::Entry()
{
	wcout << L"*******************************************************************************************************" << endl;
	wcout << endl << L"[Unlucky] ������ �����մϴ�." << endl;
	mBattleResult = EBattleResult::None;

	// ���� ����, ��ġ�մϴ�.
	mpEnemyParty = EnemyManager::GetInstance()->GetEnemyPartyByIndex(mpPlayer->CurrentEnemy);
	Enemy* pEnemy = mpEnemyParty->GetEnemyByIndex(0);
	wcout << L"[Unlucky] " << pEnemy->Name << L" [HP : " << pEnemy->HP << L"] �� ����!!!!!!!!!" << endl;

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

	// ���¸� �����մϴ�.
	mCurrentState = EBattleState::EnemyTurn;
	return false;
}

// �ൿ ���� : ��
bool BattleManager::EnemyTurn()
{
	wcout << endl;
	wcout << endl;

	//�� �׷��� ���� ���� ���� Ȯ��
	int enemyCount = mpEnemyParty->GetEnemyCount();
	for (int index = 0; index < enemyCount; index++)
	{
		Enemy* pEnemy = mpEnemyParty->GetEnemyByIndex(index);

		// ���� ���� ������ Ȯ��
		bool bChangePhase = pEnemy->SetPhaseIndex();
		if (bChangePhase)
		{
			//������ ��ȭ ǥ��
		}

		//���� ���� �ൿ ����
		int actionNum = pEnemy->GetCurrentPattern();
		if (actionNum == 0)
		{
			wcout << L"[System] �� [ ���� ]�� ����!";

			//�� ���� ����

			//���Ⱑ ���� ��� : ��ȣ ���� ���
			if (pEnemy->pWeaponVec.size() <= 0)
			{
				//��ȣ ���⸦ �̾Ƽ� �κ��丮�� �ִ´�.
				pEnemy->GetBlessWeapon();
			}

			// ���� �߿� 1���� ����
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
			//�� ��� ���� 
			wcout << L"[System] �� [ ��� ]�� ����!" << endl;
			mEnemyWeaponImage->SetImageName(_T(""));
			pEnemy->CurrentAction = EEnemyAction::Defence;
		}

		pEnemy->patternIndex += 1;
	}

	wcout << endl;

	// ���¸� �����մϴ�.
	mCurrentState = EBattleState::StartUserTurn;

	return false;
}

// ���� �� ����
bool BattleManager::StartUserTurn()
{
	wcout << L"[Select] �÷��̾� �ൿ ���� ���� [HP : " << mpPlayer->HP << L"]" << endl;
	wcout << L"[Select] 1. ���� 4. ������" << endl;

	// ���¸� �����մϴ�.
	mCurrentState = EBattleState::UserTurn;
	return false;
}

// �ൿ ���� : ����
bool BattleManager::UserTurn()
{
	mpPlayer->CurrentAction = EPlayerAction::Attack;
	mCurrentState = EBattleState::StartSelectWeapon;

	return false;
}


// ���� ���� ���� ����
bool BattleManager::StartSelectWeapon()
{
	wcout << endl;
	wcout << L"[Select] ���⸦ �����ϼ���." << endl;

	mpPlayer->SelectWeaponIndex = 0;
	// �÷��̾� ���� ���� Ȯ��
	int loopCount = mpPlayer->pWeaponVec.size();
	for (int index = 0; index < loopCount; index++)
	{
		wcout << L"[Weapon" << index + 1 << L"]";
		mpPlayer->pWeaponVec[index]->PrintWeaponInfo();
	}

	//wcout << L"[Select] ��ȣ : ���⼱��(1 ~ 7)  /  BackSpace : ��������  / ��� ���� ������ ����(�̱���)" << endl;
	mCurrentState = EBattleState::SelectWeapon;
	return false;
}

// ���� ���� : ����
bool BattleManager::SelectWeapon()
{
	if (InputKeyDown(VK_BACK))
	{
		//���� �ൿ �������� ���ư���.
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
	wcout << L"[System] ������ ����� [Weapon " << index + 1 << L"][" << (const wchar_t*)(mpPlayer->pWeaponVec[index]->Name) << L"]" << endl << endl;
	mCurrentState = EBattleState::StartUserTurn;
	return false;
}

void BattleManager::SelectWeaponByButton(int slotIndex)
{
	if (mCurrentState != EBattleState::SelectWeapon) { return; }
	if (slotIndex + mScrollNum >= mpPlayer->pWeaponVec.size()) { return; }

	mpPlayer->SelectWeaponIndex = slotIndex + mScrollNum;
	wcout << L"[System] ������ ����� [Weapon " << slotIndex + mScrollNum << L"][" << (const wchar_t*)(mpPlayer->pWeaponVec[slotIndex + mScrollNum]->Name) << L"]" << endl << endl;

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

// ���� ����
bool BattleManager::StartBattle()
{
	wcout << L">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	wcout << L"[System] ������ ���۵˴ϴ�." << endl << endl;

	//�÷��̾ �������� ����� �� shortcut
	playerAction = mpPlayer->CurrentAction;
	playerSelectWeaponIndex = 0;
	playerSelectWeapon = nullptr;

	currentEnemy = nullptr;
	enemyCount = 0;
	enemySelectWeaponIndex = 0;
	enemySelectWeapon = nullptr;


	wcout << L"---------���� �Ͽ��� ����� ��ų---------" << endl;
	// ���� �� ��ų : �÷��̾�
	if (mpPlayer->NextSkillFunction != nullptr)
	{
		wcout << L"[System] ���� �� �� ��ų : ";
		currentEnemy = mpEnemyParty->GetEnemyByIndex(0);
		mpPlayer->NextSkillFunction(mpPlayer, currentEnemy);
		mpPlayer->NextSkillFunction = nullptr;
	}

	// ���� �� ��ų : ��
	enemyCount = mpEnemyParty->GetEnemyCount();
	for (int index = 0; index < enemyCount; index++)
	{
		currentEnemy = mpEnemyParty->GetEnemyByIndex(index);
		if (currentEnemy->NextSkillFunction != nullptr)
		{
			wcout << L"[System] �� �� �� ��ų : ";
			currentEnemy->NextSkillFunction(currentEnemy, mpPlayer);
			currentEnemy->NextSkillFunction = nullptr;
		}

		// ������ ��ų ���
		currentEnemy->UsePhaseSkill(mpPlayer);

		// �÷��̾��� HP�� �˻��ؾ��Ѵ�.
		if (mpPlayer->HP <= 0)
		{
			mCurrentState = EBattleState::Battle;
			return false;
		}
	}

	// ���¸� �����մϴ�.
	mCurrentState = EBattleState::UserBattleStart;
	return false;
}

bool BattleManager::UserBattleStart()
{
	wcout << L"[System] UserBattleStart" << endl;

	wcout << endl;
	wcout << L"--------------�÷��̾� ��-----------------" << endl;
	// ���� ���� : �÷��̾� �� �ൿ (����, �� ���)
	if (playerAction == EPlayerAction::Attack)
	{
		playerSelectWeaponIndex = mpPlayer->SelectWeaponIndex;
		playerSelectWeapon = mpPlayer->pWeaponVec[playerSelectWeaponIndex];
		currentEnemy = mpEnemyParty->GetEnemyByIndex(0);

		// Ȯ�� Ȯ�� : ���� ����
		if (IsSuccess(playerSelectWeapon->BrokenRate + mpPlayer->AdditionalBrokenRate))
		{
			// ������ ��ȣ Ȯ��
			if (playerSelectWeapon->BlessCount > 0)
			{
				playerSelectWeapon->BlessCount -= 1;
				wcout << L"[System] ������ ��ȣ -1  �����ı��� ���ҽ��ϴ�." << endl;
			}
			else
			{
				//���� �ı�
				wcout << L"[System] ���Ⱑ �μ������ϴ�. ���ݿ� �����߽��ϴ�." << endl;
				mpPlayer->DestroyWeaponByIndex(playerSelectWeaponIndex);
				mpPlayer->IncreaseUnluckyStack(1);
			}
		}
		// Ȯ�� Ȯ�� : ���� ����
		else
		{
			wcout << L"[System] �÷��̾ ���� �����մϴ�." << endl;
			bool bAttack = true;

			// ���� : ��ų ���
			mpPlayer->UseWeaponSkill(currentEnemy);

			//mpPlayer HP �˻簡 �ѹ� �� ������ 

			// ���� ���� : �� �� �ൿ (���) 
			if (currentEnemy->CurrentAction == EEnemyAction::Defence)
			{
				// Ȯ�� Ȯ�� : ��� ���� 
				if (currentEnemy->IsBlock)
				{
					bAttack = false;
					wcout << L"[System] �� ��� �÷��� �ߵ�, ��� ����" << endl;
				}
				else
				{
					if (IsSuccess(50))
					{
						bAttack = false;

						wcout << L"[System] ���� �� �����߽��ϴ�." << endl;
					}
				}

			}

			// ���� ���� : �� ��� ����
			if (bAttack)
			{
				int damage = playerSelectWeapon->AttackPow * (mpPlayer->AdditionalPowerRate + 1);

				currentEnemy->HP -= damage;
				wcout << L"[System] " << damage << L"�� �������� �־���." << endl;
				wcout << L"[System] " << currentEnemy->Name << L"�� ü���� " << currentEnemy->HP << L"�� �Ǿ���." << endl;

				// �� �ݰ� (�̹� 50% ����)
				if (currentEnemy->IsCounter)
				{
					wcout << L"[System] ���� " << damage << L"�� [�ݰ�] �������� �־���." << endl;
					mpPlayer->HP -= damage;
				}

				// �÷��̾� ����
				if (mpPlayer->IsDrain)
				{
					wcout << L"[System] " << damage << L"�� HP�� ����ߴ�." << endl;
					wcout << L"[System] �÷��̾��� ";
					mpPlayer->RecoveryHP(damage);
				}

				if (currentEnemy->HP <= 0)
				{
					// ��Ƽ�� �ε����� ���� ����
					KillEnemyByIndex(0);
				}
			}
		}
		//����� �� �ʱ�ȭ
		currentEnemy->ResetDefenceValues();

		// ������ �� �ʱ�ȭ
		mpPlayer->ResetAttackValues();
	}

	mCurrentState = EBattleState::UserBattleUpdate;
	return false;
}

bool BattleManager::UserBattleUpdate()
{
	wcout << L"[System] UserBattleUpdate" << endl;


	//�̹� �ִϸ��̼��ϰ� �������� �Ѿ����
	ID2D1Bitmap* Pweapon = SpriteManager::GetInstance()->GetSpriteByPath(playerSelectWeapon->FileName);
	//DrawImage(Pweapon,)
		

	mCurrentState = EBattleState::EnemyBattleStart;
	return false;
}

bool BattleManager::EnemyBattleStart()
{
	wcout << L"[System] EnemyBattleStart" << endl;

	wcout << endl;
	wcout << L"-----------------�� �� -------------------" << endl;
	// ���� ���� : �� �� �ൿ (����, ��ų)
	enemyCount = mpEnemyParty->GetEnemyCount();
	for (int index = 0; index < enemyCount; index++)
	{
		bool bAttackSuccess = true;
		currentEnemy = mpEnemyParty->GetEnemyByIndex(index);

		// ���� ���� : ���� ���� �ൿ ����
		if (currentEnemy->HP <= 0) { continue; }

		// ���� ���� : �� ����
		if (currentEnemy->CurrentAction == EEnemyAction::Attack)
		{
			wcout << L"[System] ���� �����Ͽ����ϴ�." << endl;

			// ���� ���� Ȯ�� 
			enemySelectWeaponIndex = currentEnemy->SelectWeaponIndex;
			enemySelectWeapon = currentEnemy->pWeaponVec[enemySelectWeaponIndex];

			// Ȯ�� ���� : �� ���� ����
			if (IsSuccess(enemySelectWeapon->BrokenRate + currentEnemy->AdditionalBrokenRate))
			{
				// ���� ���Ⱑ �μ������ϴ�.
				wcout << L"[System] ���� ���Ⱑ �μ������ϴ�." << endl;
				currentEnemy->DestroyWeaponByIndex(enemySelectWeaponIndex);
				bAttackSuccess = false;
			}

			// �÷��̾� ��� ���� 
			if (mpPlayer->IsBlock)
			{
				bAttackSuccess = false;
				wcout << L"[System] �÷��̾ ����߽��ϴ�." << endl;
			}

			// �ൿ ���� : �� ���� ����
			if (bAttackSuccess)
			{
				// ���� : ��ų ���
				currentEnemy->UseWeaponSkill(mpPlayer);

				//�� ������ ����
				int damage = enemySelectWeapon->AttackPow * (currentEnemy->AdditionalPowerRate + 1);

				mpPlayer->HP -= damage;
				wcout << L"[System] " << damage << L"�� ���ظ� �Ծ����ϴ�. ���� HP " << mpPlayer->HP << endl;

				// �� ī����
				if (mpPlayer->IsCounter)
				{
					//��� �������� ��� ����
					//���� ü���� 0���� ������ �������� �ʴ´�. 
					currentEnemy->HP -= damage;
					wcout << L"[System] " << damage << L"��ŭ ������ ������! ���� ���� HP " << currentEnemy->HP << endl;
				}

				// �� ����
				if (currentEnemy->IsDrain)
				{
					wcout << L"[System] " << damage << L"�� HP�� ����ߴ�." << endl;
					wcout << L"[System] ���� ";
					currentEnemy->RecoveryHP(damage);
				}
			}
		}
		// ������ �� �ʱ�ȭ
		currentEnemy->ResetAttackValues();
	}

	// ����� �� �ʱ�ȭ ( �÷��̾��� ���, ȸ��, ���ݷµ� ���� ��뿡�� ����[���� ���� �������� ���])
	mpPlayer->ResetDefenceValues();

	mCurrentState = EBattleState::EnemyBattleUpdate;
	return false;
}

bool BattleManager::EnemyBattleUpdate()
{
	wcout << L"[System] EnemyBattleUpdate" << endl;


	//�� �ִϸ��̼��ϰ� �������� �Ѿ����


	mCurrentState = EBattleState::Battle;
	return false;
}

// ���� ��
bool BattleManager::Battle()
{
	// ���¸� �����մϴ�.
	mpPlayer->CurrentListUI->RefreshUI();
	mCurrentState = EBattleState::Result;
	return false;
}

// ���
bool BattleManager::Result()
{
	if (mpPlayer->HP <= 0)
	{
		//���� ���� ( HP Zero )
		wcout << L"[System] HP 0 !! ���� ����!!" << endl;
		mCurrentState = EBattleState::BattleEnd;
		mBattleResult = EBattleResult::GameOver_HP;
		return false;
	}
	if (mpPlayer->pWeaponVec.size() <= 0)
	{
		//���� ���� ( ���� ���� )
		wcout << L"[System] �� �̻� ��� ������ ���Ⱑ �����ϴ�! ���� ����!" << endl;
		mCurrentState = EBattleState::BattleEnd;
		mBattleResult = EBattleResult::GameOver_WEAPON;
		return false;
	}
	wcout << L"[System] ���� ���� �� " << mpEnemyParty->GetEnemyCount() << endl;

	if (mpEnemyParty->GetEnemyCount() <= 0)
	{
		//���� �¸�
		mpPlayer->CurrentStage++;

		mpPlayer->RecoveryHP(50);
		//�� �������� ����ŭ
		if (mpPlayer->CurrentStage >= 5)
		{
			wcout << L"[System] ��� �� ����, ���� ����" << endl;

			mCurrentState = EBattleState::BattleEnd;
			mBattleResult = EBattleResult::PlayerWin;
			return false;
		}

		//�������� ���� â���� �����Ѵ�.
		mCurrentState = EBattleState::BattleEnd;
		mBattleResult = EBattleResult::BattleWin;
		return false;
	}

	// ���¸� �����մϴ�.
	mCurrentState = EBattleState::EnemyTurn;
	return false;
}

// ���� ���� : ��Ʋ �Ŵ��� ��������
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


// Ȯ�� Ȯ��
bool BattleManager::IsSuccess(float rate)
{
	//�Ҽ��� 2�ڸ� Ȯ��
	float result;
	result = (float)(rand() % 10000);
	result /= 100;

	wcout << L"[System][Ȯ�� ���] ���� ���� : " << result << L" / Ȯ�� : " << rate << endl;
	if (result <= rate)
	{
		//����
		return true;
	}

	//����
	return false;
}

// �� �׿���
void BattleManager::KillEnemyByIndex(int index)
{
	Enemy* currentEnemy = mpEnemyParty->GetEnemyByIndex(index);

	ResultUI->ReseWeaponVec();

	wcout << L"[System] ���� �����ƴ�!" << endl;

	wcout << L"[System] �⺻ ���� weapon box + 2" << endl;
	mpPlayer->WeaponBoxCount += 2;

	int lootCnt = 0;
	for (int weaponIdx = 0; weaponIdx < currentEnemy->pWeaponVec.size(); weaponIdx++)
	{
		if (currentEnemy->pWeaponVec[weaponIdx]->BlessCount > 0) { continue; }
		lootCnt++;

		// ���� ���Ͱ� ������ �ִ� ���⸦ ��ȣ ���⸦ �����ϰ� ȹ��
		wcout << L"[System] [ " << (const wchar_t*)(currentEnemy->pWeaponVec[weaponIdx]->Name) << L" ] �� ȹ�� �߽��ϴ�." << endl;
		mpPlayer->pWeaponVec.push_back(currentEnemy->pWeaponVec[weaponIdx]->Copy());
		ResultUI->SetWeapon(currentEnemy->pWeaponVec[weaponIdx]);
	}

	//����� ���� ���� ������ �־�� �Ѵ�.
	mpEnemyParty->EraseEnemyInPartyByIndex(0);
}

// ���� �÷��̾��� ���⸦ �޾ƿ´�.
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
