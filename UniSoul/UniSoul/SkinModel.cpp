#include "stdafx.h"
#include "Game.h"
#include "SkinModel.h"
#include "SkinModelData.h"
#include "Light.h"


SkinModel::SkinModel()
{
	m_skinModelData = nullptr;
	D3DXMatrixIdentity(&m_worldMatrix);
	D3DXMatrixIdentity(&m_rotationMatrix);
	m_light = nullptr;
	m_effect = NULL;
	m_shadoweffect = NULL;
	m_isShadowReceiver = FALSE;
}

SkinModel::~SkinModel()
{

}

void SkinModel::Initialize(SkinModelData* modelData)
{
	m_effect = g_effectManager->LoadEffect("Assets/Shader/modellight.fx");
	m_skinModelData = modelData;
}

void SkinModel::Update(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale)
{
	D3DXMATRIX Trans,Scale;
	D3DXMatrixTranslation(&Trans, trans.x, trans.y, trans.z);
	D3DXMatrixRotationQuaternion(&m_rotationMatrix, &rot);
	D3DXMatrixScaling(&Scale, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(&m_worldMatrix, &Scale, &m_rotationMatrix);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &Trans);
	//�{�[���s����X�V�B
	if (m_skinModelData) {
		m_skinModelData->UpdateBoneMatrix(m_worldMatrix);	
	}
}

void SkinModel::Draw(D3DXMATRIX* viewMatrix,
	D3DXMATRIX* projMatrix ,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight,
	bool isDrawToShadowMap)
{
	if (m_skinModelData) {
		DrawFrame(
			g_pd3dDevice,
			m_skinModelData->GetFrameRoot(),
			m_effect,
			&m_worldMatrix,
			&m_rotationMatrix,
			viewMatrix,
			projMatrix,
			diffuseLightDirection,
			diffuseLightColor,
			ambientLight,
			numDiffuseLight,
			isDrawToShadowMap
			);
	}
}

void SkinModel::DrawMeshContainer(
	IDirect3DDevice9* pd3dDevice,
	LPD3DXMESHCONTAINER pMeshContainerBase,
	LPD3DXFRAME pFrameBase,
	ID3DXEffect* effect,
	D3DXMATRIX* worldMatrix,
	D3DXMATRIX* rotationMatrix,
	D3DXMATRIX* viewMatrix,
	D3DXMATRIX* projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight,
	bool isDrawToShadowMap
	)
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainerBase;
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	UINT iAttrib;
	LPD3DXBONECOMBINATION pBoneComb;

	D3DXMATRIXA16 matTemp;
	D3DCAPS9 d3dCaps;
	pd3dDevice->GetDeviceCaps(&d3dCaps);
	D3DXMATRIX viewProj;
	D3DXMatrixMultiply(&viewProj, viewMatrix, projMatrix);

	
		if (pMeshContainer->pSkinInfo != NULL) {
			//��ȊO�̃��f���̕`��
			if (isDrawToShadowMap == TRUE)
			{
				//�e�p�̃e�N�j�b�N��ݒ�
				m_effect->SetTechnique("SkinModelDrowToShadowMap");
			}
			else
			{
				m_effect->SetTechnique("SkinModel");
			}
		}
		else {
			//��̃��f���̕`��
			if (isDrawToShadowMap == TRUE)
			{
				//�e�p�̃e�N�j�b�N��ݒ�
				m_effect->SetTechnique("NoSkinModelDrowToShadowMap");
			}
			else
			{
				m_effect->SetTechnique("NoSkinModel");
			}
		}

		//���C�g�r���[�v���W�F�N�V�����s��̌v�Z�B
		m_LVP = game->Getshadowmapcamera()->GetShadowMapCameraViewMatrix() * game->Getshadowmapcamera()->GetShadowMapCameraProjectionMatrix();

		//�萔���W�X�^�ɐݒ肷��J���[�B
		D3DXVECTOR4 color(1.0f, 0.0f, 0.0f, 1.0f);
		//���[���h�s��̓]���B
		m_effect->SetMatrix("g_worldMatrix", &m_worldMatrix);
		//�r���[�s��̓]���B
		m_effect->SetMatrix("g_viewMatrix", viewMatrix);
		//�v���W�F�N�V�����s��̓]���B
		m_effect->SetMatrix("g_projectionMatrix", projMatrix);
		//��]�s���]���B
		m_effect->SetMatrix("g_rotationMatrix", &m_rotationMatrix);
		//���C�g
		//m_effect->SetValue("g_light", light, sizeof(Light));
		//���C�g�̌�����]���B
		m_effect->SetVectorArray("g_diffuseLightDirection", diffuseLightDirection, numDiffuseLight);
		////���C�g�̃J���[��]���B
		m_effect->SetVectorArray("g_diffuseLightColor", diffuseLightColor, numDiffuseLight);
		////������ݒ�B
		m_effect->SetVector("g_ambientLight", &ambientLight);
		//�e�̃t���O��]���B
		//�e�𗎂Ƃ��������f���Ńt���O��TRUE�ɂ��Ă���
		m_effect->SetInt("g_ShadowReceiverFlag", m_isShadowReceiver);
		//���C�g�r���[�v���W�F�N�V�����s��̓]���B
		m_effect->SetMatrix("g_mLVP", &m_LVP);
		//�r���[�v���W�F�N�V�����B
		m_effect->SetMatrix("g_mViewProj", &viewProj);
		//���_�B
		m_effect->SetVector("vEyePos", &(D3DXVECTOR4)game->GetCamera()->GetEyePt());
		//�e��`�悵�Ă��郌���_�[�^�[�Q�b�g�̃e�N�X�`�����擾�B
		if (m_isShadowReceiver == TRUE)
		{
			m_effect->SetTexture("g_shadowTexture", game->GetRenderTarget()->GetTexture());
		}

		if (pMeshContainer->pSkinInfo != NULL)
		{
			//�X�L�����L��B
			pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
			for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
			{
				// first calculate all the world matrices
				for (DWORD iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
				{
					DWORD iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
					if (iMatrixIndex != UINT_MAX)
					{
						D3DXMatrixMultiply(
							&m_boneMatrixPallet[iPaletteEntry],
							&pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
							pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]
							);
					}
				}


				m_effect->SetMatrixArray("g_mWorldMatrixArray", m_boneMatrixPallet, pMeshContainer->NumPaletteEntries);
				m_effect->SetInt("g_numBone", pMeshContainer->NumInfl);
				// �f�B�t���[�Y�e�N�X�`���B
				m_effect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId]);

				// �{�[�����B
				m_effect->SetInt("CurNumBones", pMeshContainer->NumInfl - 1);
				D3DXMATRIX viewRotInv;
				D3DXMatrixInverse(&viewRotInv, NULL, viewMatrix);
				viewRotInv.m[3][0] = 0.0f;
				viewRotInv.m[3][1] = 0.0f;
				viewRotInv.m[3][2] = 0.0f;
				viewRotInv.m[3][3] = 1.0f;
				D3DXMatrixTranspose(&viewRotInv, &viewRotInv);
				m_effect->SetMatrix("g_viewMatrixRotInv", &viewRotInv);
				m_effect->Begin(0, D3DXFX_DONOTSAVESTATE);
				m_effect->BeginPass(0);
				m_effect->CommitChanges();
				pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
				m_effect->EndPass();
				m_effect->End();

			}
		}
		else {

			D3DXMATRIX mWorld;
			if (pFrame != NULL) {
				mWorld = pFrame->CombinedTransformationMatrix;
			}
			else {
				mWorld = *worldMatrix;
			}

			m_effect->SetMatrix("g_worldMatrix", &mWorld);
			m_effect->SetMatrix("g_rotationMatrix", rotationMatrix);
			m_effect->Begin(0, D3DXFX_DONOTSAVESTATE);
			m_effect->BeginPass(0);
			for (DWORD i = 0; i < pMeshContainer->NumMaterials; i++) {

				m_effect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[i]);
				m_effect->CommitChanges();
				pMeshContainer->MeshData.pMesh->DrawSubset(i);
			}
			m_effect->EndPass();
			m_effect->End();
		}
}

void SkinModel::DrawFrame(
	IDirect3DDevice9* pd3dDevice,
	LPD3DXFRAME pFrame,
	ID3DXEffect* effect,
	D3DXMATRIX* worldMatrix,
	D3DXMATRIX* rotationMatrix,
	D3DXMATRIX* viewMatrix,
	D3DXMATRIX* projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight,
	bool isDrawToShadowMap
	)
{
	LPD3DXMESHCONTAINER pMeshContainer;

	pMeshContainer = pFrame->pMeshContainer;
	while (pMeshContainer != NULL)
	{
		DrawMeshContainer(
			pd3dDevice,
			pMeshContainer,
			pFrame,
			effect,
			worldMatrix,
			rotationMatrix,
			viewMatrix,
			projMatrix,
			diffuseLightDirection,
			diffuseLightColor,
			ambientLight,
			numDiffuseLight,
			isDrawToShadowMap
			);

		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}

	if (pFrame->pFrameSibling != NULL)
	{
		DrawFrame(
			pd3dDevice,
			pFrame->pFrameSibling,
			m_effect,
			worldMatrix,
			rotationMatrix,
			viewMatrix,
			projMatrix,
			diffuseLightDirection,
			diffuseLightColor,
			ambientLight,
			numDiffuseLight,
			isDrawToShadowMap
			);
	}

	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(
			pd3dDevice,
			pFrame->pFrameFirstChild,
			m_effect,
			worldMatrix,
			rotationMatrix,
			viewMatrix,
			projMatrix,
			diffuseLightDirection,
			diffuseLightColor,
			ambientLight,
			numDiffuseLight,
			isDrawToShadowMap
			);
	}
}