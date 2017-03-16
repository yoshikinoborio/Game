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

	//TRUEを渡すとYOU DIEDのα値を増やしていく。
	void SetStartFlag(bool flag)
	{
		m_startFlag = flag;
	}
private:
	int		m_alph;		 //α値の変わり。
	bool	m_startFlag; //TRUEになったらYOU DIEDが見えるようになる。
};

