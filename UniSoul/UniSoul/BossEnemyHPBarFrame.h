#pragma once
#include "2DImage.h"

//ボスの体力バーのフレーム。
class BossEnemyHPBarFrame :public C2DImage
{
public:
	//コンストラクタ。
	BossEnemyHPBarFrame();

	//デストラクタ。
	~BossEnemyHPBarFrame();

	//初期化。
	void Initialize();

	//更新。
	void Update();
};

