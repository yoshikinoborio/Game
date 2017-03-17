#pragma once
#include "RenderTarget.h"

namespace {
	static const int	MGF_DOWN_SAMPLE_COUNT = 4;							//MGF�_�E���T���v�����O�̉񐔁B
	static const int	NUM_WEIGHTS = 8;									//�K�E�X�u���[�̏d�݁B
}

class Bloom {
public:
	/*!
	* @brief	�R���X�g���N�^�B
	*/
	Bloom();
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~Bloom();
	/*!
	* @brief	�`��B
	*/
	void Render();
	//�d�݂̍X�V�B
	void UpdateWeight(float dispersion);
private:
	
	LPD3DXEFFECT		m_effect;												//�V�F�[�_�[�G�t�F�N�g�B
	RenderTarget		m_luminanceRenderTarget;								//�P�x�𒊏o���邽�߂̃����_�����O�^�[�Q�b�g�B
	RenderTarget		m_downSamplingRenderTarget[MGF_DOWN_SAMPLE_COUNT][2];	//MGF�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g�B
	float				m_weights[NUM_WEIGHTS];								//�K�E�X�u���[�Ŏg���d�݃e�[�u���B
};