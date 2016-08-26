#pragma once
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "Light.h"
#include "Pad.h"

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
	void Terminate();
	Player* GetPlayer()
	{
		return &player;
	}
	Light* GetLight()
	{
		return &light;
	}
	Camera* GetCamera()
	{
		return &camera;
	}
	Stage* GatStage()
	{
		return &stage;
	}
private:
	Player player;
	Camera camera;
	Stage stage;
	Light light;
};

extern Game* game;
extern Pad g_pad;				//�ǂ��ł��g����悤��extern