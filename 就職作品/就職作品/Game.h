#pragma once
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "Light.h"
#include "Pad.h"
#include "EffectManager.h"
#include "UnityChan.h"

class Game
{
public:
	//�R���X�g���N�^
	Game();
	//�f�X�g���N�^
	~Game();
	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();
	//���
	void Terminate();
	//�v���C���[�̃C���X�^���X�̎擾
	Player* GetPlayer()
	{
		return &player;
	}
	//���j�e�B�����̃C���X�^���X�擾
	UnityChan* GetUnityChan()
	{
		return &unitychan;
	}
	//���C�g�̃C���X�^���X�̎擾
	Light* GetLight()
	{
		return &light;
	}
	//�J�����̃C���X�^���X�̎擾
	Camera* GetCamera()
	{
		return &camera;
	}
	//�X�e�[�W�̃C���X�^���X�̎擾
	Stage* GatStage()
	{
		return &stage;
	}
private:
	Player player;
	UnityChan unitychan;
	Camera camera;
	Stage stage;
	Light light;
};

extern Game* game;
extern Pad g_pad;				//�ǂ��ł��g����悤��extern
extern EffectManager* g_effectManager;