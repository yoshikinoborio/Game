#pragma once
#include "PreCompile.h"
//�A�j���[�V�����N���X
class Animation
{
public:
	Animation() 
	{
		m_pAnimController = nullptr;
		m_numAnimSet = 0;
		m_isBlending = false;
		m_isInterpolate = false;
		m_numMaxTracks = 0;
		m_interpolateTime = 0.0f;
		m_interpolateEndTime = 0.0f;
	};
	~Animation();
	void Initialize(ID3DXAnimationController* anim);
	void Update(float deltaTime);

	// �A�j���[�V�����Đ��֐�
	// ������: int�^ �Đ��������A�j���[�V�����̃C���f�b�N�X
	void PlayAnimation(int animationSetIndex);

	// �A�j���[�V�����Đ��֐�
	// ������: int�^ �Đ��������A�j���[�V�����̃C���f�b�N�X
	//		�@ float�^ �⊮����
	void PlayAnimation(int animationSetIndex, float interpolateTime);

	// �A�j���[�V�����Đ����x��ݒ�
	void SetAnimSpeed(float speed);

	//�A�j���[�V�����̏I���^�C����ݒ肷��֐�
	//������:int�^ �A�j���[�V�����C���f�b�N�X
	//      :double�^ �A�j���[�V�����̏I���^�C��
	//��-1.0���w�肷��ƃf�t�H���g�̏I�����Ԃ��ݒ肳��܂�
	void SetAnimationEndtime(int animationIndex, double endTime){
		m_animationEndTime[animationIndex] = endTime;
	}
#if 0
	// �A�j���[�V�����̃u�����f�B���O�Đ�
	// ������: int�^ �Đ��������A�j���[�V�����̃C���f�b�N�X
	void BlendAnimation(int animationSetIndex);
#endif
	int GetNumAnimationSet() const{
		return m_numAnimSet;
	}
private:
	ID3DXAnimationController*				m_pAnimController;		//�A�j���[�V�����R���g���[���B
	int										m_numAnimSet;			//�A�j���[�V�����Z�b�g�̐��B
	std::unique_ptr<ID3DXAnimationSet*[]>	m_animationSets;		//�A�j���[�V�����Z�b�g�̔z��B
	//�X�}�[�g�|�C���^�[(�|�C���^�œn���ꂽ�N���X�̃f�X�g���N�^��L���͈͂����ƌĂяo��)
	std::unique_ptr<float[]>				m_blendRateTable;		//�u�����f�B���O���[�g�̃e�[�u���B
	std::unique_ptr<double[]>				m_animationEndTime;		//�A�j���[�V�����̏I���^�C���B�f�t�H���g��-1.0�������Ă��āA-1.0�������Ă���ꍇ��ID3DXAnimationSet�̃A�j���[�V�����I���^�C�����D�悳���B
	int										m_oldAnimationSetNo;	// 1�t���[���O�̃A�j���[�V�����Z�b�g�̔ԍ�
	double									m_localAnimationTime;	//���[�J���A�j���[�V�����^�C���B
	int										m_currentAnimationSetNo;//���ݍĐ����̃A�j���[�V�����g���b�N�̔ԍ��B
	int										m_currentTrackNo;		//���݂̃g���b�N�̔ԍ��B
	int										m_numMaxTracks;			//�A�j���[�V�����g���b�N�̍ő吔�B
	bool									m_isBlending;			//�A�j���[�V�����u�����f�B���O�����ǂ����̃t���O
	bool									m_isInterpolate;		//��Ԓ����̃t���O
	float									m_interpolateEndTime;	//��ԏI�����ԁB
	float									m_interpolateTime;		//��Ԏ��ԁB
};