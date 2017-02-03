#pragma once
//�����_�����O�^�[�Q�b�g�B
class RenderTarget {
public:
	//�R���X�g���N�^
	RenderTarget();
	//�f�X�g���N�^
	~RenderTarget();

	//���
	void Release();
	/*!
	*@brief	�����_�����O�^�[�Q�b�g�̍쐬�B
	*@param[in]	w					�����_�����O�^�[�Q�b�g�̕��B
	*@param[in]	h					�����_�����O�^�[�Q�b�g�̍����B
	*@param[in]	mipLevel			�~�b�v�}�b�v���x���B
	*@param[in]	colorFormat			�J���[�o�b�t�@�̃t�H�[�}�b�g�B
	*@param[in]	depthStencilFormat	�f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g�B
	*@param[in]	multiSampleType		�}���`�T���v�����O�̎�ށB
	*@param[in]	multiSampleQuality	�}���`�T���v�����O�̕i���B
	*/
	void Create(
		int w,
		int h,
		int mipLevel,
		D3DFORMAT colorFormat,
		D3DFORMAT depthStencilFormat,
		D3DMULTISAMPLE_TYPE multiSampleType,
		int multiSampleQuality);
	//�T�[�t�F�X�̎擾
	LPDIRECT3DSURFACE9 GetSurface()
	{
		return m_surface;
	}
	//�f�v�X�X�e���V���o�b�t�@�̎擾
	LPDIRECT3DSURFACE9 GetDepthStencilBuffer()
	{
		return m_depthSurface;
	}
	//�e�N�X�`���̎擾
	LPDIRECT3DTEXTURE9 GetTexture()
	{
		return m_texture;
	}
	//�����擾�B
	
	int GetWidth() const
	{
		return m_width;
	}
	//�������擾
	int GetHeight() const
	{
		return m_height;
	}
private:
	LPDIRECT3DSURFACE9		m_depthSurface;		//�[�x�o�b�t�@�p�̃T�[�t�F�C�X(�f�v�X�X�e���V���o�b�t�@)
	LPDIRECT3DTEXTURE9		m_texture;			//�������ݐ�̃e�N�X�`���B
	LPDIRECT3DSURFACE9		m_surface;			//�T�[�t�F�C�X
	int						m_width = 0;		//��
	int						m_height = 0;		//����
};