#pragma once
#include "2DImage.h"
#include "UnityChan.h"

//プレイヤーのHPバークラス。
class PlayerHPBar:public C2DImage
{
public:
	//コンストラクタ。
	PlayerHPBar();

	//デストラクタ。
	~PlayerHPBar();

	//初期化。
	void Initialize();

	//更新。
	void Update();
private:
	UnityChan*	m_unityChan;	//プレイヤーのインスタンス。
};
