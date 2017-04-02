#pragma once
#include "2DImage.h"

//プレイヤーが死んだ時に出てくるYou Diedクラス。
class YouDied :public C2DImage
{
public:
	//コンストラクタ。
	YouDied();

	//デストラクタ。
	~YouDied();
	//初期化。
	void Initialize();

	//更新。
	void Update();

	//You Deadの文字を描画する処理。
	void YouDiedDrawProcess();
private:
	int		m_alph;		 //α値の変わり。
};

