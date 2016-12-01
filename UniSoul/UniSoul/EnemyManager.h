#pragma once
#include "Animation.h"
//�G�l�~�[�S���̏���������N���X�B
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
	void Release();
	Animation m_animation;
};