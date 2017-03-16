#pragma once
#include "2DImage.h"
#include "EnemyBoss.h"

//ボスの体力バー。
class BossEnemyHPBar :public C2DImage
{
public:
	//コンストラクタ。
	BossEnemyHPBar();

	//デストラクタ。
	~BossEnemyHPBar();
	//初期化。
	void Initialize();

	//更新。
	void Update();
private:
	EnemyBoss*	m_bossEnemy;	//ボスのインスタンス。
};

