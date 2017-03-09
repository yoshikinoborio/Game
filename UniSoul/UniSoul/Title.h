#pragma once
#include "2DImage.h"

//タイトルの画像表示クラス。
class Title : public C2DImage
{
public:
	Title();
	~Title();
	void Initialize();
	void Update();
};