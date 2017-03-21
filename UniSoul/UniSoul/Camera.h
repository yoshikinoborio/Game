#pragma once
#include "CharacterController.h"
class UnityChan;

//�J�����N���X
class Camera
{
public:
	enum class GameObject
	{
		Skeleton = 0,
		Goblin,
		House_A,
		House_B,
		House_C,
		House_D,
		Yashi,
		ObjectNum,
	};
	//�R���X�g���N�^
	Camera();

	//�f�X�g���N�^
	~Camera();

	//������
	void Initialize();

	//�X�V
	void Update();

	//�p�b�h���g�����J�����̉�]�̏����B
	void PadUseRotation();

	//�t���[�J�������[�h�̏����B
	void FreeCameraMode();

	//�t���[�J�������[�h�t���O�̑��쏈���B
	void FreeCameraFlagChanger();

	//�Q�[���̒�~�B
	void GameStop();

	//�J�����̃r���[�s��ƃp�[�X�y�N�e�B�u�ˉe�s��̍쐬�B
	void CameraMatrixUpadate();

	//�J�������v���C���[��ǂ������鏈���B
	void TargetPlayer();

	//�Q�[���̏I���B
	void GameEnd();


	//�r���[�s��̐ݒ�
	void SetViewMatrix(const D3DXMATRIX& View)
	{
		m_viewMatrix = View;
	}

	//�r���[�s��̎擾
	const D3DXMATRIX& GetViewMatrix() const
	{
		return m_viewMatrix;
	}

	//�r���[�s��̋t�s����擾�B
	const D3DXMATRIX& GetViewMatrixInv() const
	{
		return m_viewMatrixInv;
	}

	//�v���W�F�N�V�����s��̐ݒ�
	void SetProjectionMatrix(const D3DXMATRIX& Proj)
	{
		m_projectionMatrix = Proj;
	}

	//�v���W�F�N�V�����s��̎擾
	const D3DXMATRIX& GetProjectionMatrix() const
	{
		return m_projectionMatrix;
	}

	//�J�����̍��W�̐ݒ�
	void SetEyePt(const D3DXVECTOR3& Eye)
	{
		m_eyePt = Eye;
	}
	
	//�J�����̍��W�̎擾
	const D3DXVECTOR3& GetEyePt() const
	{
		return m_eyePt;
	}

	//�J�����̒����_�̐ݒ�
	void SetLookatPt(const D3DXVECTOR3& Lookat)
	{
		m_lookatPt = Lookat;
	}
	
	//�J�����̒����_�̎擾
	const D3DXVECTOR3& GetLookatPt() const
	{
		return m_lookatPt;
	}

	//�J�����̏�����̐ݒ�
	void SetUpVec(const D3DXVECTOR3& Up)
	{
		m_upVec = Up;
	}
	
	//�J�����̏�����̎擾
	const D3DXVECTOR3& GetUpVec() const
	{
		return m_upVec;
	}

	//�t�@�[�̐ݒ�
	void SetFar(float Far)
	{
		m_far = Far;
	}

	//�t�@�[�̎擾
	float GetFar() const
	{
		return m_far;
	}

	//��A�[�̐ݒ�
	void SetNear(float Near)
	{
		m_near = Near;
	}

	//��A�[�̎擾
	float GetNear() const
	{
		return m_near;
	}

	//�A�X�y�N�g��̐ݒ�
	void SetAspect(float Aspect)
	{
		m_aspect = Aspect;
	}

	//�A�X�y�N�g��̎擾
	float GetAspect() const
	{
		return m_aspect;
	}
	//�J�����̂����R���Œ肩�̃t���O���擾�B
	bool GetCameraFreeFlag() const
	{
		return m_cameraFreeFlag;
	}

	int GetNowObject() const
	{
		return m_nowGameObject;
	}
private:
	D3DXMATRIX		m_viewMatrix;			//�r���[�s�� �J�����s��Ƃ������B
	D3DXMATRIX		m_projectionMatrix;		//�v���W�F�N�V�����s�� �r���[��Ԃ���ˉe��Ԃɕϊ�����s��E
	D3DXMATRIX		m_viewMatrixInv;		//�r���[�s��̋t�s��B
	D3DXVECTOR3		m_eyePt;				//�J�����̍��W�B
	D3DXVECTOR3		m_lookatPt;				//�J�����̒����_�B
	D3DXVECTOR3		m_upVec;				//�J�����̏�����B
	float			m_far;					//������(�t�@�[)�B
	float			m_near;					//�ߕ���(�j�A�[)�B
	float			m_aspect;				//�A�X�y�N�g��B
	D3DXVECTOR3		m_toEyeptVector;		//�����_����J�����̍��W�Ɍ������x�N�g���B
	UnityChan*      m_unitychan;			//�v���C���[�̃C���X�^���X�B
	float			m_angle;				//��]�B
	D3DXQUATERNION	m_yAxis;				//Y����]�̃N�H�[�^�j�I���B
	D3DXQUATERNION	m_zAxis;				//Z����]�̃N�H�[�^�j�I���B
	D3DXMATRIX		m_rot;					//�N�H�[�^�j�I������������]�s����i�[�B
	D3DXVECTOR4		m_v4;					//��]�s����g����m_toEyeptVector����]�������̂��i�[�B
	float			m_rStick_x;				//�E�X�e�B�b�N��X���̓��͗ʂ��i�[�B
	float           m_rStick_y;				//�E�X�e�B�b�N��Y���̓��͗ʂ��i�[�B
	bool			m_cameraFreeFlag;		//���R�ȃJ�����ɐ؂�ւ���t���O�B
	D3DXVECTOR3     m_moveDir;				//�J�����̌����B
	int				m_nowGameObject;		//�I������Ă���Q�[���I�u�W�F�N�g�B
	DWORD			m_nowTime;				//���݂̎��Ԃ��i�[�B
	DWORD			m_selectMoveTime;		//�I�u�W�F�N�g��I�����Ă���o�߂������ԁB
};