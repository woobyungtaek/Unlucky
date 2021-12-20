#pragma once

// Scene
enum class ESceneType
{
	TitleStart = 0,
	TitleUpdate,
	LoadingStart,
	LoadingUpdate,
	BattleStart,
	BattleUpdate,
	LobbyStart,
	LobbyUpdate,
	GotcharStart,
	GotcharUpdate,

	SceneCount
};

// Battle
enum class EBattleState
{
	Entry = 0,

	StartUserTurn,
	UserTurn,

	StartSelectWeapon,
	SelectWeapon,

	EnemyTurn,

	StartBattle,

	UserBattleStart,
	UserBattleUpdate,

	EnemyBattleStart,
	EnemyBattleUpdate,

	Battle,
	Result,

	BattleEnd,

	StateCount
};
enum class EBattleResult
{
	// ���� �¸�
	// ���� ����
	// ���� ���� HP
	// ���� ���� ��������
	

	None = 0,
	BattleWin,
	PlayerWin,
	GameOver_HP,
	GameOver_WEAPON,
	ResultCount
};

// Player
enum class EPlayerAction
{
	Attack = 0,
	ChoiceCount
};

// Weapon
enum class EWeaponGrade
{
	Normal = 0,
	Rare,
	Epic,
	Legend
};

enum class EWeaponType
{
	Sword = 0,
	Shield,
	Dagger,
	Spear,
	Hammer
};