#pragma once
#include "AnimationModel3D.h"
#include "CharacterController.h"
#define WALKSPEED 0.02f	//�����X�s�[�h�B
#define RUNSPEED 0.2f*60.0f	//����X�s�[�h�B
#define MAX_RUN 0.6f*60.0f	//�����܂ł̏���l�B

class Camera;

class UnityChan : public AnimationModel3D
{
public:
	UnityChan();
	~UnityChan();
	//�������B
	void Initialize();
	//�X�V�B
	void Update()override;
	//�`��B
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight,
		bool isShadowReceiver);
	//����B
	void Release();
	//�p�b�h�ɂ��J�����̉��Ɉړ����鏈���B
	void PadMove();
	D3DXVECTOR3 GetUnityChanPos()
	{
		return m_position;
	}
	D3DXMATRIX GetUnityChanWorld()
	{
		return m_world;
	}
	D3DXVECTOR3 GetUnityiChanScale()
	{
		return m_scale;
	}
	D3DXQUATERNION GetUnityiChanRotation()
	{
		return m_rotation;
	}
	//�v���C���[�ōĐ������A�j���[�V�����̎�ށB
	enum PlayerAnimationNo {
		AnimationInvalid = -1,
		AnimationWait_00,	//�ҋ@(����)�B
		AnimationWalk,		//�����B
		AnimationRun,		//����B
		AnimationWait_01,	//�ҋ@(�r�L�΂�)�B
		AnimationWait_02,	//�ҋ@(�N���N��)�B
		AnimationSLID,		//�X���C�f�B���O�B
		AnimationBackStep,	//�o�b�N�X�e�b�v�B
	};
	//�v���C���[�̏�ԑJ�ڂ̎�ށB
	enum PlayerState{
		StateWait_00 = 0,	//�ҋ@(����)�B
		StateWait_01,		//�ҋ@(�r�L�΂�)�B
		StateWait_02,		//�ҋ@(�N���N��)�B
		StateWalk,          //�����B
		StateRun,			//����B
		StateSLID,			//�X���C�f�B���O�B
		StateBackStep,		//�o�b�N�X�e�b�v�B
	};

private:
	D3DXVECTOR3		m_position;					//���W�B
	D3DXVECTOR3     m_scale;					//�X�P�[���B
	D3DXMATRIX		m_world;					//���[���h�s��B
	Camera*         m_camera;					//�J�����̃C���X�^���X�B
	PlayerAnimationNo	m_currentAnimSetNo;		//���ݍĐ����Ă���A�j���[�V�����B
	PlayerState     m_state;					//�v���C���[�̏�ԁB
	D3DXQUATERNION  m_rotation;					//��]�s��B
	D3DXVECTOR3     m_moveDir;					//�J�������狁�߂������B
	float           m_moveSpeed;				//�ړ����x(�������Ƒ��鎞�̑��x�����p)�B
	float           m_waitAnimetionChangeTime;	//�ҋ@�A�j���[�V�����̐؂�ւ����ԁB
	float			m_currentAngleY;			//���݂̕����B
	float			m_targetAngleY;				//�������������B
	bool			m_isTurn;					//��]�t���O�B
	float           m_saveLStickX;				//���X�e�B�b�N�̍��E�̓��͗ʂ��i�[�B
	float			m_saveLStickY;				//���X�e�B�b�N�̑O��̓��͗ʂ��i�[�B
	CharacterController m_characterController;	//�L�����N�^�R���g���[���B
	float			m_height;					//���j�e�B�����̍����B
	float			m_radius;					//���j�e�B�����̔��a�B
	D3DXVECTOR3		m_moveDirSpeed;				//�ړ��ʁB
};
