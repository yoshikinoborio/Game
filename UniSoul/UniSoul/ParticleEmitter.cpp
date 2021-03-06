#include "stdafx.h"
#include "ParticleEmitter.h"
#include "Particle.h"

using namespace std;

CParticleEmitter::CParticleEmitter()
{
	param = nullptr;
	timer = 0.0f;
}

CParticleEmitter::~CParticleEmitter()
{

}

void CParticleEmitter::Initialize()
{
	strcpy_s(m_ParticleName, param->texturePath);
	timer = 1.0f;
}

void CParticleEmitter::Update()
{
	if (timer >= param->intervalTime) {
		//パーティクルを生成。
		CParticle* p = new CParticle;
		p->Init(*param, param->initSpeed, m_emitPosition);
		timer = 0.0f;
		particleList.push_back(p);
	}
	//パーティクルの先頭を確保。
	auto it = particleList.begin();
	//パーティクルのリストの最後まで。
	while (it != particleList.end())
	{
		//パーティクルがfalseを返して来たら削除。
		if (!(*it)->Update()) {
			//パーティクルの解放。
			delete *it;
			//解放した次のパーティクルを確保。
			it = particleList.erase(it);
		}
		else
		{
			//次に進む処理。
			it++;
		}
	}
	timer += 1.0f / 60.0f;
	for (auto p : particleList) {
		p->Update();
	}
}
void CParticleEmitter::Render(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix)
{
	for (auto p : particleList) {
		p->Render(*viewMatrix, *projMatrix);
	}
}
