#pragma once
#include "2DImage.h"

//ボスの体力バーの背景。
class BossEnemyHPBarBack : public C2DImage
{
public:
	//コンストラクタ。
	BossEnemyHPBarBack();

	//デストラクタ。
	~BossEnemyHPBarBack();

	//初期化。
	void Initialize();

	//更新。
	void Update();
};

