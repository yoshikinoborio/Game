#pragma once

//�Q�[���V�[���̃��j���[��ʂ̏����B
class GameMenu
{
public:

	//�R���X�g���N�^�B
	GameMenu();

	//�f�X�g���N�^�B
	~GameMenu();

	//�������B
	void Initialize();

	//�X�V�B
	void Update();

	//�`��B
	void Draw();
private:
	D3DVIEWPORT9 m_viewPort;	//�r���[�|�[�g�B
};