#pragma once
#include "AnimationModel3D.h"

class Camera;

class UnityChan : AnimationModel3D
{
public:
	UnityChan();
	~UnityChan();
	//�������B
	void Initialize()override;
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
private:
	enum AnimationNo {
		AnimationInvalid = -1,
		AnimationStand,		//�����B
		AnimationWalk,		//�����B
		AnimationRun,		//����B
		AnimationJump,		//�W�����v�B
	};
	D3DXVECTOR3		m_position;			//���W�B
	D3DXVECTOR3     m_scale;			//�X�P�[���B
	D3DXMATRIX		m_world;			//���[���h�s��B
	Camera*         m_camera;			//�J�����̃C���X�^���X�B
	AnimationNo		m_currentAnimSetNo;
	D3DXQUATERNION  m_rotation;			//��]�s��B
	int				m_animationcount;
};
