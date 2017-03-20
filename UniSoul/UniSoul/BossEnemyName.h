#pragma once
#include "2DImage.h"

//ボスの名前表示。
class BossEnemyName :public C2DImage
{
public:
	//コンストラクタ。
	BossEnemyName();

	//デストラクタ。
	~BossEnemyName();

	//初期化。
	void Initialize();

	//更新。
	void Update();
};

