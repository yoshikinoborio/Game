#pragma once

//����p�쐬�N���X�B
class CreateViewAngle
{
public:
	//�R���X�g���N�^�B
	CreateViewAngle();

	//�f�X�g���N�^�B
	~CreateViewAngle();

	//����p�쐬�B
	//�������̓v���C���[�Ɍ������x�N�g���B
	//�������͎����̌����x�N�g���B
	//�߂�l�͍쐬��������p�B
	float CreateView(const D3DXVECTOR3& TargetDir, const D3DXMATRIX& MyDir);
};

