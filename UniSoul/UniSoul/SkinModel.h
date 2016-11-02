#pragma once
#include "Animation.h"
#include "SkinModelData.h"

class SkinModelData;
class Light;

	//�X�L�����f���B
class SkinModel {
public:
	SkinModel();
	~SkinModel();
	//�������B
	void Initialize(SkinModelData* modelData);
	//�`��B
	void Draw(D3DXMATRIX* viewMatrix, 
		D3DXMATRIX* projMatrix, 
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight,
		bool isDrawToShadowMap);
	/*!
	*@brief	�X�V�B
	*@details
	*@param[in]		trans	���s�ړ��B
	*@param[in]		rot		��]�B
	*@param[in]		scale	�g��B
	*/
	void Update(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale);

	void DrawMeshContainer(
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
		);
	void DrawFrame(
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
		);
	//���C�g�̐ݒ�B
	void SetLight(Light* light)
	{
		this->m_light = light;
	}
	//�V���h�E���V�[�o�[�̃t���O��ݒ�B
	void SetShadowReceiverFlag(bool flag)
	{
		m_isShadowReceiver = flag;
	}

	LPD3DXMESH GetOrgMeshFirst();
private:
	D3DXMATRIX				m_worldMatrix;		//���[���h�s��B
	D3DXMATRIX				m_rotationMatrix;	//��]�s��B
	SkinModelData*			m_skinModelData;	//�X�L�����f���f�[�^�B
	Animation				m_animation;		//�A�j���[�V�����B
	static const int		MAX_MATRIX_PALLET = 128;	//�}�g���N�X�p���b�g�̍ő吔�B
	D3DXMATRIX				m_boneMatrixPallet[MAX_MATRIX_PALLET];	//�}�g���N�X�p���b�g�B
	ID3DXEffect*			m_effect;			//�G�t�F�N�g�B
	ID3DXEffect*			m_shadoweffect;			//�V���h�E�G�t�F�N�g�B
	Light*					m_light;			//���C�g�B
	bool					m_isShadowReceiver;		//�V���h�E���V�[�o�[�B
	D3DXMATRIX				m_LVP;					//���C�g�r���[�v���W�F�N�V�����s��
};