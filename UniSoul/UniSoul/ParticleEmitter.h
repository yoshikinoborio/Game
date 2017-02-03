#pragma once
#ifndef _TKPARTICLEEMITTER_H_
#define _TKPARTICLEEMITTER_H_

#include <list>
#include "ParticleParameterTable.h"
#define _CRT_SECURE_NO_WARNINGS 1
#define MAX_NAME 255
class CParticle;
/*!
* @brief	�p�[�e�B�N���̔����@
*/
class CParticleEmitter {
public:
	static CParticleEmitter* EmitterCreate(LPCSTR EmitterName, ParicleType type, D3DXVECTOR3 pos) {
		CParticleEmitter* pEmitter = new CParticleEmitter;
		pEmitter->SetEmitParameter(static_cast<SParicleEmitParameter*>(ParticleParamPT_Array[type]));
		pEmitter->SetEmitterName(EmitterName);
		pEmitter->SetEmitPos(pos);
		pEmitter->Init();
		return pEmitter;
	}
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	CParticleEmitter();
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~CParticleEmitter();
	/*!
	*@brief	�������B
	*@param[in]	camera		�p�[�e�B�N���̕`��Ŏg�p����J�����B
	*@param[in]	param		�p�[�e�B�N�������p�̃p�����[�^�B
	*/
	void Init();
	void Update();
	void Render(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix);
	//�p�[�e�B�N���e�[�u���̃p�[�e�B�N����ݒ�B
	void SetEmitParameter(SParicleEmitParameter* param) {
		this->param = param;
	}
	//�n���ꂽ�p�[�e�B�N���G�~�b�^�[�̖��O��ݒ�B
	void SetEmitterName(LPCSTR name) {
		CH_ASSERT(strlen(name) < MAX_NAME);
		strcpy(m_EmitterName, name);
	}
	//�����ꏊ���Z�b�g�B
	void SetEmitPos(D3DXVECTOR3 pos) {
		m_emitPosition = pos;
	}
private:
	SParicleEmitParameter*	param;			//!<�p�����[�^�B
	std::list<CParticle*>	particleList;	//!<�p�[�e�B�N���̃��X�g�B
	float					timer;			//!<�^�C�}�[
	char m_EmitterName[MAX_NAME];			//�G�~�b�^�[�̖��O�B
	char m_ParticleName[MAX_NAME];			//�p�[�e�B�N���̖��O�B
	D3DXVECTOR3 m_emitPosition;				//�G�~�b�^�[�̔����ꏊ�B
};


#endif // _TKPARTICLEEMITTER_H_