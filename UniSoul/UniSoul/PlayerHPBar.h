#pragma once
#include "2DImage.h"
#include "UnityChan.h"

class PlayerHPBar:public C2DImage
{
public:
	PlayerHPBar();
	~PlayerHPBar();
	void Initialize()override;
	void Update()override;
private:
	UnityChan*	m_unityChan;
};
