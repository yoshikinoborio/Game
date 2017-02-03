#include "stdafx.h"
#include "SceneManager.h"
#include "bloom.h"

void Bloom::UpdateWeight(float dispersion)
{
	float total = 0;
	for (int i = 0; i<NUM_WEIGHTS; i++) {
		weights[i] = expf(-0.5f*(float)(i*i) / dispersion);
		total += 2.0f*weights[i];

	}
	// �K�i��
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		weights[i] /= total;
	}
}

Bloom::Bloom()
{
	//g_effectManager = new EffectManager;
	//�u���[���̃V�F�[�_�[�����[�h
	effect = g_effectManager->LoadEffect("Assets/Shader/bloom.fx");
	//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬����B
	luminanceRenderTarget.Create(
		FRAME_BUFFER_WITDH,		//���ƍ����̓t���[���o�b�t�@�Ɠ����ɂ��Ă����B
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A16B16G16R16F,	//���������������_�o�b�t�@�ɂ���B
		D3DFMT_D16,				//�g��Ȃ��̂�16bit�B�{���͍쐬����K�v���Ȃ��B
		D3DMULTISAMPLE_NONE,	//�}���`�T���v�����O�̎�ށB����̓}���`�T���v�����O�͍s��Ȃ��̂�D3DMULTISAMPLE_NONE�ł����B
		0						//�}���`�T���v�����O�̕i�����x���B����̓}���`�T���v�����O�͍s��Ȃ��̂�0�ł����B
	);

	int w = FRAME_BUFFER_WITDH;
	int h = FRAME_BUFFER_HEIGHT;
	//MGF�p�̃����_�����O�^�[�Q�b�g���쐬�B
	for (int i = 0; i < MGF_DOWN_SAMPLE_COUNT; i++) {


		//�u���[�������邽�߂̃_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g���쐬�B
		//���u���[�p�B
		w /= 2;	//���̉𑜓x�𔼕��ɂ���B
		downSamplingRenderTarget[i][0].Create(
			w,
			h,
			1,
			D3DFMT_A16B16G16R16F,	//���������������_�o�b�t�@�ɂ���B
			D3DFMT_D16,				//�g��Ȃ��̂�16bit�B�{���͍쐬����K�v���Ȃ��B
			D3DMULTISAMPLE_NONE,	//�}���`�T���v�����O�̎�ށB����̓}���`�T���v�����O�͍s��Ȃ��̂�D3DMULTISAMPLE_NONE�ł����B
			0						//�}���`�T���v�����O�̕i�����x���B����̓}���`�T���v�����O�͍s��Ȃ��̂�0�ł����B
		);
		//�c�u���[�p�B
		h /= 2;	//�c�̉𑜓x�𔼕��ɂ���B
		downSamplingRenderTarget[i][1].Create(
			w,	//�c�Ɖ��̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
			h,
			1,
			D3DFMT_A16B16G16R16F,	//���������������_�o�b�t�@�ɂ���B
			D3DFMT_D16,				//�g��Ȃ��̂�16bit�B�{���͍쐬����K�v���Ȃ��B
			D3DMULTISAMPLE_NONE,	//�}���`�T���v�����O�̎�ށB����̓}���`�T���v�����O�͍s��Ȃ��̂�D3DMULTISAMPLE_NONE�ł����B
			0						//�}���`�T���v�����O�̕i�����x���B����̓}���`�T���v�����O�͍s��Ȃ��̂�0�ł����B
		);
	}

}

Bloom::~Bloom()
{

}

void Bloom::Render()
{
	// Z�e�X�g�Ŏ��s���Ă�������獢��̂ŁAZ�e�X�g�͖����ɂ��Ă����B
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//�܂��͋P�x�𒊏o����B
	{
		// ���u�����h������Ȃ��B
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX����B
		g_pd3dDevice->SetRenderTarget(0, luminanceRenderTarget.GetSurface());
		g_pd3dDevice->SetDepthStencilSurface(luminanceRenderTarget.GetDepthStencilBuffer());
		//���ŃN���A�B
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		// �P�x���o�e�N�j�b�N���Z�b�g�B
		effect->SetTechnique("SamplingLuminance");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		//�V�[���e�N�X�`����ݒ肷��B
		effect->SetTexture("g_scene", static_cast<GameScene*>(g_pScenes)->GetMainRenderTarget()->GetTexture());
		//�萔���W�X�^�ւ̕ύX���R�~�b�g�B
		effect->CommitChanges();
		static_cast<GameScene*>(g_pScenes)->DrawQuadPrimitive();

		effect->EndPass();
		effect->End();
		// �ύX���������_�����O�X�e�[�g�����ɖ߂��B
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	//�K�E�X�u���[�Ŏg���d�݃e�[�u�����X�V�B
	UpdateWeight(25.0f);
	//�u���[��������P�x�e�N�X�`���̃T�C�Y�B
	int luminanceTexW = luminanceRenderTarget.GetWidth();
	int luminanceTexH = luminanceRenderTarget.GetHeight();
	LPDIRECT3DTEXTURE9 blurTexture = luminanceRenderTarget.GetTexture();
	for (int i = 0; i < MGF_DOWN_SAMPLE_COUNT; i++) {
		//�P�x�𒊏o�����e�N�X�`����X�u���[
		g_pd3dDevice->SetRenderTarget(0, downSamplingRenderTarget[i][0].GetSurface());

		effect->SetTechnique("XBlur");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		//�P�x�e�N�X�`���̃T�C�Y��]���B
		float size[2];
		size[0] = (float)luminanceTexW;
		size[1] = (float)luminanceTexH;
		effect->SetValue("g_luminanceTexSize", size, sizeof(size));

		//�I�t�Z�b�g��]���B
		float offset[2];
		offset[0] = 16.0f / size[0];
		offset[1] = 0.0f;
		effect->SetValue("g_offset", offset, sizeof(offset));

		//�����_�����O�^�[�Q�b�g�̃T�C�Y��]���B
		float renderTargetSize[2];
		renderTargetSize[0] = (float)downSamplingRenderTarget[i][0].GetWidth();
		renderTargetSize[1] = (float)downSamplingRenderTarget[i][0].GetHeight();
		effect->SetValue("g_renderTargetSize", renderTargetSize, sizeof(renderTargetSize));

		effect->SetValue("g_weight", weights, sizeof(weights));

		effect->SetTexture("g_blur", blurTexture);
		effect->CommitChanges();
		static_cast<GameScene*>(g_pScenes)->DrawQuadPrimitive();

		effect->EndPass();
		effect->End();



		//�P�x�𒊏o�����e�N�X�`����Y�u���[

		g_pd3dDevice->SetRenderTarget(0, downSamplingRenderTarget[i][1].GetSurface());

		effect->SetTechnique("YBlur");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);

		blurTexture = downSamplingRenderTarget[i][0].GetTexture();
		//�P�x�e�N�X�`���̃T�C�Y��]���B
		size[0] = (float)downSamplingRenderTarget[i][0].GetWidth();
		size[1] = (float)downSamplingRenderTarget[i][0].GetHeight();
		effect->SetValue("g_luminanceTexSize", size, sizeof(size));

		//�I�t�Z�b�g��]���B
		offset[0] = 0.0f;
		offset[1] = 16.0f / size[1];
		effect->SetValue("g_offset", offset, sizeof(offset));

		//�����_�����O�^�[�Q�b�g�̃T�C�Y��]���B
		renderTargetSize[0] = (float)downSamplingRenderTarget[i][1].GetWidth();
		renderTargetSize[1] = (float)downSamplingRenderTarget[i][1].GetHeight();
		effect->SetValue("g_renderTargetSize", renderTargetSize, sizeof(renderTargetSize));

		effect->SetValue("g_weight", weights, sizeof(weights));

		effect->SetTexture("g_blur", blurTexture);
		effect->SetFloat("g_mulYBlurOutputColor", ((float)(MGF_DOWN_SAMPLE_COUNT - i)) / MGF_DOWN_SAMPLE_COUNT);
		effect->CommitChanges();
		static_cast<GameScene*>(g_pScenes)->DrawQuadPrimitive();

		effect->EndPass();
		effect->End();

		luminanceTexW = downSamplingRenderTarget[i][1].GetWidth();
		luminanceTexH = downSamplingRenderTarget[i][1].GetHeight();
		blurTexture = downSamplingRenderTarget[i][1].GetTexture();

		//���Z�����B
		offset[0] = 0.5f / downSamplingRenderTarget[i][1].GetWidth();
		offset[1] = 0.5f / downSamplingRenderTarget[i][1].GetHeight();
		//���C�������_�����O�^�[�Q�b�g�ɖ߂��B
		g_pd3dDevice->SetRenderTarget(0, static_cast<GameScene*>(g_pScenes)->GetMainRenderTarget()->GetSurface());
		g_pd3dDevice->SetDepthStencilSurface(static_cast<GameScene*>(g_pScenes)->GetMainRenderTarget()->GetDepthStencilBuffer());
		//���Z�����B
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		effect->SetTechnique("Final");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		effect->SetTexture("g_blur", blurTexture);
		effect->SetValue("g_offset", offset, sizeof(offset));
		effect->CommitChanges();
		static_cast<GameScene*>(g_pScenes)->DrawQuadPrimitive();

		effect->EndPass();
		effect->End();

		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}


	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}