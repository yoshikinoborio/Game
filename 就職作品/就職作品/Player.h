#pragma once
#include "Model3D.h"
#include "SkinModel.h"
#include "SkinModelData.h"

class Camera;

//�v���C���[�N���X
class Player
{
public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();
	//������
	void Initialize(LPDIRECT3DDEVICE9 pd3dDevice);
	//�X�V
	void Update();
	//�`��
	void Draw(LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight);
	//���
	void Release();
	D3DXVECTOR3 GetPlayerPos()
	{
		return m_position;
	}
	//�p�b�h�ɂ��J�����̉��Ɉړ����鏈��
	void PadMove();
private:
	enum AnimationNo {
		AnimationInvalid = -1,
		AnimationStand,		//����
		AnimationWalk,		//����
		AnimationRun,		//����
		AnimationJump,		//�W�����v
	};
	Model3D			m_model3d;			//3D�֌W��\������Model3D�̃C���X�^���X��ێ�
	D3DXVECTOR3		m_position;			//���W
	D3DXVECTOR3     m_scale;			//�X�P�[��
	D3DXMATRIX		m_world;			//���[���h�s��
	//D3DXMATRIX		m_rotation;		//��]�s��
	Camera*         m_camera;			//�J�����̃C���X�^���X
	SkinModelData	m_skinModelData;	//�X�L�����f���f�[�^
	SkinModel		m_skinModel;		//�X�L�����f��
	Animation		m_animation;		//�A�j���[�V����
	AnimationNo		m_currentAnimSetNo;
	D3DXQUATERNION  m_rotation;			//��]�s��
};
