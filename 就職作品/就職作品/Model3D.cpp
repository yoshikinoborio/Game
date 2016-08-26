#include "stdafx.h"
#include "Model3D.h"

Model3D::Model3D()
{
	m_mesh = NULL;
	m_textures = NULL;
	m_numMaterial = 0;
	m_effect = NULL;
}

Model3D::~Model3D()
{
	Release();
}

//������
void Model3D::Initialize(LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR name)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;	//�}�e���A���o�b�t�@

	//X�t�@�C���̃��[�h�B
	D3DXLoadMeshFromX(
		name,	//X�t�@�C���ւ̑��΂܂��͐�΃p�X
		D3DXMESH_SYSTEMMEM,		//���_�A�C���f�b�N�X�o�b�t�@�����̃��������g�������w�肷��
		pd3dDevice,				//D3D�̃f�o�C�X�ւ̃|�C���^
		NULL,					//�|���S���̗אڏ��̏o�͐�
		&pD3DXMtrlBuffer,		//�}�e���A���o�b�t�@�̏o�͐�
		NULL,					//�����������g�����������Ǝv���̂�NULL
		&m_numMaterial,			//�}�e���A���̐��̏o�͐�
		&m_mesh					//X�t�@�C������쐬���ꂽID3DXMesh�̃C���X�^���X�̊i�[��
		);

	// �}�e���A���o�b�t�@���擾�B
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

	m_textures = new LPDIRECT3DTEXTURE9[m_numMaterial];
	//�}�e���A���̐��������[�v���񂵂ăe�N�X�`�������[�h
	for (DWORD i = 0; i < m_numMaterial; i++)
	{
		m_textures[i] = NULL;
		//�摜�t�@�C������e�N�X�`�����쐬����B
		D3DXCreateTextureFromFileA(pd3dDevice,	//�f�o�C�X�̃|�C���^
			d3dxMaterials[i].pTextureFilename,	//�摜�t�@�C���ւ̑��΂܂��͐�΃p�X
			&m_textures[i]);					//�������ꂽ�e�N�X�`���I�u�W�F�N�g�̃|�C���^���Ԃ�
	}
	// �}�e���A���o�b�t�@������B
	pD3DXMtrlBuffer->Release();

	LPD3DXBUFFER  compileErrorBuffer = NULL;

	//�V�F�[�_�[���R���p�C���B
	HRESULT hr = D3DXCreateEffectFromFile(
		pd3dDevice,								//�����̃f�o�C�X�̃|�C���^
		"basic.fx",								//�V�F�[�_�v���O�������������܂ꂽ�t�@�C���ւ̑��΂܂��͐�΃p�X
		NULL,									//�v���v���Z�b�T�̒�`
		NULL,									//ID3DXInclude�C���^�[�t�F�C�X�̒�`
		D3DXSHADER_SKIPVALIDATION,				//�V�F�[�_�[�R���p�C�����̃R���p�C���I�v�V�������w��
		NULL,									//�G�t�F�N�g�Ԃŋ��L����O���[�o���ϐ����Ƃ�܂Ƃ߂Ă����ID3DXEffectPool�C���^�[�t�F�C�X��n��
		&m_effect,								//ID3DXEffect�̃C���X�^���X
		&compileErrorBuffer						//�R���p�C���G���[���N���������̃G���[��񂪊i�[�����
		);
	if (hr != S_OK) {
		//�V�F�[�_�[�̃G���[�\��
		MessageBox(NULL, (char*)(compileErrorBuffer->GetBufferPointer()), "error", MB_OK);
		std::abort();
	}
}

//�`��
void Model3D::Draw(LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	D3DXMATRIX	m_world,
	D3DXMATRIX	m_rotation,
	int numDiffuseLight)
{
	m_effect->SetTechnique("SkinModel");
	m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_effect->BeginPass(0);

	//�萔���W�X�^�ɐݒ肷��J���[�B
	D3DXVECTOR4 color(1.0f, 0.0f, 0.0f, 1.0f);
	//���[���h�s��̓]���B
	m_effect->SetMatrix("g_worldMatrix", &m_world);
	//�r���[�s��̓]���B
	m_effect->SetMatrix("g_viewMatrix", &viewMatrix);
	//�v���W�F�N�V�����s��̓]���B
	m_effect->SetMatrix("g_projectionMatrix", &projMatrix);	
	//��]�s���]���B
	m_effect->SetMatrix("g_rotationMatrix", &m_rotation);		
	//���C�g�̌�����]���B
	m_effect->SetVectorArray("g_diffuseLightDirection", diffuseLightDirection, numDiffuseLight);
	//���C�g�̃J���[��]���B
	m_effect->SetVectorArray("g_diffuseLightColor", diffuseLightColor, numDiffuseLight);
	//������ݒ�B
	m_effect->SetVector("g_ambientLight", &ambientLight);

	m_effect->CommitChanges();						//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B

	for (DWORD i = 0; i < m_numMaterial; i++)
	{
		m_effect->SetTexture("g_diffuseTexture", m_textures[i]);
		// Draw the m_mesh subset
		m_mesh->DrawSubset(i);
	}

	m_effect->EndPass();
	m_effect->End();
}

//���
void Model3D::Release()
{
	//���b�V�����J���B
	if (m_mesh != NULL) {
		m_mesh->Release();
		m_mesh = NULL;
	}
	//�e�N�X�`�����J���B
	if (m_textures != NULL) {
		for (unsigned int i = 0; i < m_numMaterial; i++) {
			if (m_textures[i] != NULL) {
				m_textures[i]->Release();
				m_textures[i] = NULL;
			}
		}
		delete[] m_textures;
		m_textures = NULL;
	}
	//�G�t�F�N�g���J���B
	if (m_effect != NULL) {
		m_effect->Release();
		m_effect = NULL;
	}
}