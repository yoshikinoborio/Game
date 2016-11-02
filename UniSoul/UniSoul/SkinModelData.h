#pragma once
struct D3DXFRAME_DERIVED : public D3DXFRAME {
	D3DXMATRIXA16	CombinedTransformationMatrix;	//�����ςݍs��B
};
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER {
	LPDIRECT3DTEXTURE9* ppTextures;
	LPD3DXMESH pOrigMesh;
	LPD3DXATTRIBUTERANGE pAttributeTable;
	DWORD NumAttributeGroups;
	DWORD NumInfl;
	LPD3DXBUFFER pBoneCombinationBuf;
	D3DXMATRIX** ppBoneMatrixPtrs;
	D3DXMATRIX* pBoneOffsetMatrices;
	DWORD NumPaletteEntries;
	bool UseSoftwareVP;
	DWORD iAttributeSW;
};
class Animation;

//�X�L�����f���f�[�^�N���X
class SkinModelData{
public:
	SkinModelData();
	~SkinModelData();
	
	//���f���f�[�^�����[�h
	//filePath	�t�@�C���p�X
	//anim		�A�j���[�V�����t�����f���f�[�^�̏ꍇ�A�A�j���[�V�����N���X���\�z�����
	void LoadModelData(const char* filePath, Animation* anim);

	//�t���[�����[�g�̎擾
	LPD3DXFRAME GetFrameRoot()
	{
		return m_frameRoot;
	}

	//�A�j���[�V�����R���g���[���[�̎擾
	ID3DXAnimationController* GetAnimationController()
	{
		return m_pAnimController;
	}

	//��ԍŏ��Ɍ��������I���W�i�����b�V�����擾�B
	LPD3DXMESH GetOrgMeshFirst();

	//��ԍŏ��Ɍ��������I���W�i�����b�V�����擾�B
	LPD3DXMESH GetOrgMesh(LPD3DXFRAME frame);

	//���[�g�̃{�[�����擾�B
	D3DXMATRIX* GetRootBoneWorldMatrix()
	{
		D3DXFRAME_DERIVED* frameDer = (D3DXFRAME_DERIVED*)m_frameRoot;
		return &frameDer->CombinedTransformationMatrix;
	}

	//�{�[���s��̍X�V
	void UpdateBoneMatrix(const D3DXMATRIX& matWorld);

	void Release();
private:
	LPD3DXFRAME					m_frameRoot;		//�t���[�����[�g�B
	ID3DXAnimationController*   m_pAnimController;	//�A�j���[�V�����R���g���[���B
};
