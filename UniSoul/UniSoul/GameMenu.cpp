#include "stdafx.h"
#include "GameMenu.h"
#include "SceneManager.h"


//�R���X�g���N�^�B
GameMenu::GameMenu()
{
	//�r���[�|�[�g�̊e�ݒ�̏������B
	m_viewPort.X = 0;
	m_viewPort.Y = 0;
	m_viewPort.Width = 0;
	m_viewPort.Height = 0;
	m_viewPort.MinZ = 0.0f;
	m_viewPort.MaxZ = 1.0f;
}

//�f�X�g���N�^�B
GameMenu::~GameMenu()
{

}

//�������B
void GameMenu::Initialize()
{
	//�r���[�|�[�g�̊e�ݒ�̍Đݒ�B
	m_viewPort.X = 100;			//�������x���W
	m_viewPort.Y = 100;			//�������y���W
	m_viewPort.Width = 500;		//����
	m_viewPort.Height = 500;	//�c��
	m_viewPort.MinZ = 0.0f;		//�[�x�l�̍ŏ��l�@�ʏ��0.0f
	m_viewPort.MaxZ = 1.0f;		//�[�x�l�̍ő�l  �ʏ��1.0f
}

//�X�V�B
void GameMenu::Update()
{
	if (g_pad.IsTrigger(enButtonStart))
	{

	}
}

//�`��B
void GameMenu::Draw()
{
#ifdef _DEBUG
	//�`��̈��ύX�i�r���[�|�[�g�s��j�B
	g_pd3dDevice->SetViewport(&m_viewPort);

	//�`��̈�ɂ�������C�ӂ̐F�ŃN���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	//�v���C���[�̕`��B
	g_pScenes->GetUnityChan()->Draw(static_cast<GameScene*>(g_pScenes)->GetCamera()->GetViewMatrix(),
		static_cast<GameScene*>(g_pScenes)->GetCamera()->GetProjectionMatrix(),
		FALSE);

#endif // !_DEBUG
}