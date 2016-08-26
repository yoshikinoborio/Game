#pragma once

//3D���f���̃N���X
class Model3D
{
public:
	//�R���X�g���N�^
	Model3D();

	//�f�X�g���N�^
	~Model3D();

	//������
	void Initialize(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR name);

	//�`��
	void Draw(LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		D3DXMATRIX	m_world,
		D3DXMATRIX	m_rotation,
		int numDiffuseLight);

	//���
	void Release();
private:
	LPD3DXMESH				m_mesh;				//���b�V���B
	LPDIRECT3DTEXTURE9*		m_textures;			//�e�N�X�`���B
	DWORD					m_numMaterial;		//�}�e���A���̐��B
	ID3DXEffect*			m_effect;			//�G�t�F�N�g�B
};