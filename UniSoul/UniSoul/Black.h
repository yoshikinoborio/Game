#pragma once
#include "2DImage.h"

//ブラックアウトの表現に使うクラス。
class Black :	public C2DImage
{
public:
	Black();
	~Black();
	void Initialize();
	void Update();
	//黒い画像のα値を増やしたり減らしたりする。
	void SetStartFlag(bool flag)
	{
		m_alphFlag = flag;
	}
private:
	int m_alph;	//α値の変わり。
	bool m_alphFlag; //FALSEの時はだんだん色が薄くなりTRUEにすると濃くなっていく。
};

