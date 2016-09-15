#include "stdafx.h"
#include "GraphicsDevice.h"

LPDIRECT3D9             g_pD3D = NULL;
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;

extern void Init();
extern void Render();
extern void Update();
extern void Terminate();
//-----------------------------------------------------------------------------
// DirectX���������B
//-----------------------------------------------------------------------------
void InitD3D(HWND hWnd)
{
	//D3D�I�u�W�F�N�g���쐬����(�R���|�[�l���g�̎擾�A��΂ɂ���B�����Ɖ����ł��Ȃ�)�B
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	// D3D�f�o�C�X���쐬���邽�߂̃p�����[�^��ݒ肷��B
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));			//�\���̑S�̂̏�����
	d3dpp.Windowed = TRUE;						//TRUE�̏ꍇ�̓E�B���h�E���[�h�AFALSE�̓t���X�N���[�����[�h
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@�̐؂�ւ����@���`���镔��
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//D3DFMT_UNKNOWN�ɂ���Ɠ�����ɍ��킹�ăt�H�[�}�b�g��ς��Ă����B
	d3dpp.EnableAutoDepthStencil = TRUE;		//�[�x�X�e���V���o�b�t�@(Z�o�b�t�@�Ȃǂ�3D��Ԃɂ�����I�u�W�F�N�g�̉��s����ێ�����o�b�t�@+�X�e���V���o�b�t�@�Ƃ�����ʂɃ}�X�N�������ĕ`��̈�𐧌�����(�d�Ȃ��ĕ`�悳��Ă��鏊�𓧉߂�������`�悵�Ȃ��悤�ɂ���)�o�b�t�@)�A3D�������Ȃ�TRUE
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//�X�e���V���o�b�t�@�̃t�H�[�}�b�g���w��(�X�e���V���o�b�t�@���g���Ȃ�TRUE�A�g��Ȃ��Ȃ�FALSE�AD3DFMT_D16�̓G���[���N�����ɂ���)

	//D3D�f�o�C�X���쐬����B
	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,	//D3DADAPTER_DEFAULT�ȊO���w�肷�鎖�͂܂�����
		D3DDEVTYPE_HAL,							//D3DDEVTYPE_HAL���w�肷��ƁA�n�[�h�E�F�A���ő���Ɏg�p�����p�t�H�[�}���X�𓾂鎖���o����AD3DDEVTYPE_REF���w�肷��ƁA�`�擙�̏������\�t�g�E�F�A�ōs��
		hWnd,									//�`����s���E�B���h�E�n���h�����w��
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,	//D3DCREATE_HARDWARE_VERTEXPROCESSING(�n�[�h�E�F�A�ɂ�钸�_����)�AD3DCREATE_MIXED_VERTEXPROCESSING(�\�t�g�E�F�A����уn�[�h�E�F�A�ɂ��) �~�b�N�X�̒��_����)�AD3DCREATE_SOFTWARE_VERTEXPROCESSING(�\�t�g�E�F�A�ɂ�钸�_����)�\�t�g�E�F�A�ɐݒ肵�Ă����ƃn�[�h�E�F�A�ŃG���[�̎��\�t�g�E�F�A�Ōv�Z�����Ă����
		&d3dpp,									//D3DPRESENT_PARAMETERS�\���̂ւ̃|�C���^���w��
		&g_pd3dDevice);							//IDirect3DDevice9�R���|�[�l���g�ւ̃|�C���^���w�肵�A�֐�����������Ƃ����ɃR���|�[�l���g�ւ̃|�C���^���i�[�����

}
//-----------------------------------------------------------------------------
// ���b�Z�[�W�v���V�[�W���B
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		if (g_pd3dDevice != NULL)
			g_pd3dDevice->Release();

		if (g_pD3D != NULL)
			g_pD3D->Release();
		Terminate();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//-----------------------------------------------------------------------------
// �E�B�����C���B
//-----------------------------------------------------------------------------
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);

	// �E�B���h�E�N���X��o�^�B
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),		//�\���̂̃T�C�Y
		CS_CLASSDC,				//�E�C���h�E�X�^�C��
		MsgProc,				//�E�C���h�E�̃��b�Z�[�W����������R�[���o�b�N�֐��ւ̃|�C���^
		0L,						//�E�C���h�E�N���X�\���̂̌��Ɋ��蓖�Ă�⑫�o�C�g��
		0L,						//�E�C���h�E�C���X�^���X�̌��Ɋ��蓖�Ă�⑫�o�C�g��
		GetModuleHandle(NULL),	//���̃N���X�̂��߂̃E�C���h�E�v���V�[�W��������C���X�^���X�n���h��
		NULL,					//�A�C�R���̃n���h��
		NULL,					//�}�E�X�J�[�\���̃n���h��
		NULL,					//�E�C���h�E�w�i�F(�w�i�`��p�u���V�̃n���h��)
		NULL,					//�f�t�H���g���j���[��
		"�A�E��i",				//�E�C���h�E�N���X�ɂ��閼�O
		NULL					//16�~16�̏������T�C�Y�̃A�C�R��(�^�X�N�o�[�ɕ\�������A�C�R��)
	};
	//�쐬�����E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wc);

	// �E�B���h�E���쐬�B
	HWND hWnd = CreateWindow("�A�E��i",			//RegisterClassEx()�œo�^�����N���X�̖��O
		"�A�E��i",									//�^�C�g���o�[�Ƃ��ɕ\�����镶����
		WS_OVERLAPPEDWINDOW,						//�E�C���h�E�X�^�C��(dwStyle)
		0,											//�E�C���h�E����x���W(��ʍ��オ0)�D�K���ł�������CW_USEDEFAULT
		0,											//�E�C���h�E����y���W(��ʍ��オ0)�D�K���ł�������CW_USEDEFAULT
		1920,										//�E�C���h�E���D�K���ł�������CW_USEDEFAULT
		1080,										//�E�C���h�E�����D�K���ł�������CW_USEDEFAULT
		NULL,										//�e�E�C���h�E�̃n���h���D�Ȃ����NULL�DdwStyle��DW_CHILD���w�肵���Ƃ��͕K�{�D
		NULL,										//���j���[�̃n���h���D�f�t�H���g(WNDCLASS.lpszMenuName)���g���ꍇ��NULL
		wc.hInstance,								//WM_CREATE��LPARAM�ɓn�������l�D��������NULL
		NULL);										//�쐬���ꂽ�E�C���h�E�̃n���h���D���s������NULL

	// Direct3D���������B
	InitD3D(hWnd);


	// Show the window
	//�E�C���h�E�̕\����Ԃ̐ݒ�
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	//��������Q�[���֌W�̏������B
	Init();

	// �Q�[�����[�v
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			Update();
			Render();
		}
	}
	//�E�C���h�E�N���X���(RegisterClass(Ex)�œo�^�����N���X���������֐� ���̃N���X���g�����E�C���h�E��S�ĕ��Ă���g������)
	//�N���X��,�N���X���쐬�������W���[���̃C���X�^���X�n���h��
	UnregisterClass("�A�E��i", wc.hInstance);
	return 0;
}
