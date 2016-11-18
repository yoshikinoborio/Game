#include "stdafx.h"
#include "ParticleEmitter.h"
#include "Particle.h"

extern LPDIRECT3DDEVICE9 g_pd3dDevice;

using namespace std;

CParticleEmitter::CParticleEmitter()
{

}

CParticleEmitter::~CParticleEmitter()
{

}

void CParticleEmitter::Init(const SParicleEmitParameter& param)
{
	this->param = param;
	timer = 1.0f;
}

void CParticleEmitter::Update()
{
	if (timer >= param.intervalTime) {
		//�p�[�e�B�N���𐶐��B
		CParticle* p = new CParticle;
		p->Init(param);
		timer = 0.0f;
		particleList.push_back(p);
	}
	//�p�[�e�B�N���̐擪���m�ہB
	auto it = particleList.begin();
	//�p�[�e�B�N���̃��X�g�̍Ō�܂ŁB
	while (it != particleList.end())
	{
		//�p�[�e�B�N����false��Ԃ��ė�����폜�B
		if (!(*it)->Update()) {
			//�p�[�e�B�N���̉���B
			delete *it;
			//����������̃p�[�e�B�N�����m�ہB
			it = particleList.erase(it);
		}
		else
		{
			//���ɐi�ޏ����B
			it++;
		}
	}
	timer += 1.0f / 60.0f;
	for (auto p : particleList) {
		p->Update();
	}
}
void CParticleEmitter::Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix)
{
	for (auto p : particleList) {
		p->Render(viewMatrix, projMatrix);
	}
}
