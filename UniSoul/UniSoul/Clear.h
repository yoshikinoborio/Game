#pragma once
#include "2DImage.h"

//ゲームクリア画像。
class Clear : public C2DImage
{
public:
	//コンストラクタ。
	Clear();

	//デストラクタ。
	~Clear();

	//初期化。
	void Initialize();

	//更新。
	void Update();
};

