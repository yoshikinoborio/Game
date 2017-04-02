#pragma once
#include "SkinModel.h"
#include "Turn.h"
#include "RigidBody.h"
#include "MeshCollider.h"
#include "DamageCollisionWorld.h"
#include "Light.h"
#include "CreateViewAngle.h"
#include "CharacterController.h"


//�A�j���[�V��������3D���f���̊��N���X�B
class AnimationModel3D
{
public:
	//�R���X�g���N�^�B
	AnimationModel3D();

	//�f�X�g���N�^��Virtua��t���闝�R��
	//�h���N���X�̃f�X�g���N�^���Ă΂ꂸ���������[�N���N���邩��t���Ă���B
	virtual~AnimationModel3D() 
	{
	}

	//�������z�֐��͂�����N���X���̃��\�b�h��h���N���X���ŕK������(��`)���Ă��炢�����ꍇ�A�������z�֐��Ő錾����B
	//�������z�֐��Ő錾���ꂽ�N���X���p������ꍇ�A�K���I�[�o�[���C�h���Ȃ���΂Ȃ�Ȃ��B
	//���N���X�̃����o���\�b�h���p���N���X�ŕύX���鎖���ł���B�ȒP�Ɍ����΁A�Ē�`����Ƃ������B
	//���̊��N���X�̊֐�(�I�[�o�[���C�h�����֐�)�����z�֐��ƌ����B
	virtual void Update() = 0;
protected:
	SkinModelData*			m_skinModelData;			//�X�L�����f���f�[�^�B
	SkinModel				m_skinModel;				//�X�L�����f���B
	Animation				m_animation;				//�A�j���[�V�����B
	Turn					m_turn;						//��]�����B
	MeshCollider			m_meshCollider;				//���b�V���R���C�_�[�B
	RigidBody				m_rigidBody;				//���́B
	Light					m_light;					//���C�g�B
	CreateViewAngle			m_CreateViewAngle;			//����p�쐬�N���X�B
	D3DXVECTOR3				m_position;					//���W�B
	D3DXVECTOR3				m_scale;					//�X�P�[���B
	D3DXMATRIX				m_world;					//���[���h�s��B
	D3DXQUATERNION			m_rotation;					//��]�s��B
	CharacterController		m_characterController;		//�L�����N�^�R���g���[���B
	float					m_moveSpeed;				//�ړ����x(�������Ƒ��鎞�̑��x�����p)�B
	bool					m_isTurn;					//��]�t���O�B
	float					m_height;					//�L�����N�^�[�̍����B
	float					m_radius;					//�L�����N�^�[�G�̔��a�B
	int						m_hp;						//�q�b�g�|�C���g�B
	int						m_maxhp;					//�ő�q�b�g�|�C���g�B
	float					m_currentAngleY;			//���݂̕����B
	float					m_targetAngleY;				//�������������B
	D3DXVECTOR3				m_move;						//�ړ��ʁB
	bool					m_isDead;					//���񂾁B
	float					m_frameDeltaTime = 1.0f / 60.0f;	//1�t���[���̌o�ߎ��ԁB
	float					m_deltaTimeMul = 1.0f;				//���^�C���ɏ�Z�����l�B
};