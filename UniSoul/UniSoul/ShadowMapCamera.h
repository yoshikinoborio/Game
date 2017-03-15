#pragma once

class UnityChan;

//�V���h�E�}�b�v�J�����N���X�B
class ShadowMapCamera
{
public:
	//�R���X�g���N�^�B
	ShadowMapCamera();

	//�f�X�g���N�^�B
	~ShadowMapCamera();

	//�������B
	void Initialize();

	//�X�V�B
	void Update();

	//�V���h�E�J�����̃r���[�s��ƃp�[�X�y�N�e�B�u�ˉe�s��̍쐬�B
	void ShadowCameraMatrixUpadate();

	//�V���h�E�J�������v���C���[��ǂ������鏈���B
	void ShadowCameraTargetPlayer();

	//�r���[�s��̐ݒ�B
	void SetShadowMapCameraViewMatrix(const D3DXMATRIX& View)
	{
		m_shadowmapcameraviewMatrix = View;
	}

	//�r���[�s��̎擾�B
	const D3DXMATRIX& GetShadowMapCameraViewMatrix() const
	{
		return m_shadowmapcameraviewMatrix;
	}

	//�v���W�F�N�V�����s��̐ݒ�B
	void SetShadowMapCameraProjectionMatrix(const D3DXMATRIX& Proj)
	{
		m_shadowmapcameraprojectionMatrix = Proj;
	}

	//�v���W�F�N�V�����s��̎擾�B
	const D3DXMATRIX& GetShadowMapCameraProjectionMatrix() const
	{
		return m_shadowmapcameraprojectionMatrix;
	}

	//�J�����̍��W�̐ݒ�B
	void SetShadowMapCameraEyePt(const D3DXVECTOR3& Eye)
	{
		m_shadowmapcameraeyePt = Eye;
	}

	//�J�����̍��W�̎擾�B
	const D3DXVECTOR3& GetShadowMapCameraEyePt() const
	{
		return m_shadowmapcameraeyePt;
	}

	//�J�����̒����_�̐ݒ�B
	void SetShadowMapCameraLooktPt(const D3DXVECTOR3& Lookat)
	{
		m_shadowmapcameralookatPt = Lookat;
	}

	//�J�����̒����_�̎擾�B
	const D3DXVECTOR3& GetShadowMapCameraLooktPt() const
	{
		return m_shadowmapcameralookatPt;
	}

	//�J�����̏�����̐ݒ�B
	void SetShadowMapCameraUpVec(const D3DXVECTOR3& Up)
	{
		m_shadowmapcameraupvec = Up;
	}

	//�J�����̏�����̎擾�B
	const D3DXVECTOR3& GetShadowMapCameraUpVec() const
	{
		return m_shadowmapcameraupvec;
	}

	//�t�@�[�̐ݒ�B
	void SetShadowMapCameraFar(const float& Far)
	{
		m_shadowmapcamerafar = Far;
	}

	//�t�@�[�̎擾�B
	const float& GetShadowMapCameraFar() const
	{
		return m_shadowmapcamerafar;
	}

	//��A�[�̐ݒ�B
	void SetNear(const float& Near)
	{
		m_shadowmapcameranear = Near;
	}

	//��A�[�̎擾�B
	const float& GetShadowMapCameraNear() const
	{
		return m_shadowmapcameranear;
	}

	//�A�X�y�N�g��̐ݒ�B
	void SetShadowMapCameraAspect(const float& Aspect)
	{
		m_shadowmapcameraaspect = Aspect;
	}

	//�A�X�y�N�g��̎擾�B
	const float& GetShadowMapCameraAspect() const
	{
		return m_shadowmapcameraaspect;
	}
private:
	D3DXMATRIX		m_shadowmapcameraviewMatrix;		//�V���h�E�J�����̃r���[�s�� �J�����s��Ƃ������B
	D3DXMATRIX		m_shadowmapcameraprojectionMatrix;	//�V���h�E�J�����̃v���W�F�N�V�����s�� �r���[��Ԃ���ˉe��Ԃɕϊ�����s��B
	D3DXVECTOR3		m_shadowmapcameraeyePt;				//�V���h�E�J�����̍��W�B
	D3DXVECTOR3		m_shadowmapcameralookatPt;			//�V���h�E�J�����̒����_�B
	D3DXVECTOR3		m_shadowmapcameraupvec;				//�V���h�E�J�����̏�����B
	float			m_shadowmapcamerafar;				//�V���h�E�J�����̉�����(�t�@�[)�B
	float			m_shadowmapcameranear;				//�V���h�E�J�����̋ߕ���(�j�A�[)�B
	float			m_shadowmapcameraaspect;			//�V���h�E�J�����̃A�X�y�N�g��B
	D3DXVECTOR3		m_toEyeptVector;					//�����_����J�����̍��W�Ɍ������x�N�g���B
	UnityChan*      m_unitychan;						//�v���C���[�̃C���X�^���X�B
};