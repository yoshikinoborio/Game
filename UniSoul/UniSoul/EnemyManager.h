#pragma once
#include "Animation.h"
class EnemySkeleton;
class EnemyGoblin;
class EnemyBoss;

//�G�l�~�[�S���̏���������N���X�B
class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	void Initialize();
	void Update();
	void Draw(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isShadowReceiver);
	Animation m_animation;
	//��O�ɕt���Ă���const�̖����͒l��ς��Ȃ��Q�Ƃƌ����̖����I�ɋ����Ă���B
	//���ɕt���Ă���const�̖����͊֐��̒��g�Œl��ς��Ȃ��ƌ����̂𖾎��I�ɋ����Ă���B
	const std::vector<EnemySkeleton*>& GetEnemyList() const
	{
		return m_enemyskeletonList;
	}
	//const���ƒ��g��ς��������ɕς���Ȃ��̂ŕς��������p�̂��߂ɂ�����p�ӁB
	std::vector<EnemySkeleton*>& GetEnemyList()
	{
		return m_enemyskeletonList;
	}
	/*!
	* @brief	���^�C���ɏ�Z�����l��ݒ�B
	*@param[in]	mul		�O���[�o�����^�C���ɏ�Z�����l�B���̒l��0.5��ݒ肷��ƃG�l�~�[�̋�����0.5�{���ɂȂ�B
	*/
	void SetFrameDeltaTimeMul(float mul);
private:
	//���^�̓G�̉ϒ��z��B
	std::vector< EnemySkeleton*> m_enemyskeletonList;
	//�S�u�����^�̉ϒ��z��B
	std::vector< EnemyGoblin*>	m_enemyGoblinList;
	//�{�X�B
	EnemyBoss* m_enemyBoss;
};