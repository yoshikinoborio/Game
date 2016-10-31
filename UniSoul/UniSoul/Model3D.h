#pragma once

//�A�j���[�V�������Ȃ�3D���f���̃N���X�B
class Model3D
{
public:
	//�R���X�g���N�^�B
	Model3D();

	//�f�X�g���N�^�B
	~Model3D();

	//�������B
	void Initialize(LPCSTR FileName);

	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		D3DXMATRIX	m_world,
		D3DXMATRIX	m_rotation,
		int numDiffuseLight);

	//����B
	void Release();
	/*!
	* @brief	�V���h�E���V�[�o�[�̃t���O��ݒ�B
	*@param[in]	flag	�V���h�E���V�[�o�[�̃t���O�B
	*/
	void SetShadowReceiverFlag(bool flag)
	{
		m_isShadowReceiver = flag;
	}
private:
	LPD3DXMESH				m_mesh;					//���b�V���B
	LPDIRECT3DTEXTURE9*		m_textures;				//�e�N�X�`���B
	DWORD					m_numMaterial;			//�}�e���A���̐��B
	ID3DXEffect*			m_effect;				//�G�t�F�N�g�B
	bool					m_isShadowReceiver;		//�V���h�E���V�[�o�[�B
	D3DXMATRIX				m_LVP;					//���C�g�r���[�v���W�F�N�V�����s��
};