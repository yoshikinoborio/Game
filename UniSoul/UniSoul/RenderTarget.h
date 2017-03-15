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
		const int& w,
		const int& h,
		const int& mipLevel,
		const D3DFORMAT& colorFormat,
		const D3DFORMAT& depthStencilFormat,
		const D3DMULTISAMPLE_TYPE& multiSampleType,
		const int& multiSampleQuality);

	//�T�[�t�F�X�̎擾
	const LPDIRECT3DSURFACE9& GetSurface() const
	{
		return m_surface;
	}

	//�f�v�X�X�e���V���o�b�t�@�̎擾
	const LPDIRECT3DSURFACE9& GetDepthStencilBuffer() const
	{
		return m_depthSurface;
	}

	//�e�N�X�`���̎擾
	const LPDIRECT3DTEXTURE9& GetTexture() const
	{
		return m_texture;
	}

	//�����擾�B
	const int& GetWidth() const
	{
		return m_width;
	}

	//�������擾
	const int& GetHeight() const
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