#pragma once
#include "2DImage.h"

class Title : public C2DImage
{
public:
	Title();
	~Title();
	void Initialize();
	void Update();
	void Draw();
};