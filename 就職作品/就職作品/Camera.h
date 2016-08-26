#pragma once

class Player;

//�J�����N���X
class Camera
{
public:
	//�R���X�g���N�^
	Camera();

	//�f�X�g���N�^
	~Camera();

	//������
	void Initialize();

	//�X�V
	void Update();

	//�r���[�s��̐ݒ�
	void SetViewMatrix(D3DXMATRIX View)
	{
		m_viewMatrix = View;
	}

	//�r���[�s��̎擾
	D3DXMATRIX GetViewMatrix()
	{
		return m_viewMatrix;
	}

	//�v���W�F�N�V�����s��̐ݒ�
	void SetProjectionMatrix(D3DXMATRIX Proj)
	{
		m_projectionMatrix = Proj;
	}

	//�v���W�F�N�V�����s��̎擾
	D3DXMATRIX GetProjectionMatrix()
	{
		return m_projectionMatrix;
	}

	//�J�����̍��W�̐ݒ�
	void SetEyePt(D3DXVECTOR3 Eye)
	{
		m_eyePt = Eye;
	}
	
	//�J�����̍��W�̎擾
	D3DXVECTOR3 GetEyePt()
	{
		return m_eyePt;
	}

	//�J�����̒����_�̐ݒ�
	void SetLookatPt(D3DXVECTOR3 Lookat)
	{
		m_lookatPt = Lookat;
	}
	
	//�J�����̒����_�̎擾
	D3DXVECTOR3 GetLookatPt()
	{
		return m_lookatPt;
	}

	//�J�����̏�����̐ݒ�
	void SetUpVec(D3DXVECTOR3 Up)
	{
		m_upVec = Up;
	}
	
	//�J�����̏�����̎擾
	D3DXVECTOR3 GetUpVec()
	{
		return m_upVec;
	}

	//�t�@�[�̐ݒ�
	void SetFar(float Far)
	{
		m_far = Far;
	}

	//�t�@�[�̎擾
	float GetFar()
	{
		return m_far;
	}

	//��A�[�̐ݒ�
	void SetNear(float Near)
	{
		m_near = Near;
	}

	//��A�[�̎擾
	float GetNear()
	{
		return m_near;
	}

	//�A�X�y�N�g��̐ݒ�
	void SetAspect(float Aspect)
	{
		m_aspect = Aspect;
	}

	//�A�X�y�N�g��̎擾
	float GetAspect()
	{
		return m_aspect;
	}
private:
	D3DXMATRIX		m_viewMatrix;			//�r���[�s�� �J�����s��Ƃ�����
	D3DXMATRIX		m_projectionMatrix;		//�v���W�F�N�V�����s�� �r���[��Ԃ���ˉe��Ԃɕϊ�����s��
	D3DXVECTOR3		m_eyePt;				//�J�����̍��W
	D3DXVECTOR3		m_lookatPt;				//�J�����̒����_
	D3DXVECTOR3		m_upVec;				//�J�����̏����
	float			m_far;					//������(�t�@�[)
	float			m_near;					//�ߕ���(�j�A�[)
	float			m_aspect;				//�A�X�y�N�g��
	D3DXVECTOR3		m_toEyeptVector;		//�����_����J�����̍��W�Ɍ������x�N�g��
	Player*			m_player;				//�v���C���[�C���X�^���X
	float			m_angle;				//��]
	D3DXQUATERNION	m_yAxis;				//Y����]�̃N�H�[�^�j�I��
	D3DXMATRIX		m_rot;					//�N�H�[�^�j�I������������]�s����i�[
	D3DXVECTOR4		m_v4;					//��]�s����g����m_toEyeptVector����]�������̂��i�[
	float			m_rStick_x;				//�E�X�e�B�b�N��X���̓��͗ʂ��i�[
	float           m_rStick_y;				//�E�X�e�B�b�N��Y���̓��͗ʂ��i�[
};