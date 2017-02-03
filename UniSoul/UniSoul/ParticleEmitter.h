#pragma once
#ifndef _TKPARTICLEEMITTER_H_
#define _TKPARTICLEEMITTER_H_

#include <list>
#include "ParticleParameterTable.h"
#define _CRT_SECURE_NO_WARNINGS 1
#define MAX_NAME 255
class CParticle;
/*!
* @brief	パーティクルの発生機
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
	* @brief	コンストラクタ。
	*/
	CParticleEmitter();
	/*!
	* @brief	デストラクタ。
	*/
	~CParticleEmitter();
	/*!
	*@brief	初期化。
	*@param[in]	camera		パーティクルの描画で使用するカメラ。
	*@param[in]	param		パーティクル生成用のパラメータ。
	*/
	void Init();
	void Update();
	void Render(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix);
	//パーティクルテーブルのパーティクルを設定。
	void SetEmitParameter(SParicleEmitParameter* param) {
		this->param = param;
	}
	//渡されたパーティクルエミッターの名前を設定。
	void SetEmitterName(LPCSTR name) {
		CH_ASSERT(strlen(name) < MAX_NAME);
		strcpy(m_EmitterName, name);
	}
	//発生場所をセット。
	void SetEmitPos(D3DXVECTOR3 pos) {
		m_emitPosition = pos;
	}
private:
	SParicleEmitParameter*	param;			//!<パラメータ。
	std::list<CParticle*>	particleList;	//!<パーティクルのリスト。
	float					timer;			//!<タイマー
	char m_EmitterName[MAX_NAME];			//エミッターの名前。
	char m_ParticleName[MAX_NAME];			//パーティクルの名前。
	D3DXVECTOR3 m_emitPosition;				//エミッターの発生場所。
};


#endif // _TKPARTICLEEMITTER_H_