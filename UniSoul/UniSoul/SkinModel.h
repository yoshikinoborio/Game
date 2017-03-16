#pragma once
#include "Animation.h"
#include "SkinModelData.h"
#include "SkinModelDataResources.h"
#include "Light.h"

class SkinModelData;
class SkinModelDataResources;

	//�X�L�����f���B
class SkinModel {
public:
	//�R���X�g���N�^�B
	SkinModel();

	//�f�X�g���N�^�B
	~SkinModel();

	//�������B
	void Initialize(SkinModelData* modelData);

	//�`��B
	void Draw(D3DXMATRIX* viewMatrix, 
		D3DXMATRIX* projMatrix, 
		bool isDrawToShadowMap);
	/*!
	*@brief	�X�V�B
	*@details
	*@param[in]		trans	���s�ړ��B
	*@param[in]		rot		��]�B
	*@param[in]		scale	�g��B
	*/
	void Update(const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale);

	/*!
	* @brief	�����t�H�O�p�����[�^��ݒ�B
	*@param[in]	param0		�t�H�O�p�����[�^0
	*�t�H�O���|����n�߂鋗���B
	*@param[in]	param1		�t�H�O�p�����[�^�P
	*�t�H�O���|����؂鋗���B
	*/
	void SetFogDistParam(float param0,float param1)
	{
		m_fogDistParam[0] = param0;
		m_fogDistParam[1] = param1;
	}

	//�����t�H�O�̃t���O��ݒ�B
	void SetFogDistFlag(int flag)
	{
		m_fogDistFlag = flag;
	}

	/*!
	* @brief	�����t�H�O�p�����[�^��ݒ�B
	*@param[in]	param0		�t�H�O�p�����[�^0
	*�t�H�O���|����n�߂鍂���B
	*@param[in]	param1		�t�H�O�p�����[�^�P
	*�t�H�O���|����؂鍂���B
	*/
	void SetFogHeightParam(float param0,float param1)
	{
		m_fogHeightParam[0] = param0;
		m_fogHeightParam[1] = param1;
	}

	//�����t�H�O�̃t���O��ݒ�B
	void SetFogHeightFlag(int flag)
	{
		m_fogHeightFlag = flag;
	}

	void DrawMeshContainer(
		IDirect3DDevice9* pd3dDevice,
		LPD3DXMESHCONTAINER pMeshContainerBase,
		LPD3DXFRAME pFrameBase,
		ID3DXEffect* effect,
		D3DXMATRIX* worldMatrix,
		D3DXMATRIX* rotationMatrix,
		D3DXMATRIX* viewMatrix,
		D3DXMATRIX* projMatrix,
		Light*		light,
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
		Light*		light,
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
	D3DXMATRIX& GetWorldMatrix()
	{
		return m_worldMatrix;
	}
	//�@���}�b�v�̃��[�h�B
	//�v���C���[�̖@���}�b�v��ǂݍ��ޗp�̊֐��B
	void LoadNormalMap(const char* filePath, const char* BoneName);
	//�v���C���[�ȊO�̎��Ɏg���悤�B
	void LoadNormalMap(const char* filePath);

	//�@���}�b�v�̕ێ��t���O��ݒ�B
	void SetHasNormalMap(bool hasNormalMap)
	{
		m_hasNormalMap = hasNormalMap;
	}
	LPD3DXMESH GetOrgMeshFirst();
private:
	D3DXMATRIX				m_worldMatrix;				//���[���h�s��B
	D3DXMATRIX				m_rotationMatrix;			//��]�s��B
	SkinModelData*			m_skinModelData;			//�X�L�����f���f�[�^�B
	Animation				m_animation;				//�A�j���[�V�����B
	static const int		MAX_MATRIX_PALLET = 128;	//�}�g���N�X�p���b�g�̍ő吔�B
	D3DXMATRIX				m_boneMatrixPallet[MAX_MATRIX_PALLET];	//�}�g���N�X�p���b�g�B
	ID3DXEffect*			m_effect;					//�G�t�F�N�g�B
	ID3DXEffect*			m_shadoweffect;				//�V���h�E�G�t�F�N�g�B
	Light*					m_light;					//���C�g�B
	bool					m_isShadowReceiver;			//�V���h�E���V�[�o�[�B
	D3DXMATRIX				m_LVP;						//���C�g�r���[�v���W�F�N�V�����s��B
	LPDIRECT3DTEXTURE9		m_normalMap = NULL;			//�@���}�b�v�̃e�N�X�`���B
	LPDIRECT3DTEXTURE9		m_normalMap2 = NULL;		//�@���}�b�v(�v���C���[�̓�)�̃e�N�X�`���B
	LPDIRECT3DTEXTURE9		m_normalMap3 = NULL;		//�@���}�b�v(�v���C���[�̑�)�̃e�N�X�`���B
	bool					m_hasNormalMap = FALSE;		//�@���}�b�v��ێ����Ă���(�t���O)�H
	float					m_fogDistParam[2];			//�����t�H�O�̃p�����[�^�B
	int						m_fogDistFlag;				//�����t�H�O���|���Ȃ����|���邩�̃t���O�B
	float					m_fogHeightParam[2];		//�����t�H�O�̃p�����[�^�B
	int						m_fogHeightFlag;			//�����t�H�O���|���Ȃ����|���邩�̃t���O�B
};