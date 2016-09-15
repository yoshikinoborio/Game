#pragma once
#include "AnimationModel3D.h"

class Camera;

class UnityChan : AnimationModel3D
{
public:
	UnityChan();
	~UnityChan();
	//������
	void Initialize()override;
	//�X�V
	void Update()override;
	//�`��
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight);
	//���
	void Release();
	//�p�b�h�ɂ��J�����̉��Ɉړ����鏈��
	void PadMove();
	D3DXVECTOR3 GetUnityChanPos()
	{
		return m_position;
	}
private:
	enum AnimationNo {
		AnimationInvalid = -1,
		AnimationStand,		//����
		AnimationWalk,		//����
		AnimationRun,		//����
		AnimationJump,		//�W�����v
	};
	D3DXVECTOR3		m_position;			//���W
	D3DXVECTOR3     m_scale;			//�X�P�[��
	D3DXMATRIX		m_world;			//���[���h�s��
	Camera*         m_camera;			//�J�����̃C���X�^���X
	AnimationNo		m_currentAnimSetNo;
	D3DXQUATERNION  m_rotation;			//��]�s��
	int				m_animationcount;
};
