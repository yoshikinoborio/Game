#pragma once
#include "2DImage.h"

//プレイヤーが死んだ時に出てくるYOU DIEDクラス。
class YOUDIED :public C2DImage
{
public:
	YOUDIED();
	~YOUDIED();
	void Initialize();
	void Update();
	//TRUEを渡すとYOU DIEDのα値を増やしていく。
	void SetStartFlag(bool flag)
	{
		m_startFlag = flag;
	}
private:
	int m_alph;	//α値の変わり。
	bool m_startFlag; //TRUEになったらYOU DIEDが見えるようになる。
};