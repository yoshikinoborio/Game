#pragma once
#include <vector>
#include "ParticleEmitter.h"

//リスポーンクラス。
class Respawn
{
public:
	//コンストラクタ。
	Respawn();

	//デストラクタ。
	~Respawn();

	//初期化。
	void Initialize();

	//更新。
	void Update();

	//描画。
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix);
private:
	std::vector<btGhostObject*>		m_ghostObjectList;	//ゴーストオブジェクト。
	CParticleEmitter*				m_pEmitter;
	D3DXVECTOR3						m_postion;
};

