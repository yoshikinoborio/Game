#pragma once
#include "Animation.h"
#include "SkinModelData.h"

class SkinModelData;
class Light;

	//�X�L�����f��
class SkinModel {
public:
	SkinModel();
	~SkinModel();
	//������
	void Initialize(SkinModelData* modelData);
	//�`��
	void Draw(D3DXMATRIX* viewMatrix, 
		D3DXMATRIX* projMatrix, 
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight);
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
		int numDiffuseLight
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
		int numDiffuseLight
		);
	//���C�g�̐ݒ�
	void SetLight(Light* light)
	{
		this->m_light = light;
	}
private:
	D3DXMATRIX				m_worldMatrix;		//���[���h�s��
	D3DXMATRIX				m_rotationMatrix;	//��]�s��
	SkinModelData*			m_skinModelData;	//�X�L�����f���f�[�^�B
	Animation				m_animation;		//�A�j���[�V����
	static const int		MAX_MATRIX_PALLET = 128;	//�}�g���N�X�p���b�g�̍ő吔
	D3DXMATRIX				m_boneMatrixPallet[MAX_MATRIX_PALLET];	//�}�g���N�X�p���b�g
	ID3DXEffect*			m_effect;			//�G�t�F�N�g
	Light*					m_light;			//���C�g�B
};