#include "stdafx.h"
#include "GraphicsDevice.h"

LPDIRECT3D9             g_pD3D = NULL;
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL;

extern void Init();
extern void Render();
extern void Update();
extern void Terminate();
//-----------------------------------------------------------------------------
// DirectXを初期化。
//-----------------------------------------------------------------------------
void InitD3D(HWND hWnd)
{
	//D3Dオブジェクトを作成する(コンポーネントの取得、絶対にいる。無いと何もできない)。
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	// D3Dデバイスを作成するためのパラメータを設定する。
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));			//構造体全体の初期化
	d3dpp.Windowed = TRUE;						//TRUEの場合はウィンドウモード、FALSEはフルスクリーンモード
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//フロントバッファとバックバッファの切り替え方法を定義する部分
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//D3DFMT_UNKNOWNにすると動作環境に合わせてフォーマットを変えてくれる。
	d3dpp.EnableAutoDepthStencil = TRUE;		//深度ステンシルバッファ(Zバッファなどの3D空間におけるオブジェクトの奥行きを保持するバッファ+ステンシルバッファという画面にマスクをかけて描画領域を制限する(重なって描画されている所を透過させたり描画しないようにする)バッファ)、3Dを扱うならTRUE
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//ステンシルバッファのフォーマットを指定(ステンシルバッファを使うならTRUE、使わないならFALSE、D3DFMT_D16はエラーを起こしにくい)

	//D3Dデバイスを作成する。
	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,	//D3DADAPTER_DEFAULT以外を指定する事はまず無い
		D3DDEVTYPE_HAL,							//D3DDEVTYPE_HALを指定すると、ハードウェアを最大限に使用したパフォーマンスを得る事が出来る、D3DDEVTYPE_REFを指定すると、描画等の処理をソフトウェアで行う
		hWnd,									//描画を行うウィンドウハンドルを指定
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,	//D3DCREATE_HARDWARE_VERTEXPROCESSING(ハードウェアによる頂点処理)、D3DCREATE_MIXED_VERTEXPROCESSING(ソフトウェアおよびハードウェアによる) ミックスの頂点処理)、D3DCREATE_SOFTWARE_VERTEXPROCESSING(ソフトウェアによる頂点処理)ソフトウェアに設定しておくとハードウェアでエラーの時ソフトウェアで計算をしてくれる
		&d3dpp,									//D3DPRESENT_PARAMETERS構造体へのポインタを指定
		&g_pd3dDevice);							//IDirect3DDevice9コンポーネントへのポインタを指定し、関数が成功するとここにコンポーネントへのポインタが格納される

}
//-----------------------------------------------------------------------------
// メッセージプロシージャ。
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
// ウィンメイン。
//-----------------------------------------------------------------------------
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);

	// ウィンドウクラスを登録。
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),		//構造体のサイズ
		CS_CLASSDC,				//ウインドウスタイル
		MsgProc,				//ウインドウのメッセージを処理するコールバック関数へのポインタ
		0L,						//ウインドウクラス構造体の後ろに割り当てる補足バイト数
		0L,						//ウインドウインスタンスの後ろに割り当てる補足バイト数
		GetModuleHandle(NULL),	//このクラスのためのウインドウプロシージャがあるインスタンスハンドル
		NULL,					//アイコンのハンドル
		NULL,					//マウスカーソルのハンドル
		NULL,					//ウインドウ背景色(背景描画用ブラシのハンドル)
		NULL,					//デフォルトメニュー名
		"就職作品",				//ウインドウクラスにつける名前
		NULL					//16×16の小さいサイズのアイコン(タスクバーに表示されるアイコン)
	};
	//作成したウィンドウクラスの登録
	RegisterClassEx(&wc);

	// ウィンドウを作成。
	HWND hWnd = CreateWindow("就職作品",			//RegisterClassEx()で登録したクラスの名前
		"就職作品",									//タイトルバーとかに表示する文字列
		WS_OVERLAPPEDWINDOW,						//ウインドウスタイル(dwStyle)
		0,											//ウインドウ左上x座標(画面左上が0)．適当でいい時はCW_USEDEFAULT
		0,											//ウインドウ左上y座標(画面左上が0)．適当でいい時はCW_USEDEFAULT
		1920,										//ウインドウ幅．適当でいい時はCW_USEDEFAULT
		1080,										//ウインドウ高さ．適当でいい時はCW_USEDEFAULT
		NULL,										//親ウインドウのハンドル．なければNULL．dwStyleでDW_CHILDを指定したときは必須．
		NULL,										//メニューのハンドル．デフォルト(WNDCLASS.lpszMenuName)を使う場合はNULL
		wc.hInstance,								//WM_CREATEでLPARAMに渡したい値．だいたいNULL
		NULL);										//作成されたウインドウのハンドル．失敗したらNULL

	// Direct3Dを初期化。
	InitD3D(hWnd);


	// Show the window
	//ウインドウの表示状態の設定
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	//ここからゲーム関係の初期化。
	Init();

	// ゲームループ
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
	//ウインドウクラス解放(RegisterClass(Ex)で登録したクラスを解放する関数 このクラスを使ったウインドウを全て閉じてから使うこと)
	//クラス名,クラスを作成したモジュールのインスタンスハンドル
	UnregisterClass("就職作品", wc.hInstance);
	return 0;
}
