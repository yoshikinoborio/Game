#pragma once
#ifndef _TKPARTICLEEMITTER_H_
#define _TKPARTICLEEMITTER_H_

#include <list>

class CParticle;
/*!
* @brief	�p�[�e�B�N�������p�����[�^
*/
struct SParicleEmitParameter {
	//�������B
	void Init()
	{
		memset(this, 0, sizeof(SParicleEmitParameter));
	}
	const char* texturePath;			//!<�e�N�X�`���̃t�@�C���p�X�B
	float w;							//!<�p�[�e�B�N���̕��B
	float h;							//!<�p�[�e�B�N���̍����B
	float intervalTime;					//!<�p�[�e�B�N���̔����Ԋu�B
	D3DXVECTOR3 initSpeed;				//!<�����x�B
	D3DXVECTOR3 position;				//!<�ʒu�B
	float	life;						//!<�p�[�e�B�N���̐������ԁB

};
/*!
* @brief	�p�[�e�B�N���̔����@
*/
class CParticleEmitter {
public:

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
	void Init(const SParicleEmitParameter& param);
	void Update();
	void Render(const D3DXMATRIX& viewMatrix, const D3DXMATRIX& projMatrix);
private:
	SParicleEmitParameter	param;			//!<�p�����[�^�B
	std::list<CParticle*>	particleList;	//!<�p�[�e�B�N���̃��X�g�B
	float					timer;			//!<�^�C�}�[
};


#endif // _TKPARTICLEEMITTER_H_