#pragma once
#include "2DImage.h"

//タイトルの画像表示クラス。
class Title : public C2DImage
{
public:
	//コンストラクタ。
	Title();

	//デストラクタ。
	~Title();

	//初期化。
	void Initialize();

	//更新。
	void Update();
};