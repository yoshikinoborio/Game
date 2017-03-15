#pragma once
#include "2DImage.h"

//ブラックアウトの表現に使うクラス。
class Black :	public C2DImage
{
public:
	//コンストラクタ。
	Black();

	//デストラクタ。
	~Black();

	//初期化。
	void Initialize();

	//更新。
	void Update();

	//黒い画像のα値を増やしたり減らしたりするフラグ。
	void SetStartFlag(bool flag)
	{
		m_alphFlag = flag;
	}
private:
	int		m_alph;			//α値の変わり。
	bool	m_alphFlag;		//FALSEの時はだんだん色が薄くなりTRUEにすると濃くなっていく。
};

