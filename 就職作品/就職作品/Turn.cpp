#include "stdafx.h"
#include "Turn.h"

Turn::Turn()
{

}

Turn::~Turn()
{

}

void Turn::Initialize()
{
	m_currentAngleY = 0.0f;
	m_targetAngleY = 0.0f;
	m_turnSpeed = 0.0f;

}

//��]����
float Turn::Update(bool isTurn, float m_targetAngleY)
{

	if (isTurn) {
		float angleDiff = m_targetAngleY - m_currentAngleY;	//�ړI�p�x�܂łǂꂾ���񂹂������̂����v�Z����B
		float angleDiffAbs = fabsf(angleDiff);				//�񂷊p�x�̐�Βl���v�Z�B
		if (angleDiffAbs > 0.0001f) {						//�񂷊p�x�̑傫�������ɏ������ꍇ�͉񂳂Ȃ��B
			float turnDir = angleDiff / angleDiffAbs;		//��]������������v�Z����B
			if (angleDiffAbs > fPI) {						//��]������p�x��180�x���z���Ă��邩�𔻒肷��B
				//180�x���z�����]�̂��߉����B
				m_currentAngleY += 2.0f * fPI *  turnDir;	//���݂̊p�x��-90�x�Ȃ�270�x�A180�x�Ȃ�-180�x�ɂ���B
				turnDir *= -1.0f;							//�񂷕����𔽓]�B
			}
			m_turnSpeed = g_cTurnSpeed * turnDir;
		}
	}
	m_currentAngleY += m_turnSpeed;
	if (fabsf(m_targetAngleY - m_currentAngleY) < fabsf(m_turnSpeed) + 0.01f) {
		//�^�[���I���B
		m_turnSpeed = 0.0f;
		m_currentAngleY = m_targetAngleY;
	}
	return m_currentAngleY;
}