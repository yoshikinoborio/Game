#include "stdafx.h"
#include "CreateViewAngle.h"

//�R���X�g���N�^�B
CreateViewAngle::CreateViewAngle()
{
}

//�f�X�g���N�^�B
CreateViewAngle::~CreateViewAngle()
{

}

float CreateViewAngle::CreateView(const D3DXVECTOR3& TargetDir, const D3DXMATRIX& MyDir)
{
	//�����̌����x�N�g���B
	D3DXVECTOR3 Dir = D3DXVECTOR3(MyDir.m[3][0],MyDir.m[3][1],MyDir.m[3][2]);

	//�v���C���[�ւ̌����x�N�g���B
	D3DXVECTOR3 PlayerDir = TargetDir;

	//��̃x�N�g���𐳋K���B
	D3DXVec3Normalize(&Dir, &Dir);
	D3DXVec3Normalize(&PlayerDir, &PlayerDir);

	//���K��������̃x�N�g���̓��ς��v�Z�B
	float dot = D3DXVec3Dot(&Dir, &PlayerDir);
	//���ς̒l�̋t�]�����烉�W�A�������߂�B
	float rad = acos(dot);
	//���W�A������p�x�ɕϊ������ۂ̊p�x�������߂�B
	float selfangle D3DXToDegree(rad);

	//�쐬��������p��Ԃ��B
	return selfangle;
}
