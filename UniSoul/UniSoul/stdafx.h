#pragma once
#include <d3d9.h>
#include <d3dx9effect.h>
#pragma warning( disable : 4996 ) 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <cstdlib>
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"
#include "GraphicsDevice.h"
#include <memory>
#include <list>
#include "Assert.h"
#include "Util.h"
#include "NameKey.h"
#include "Noncopyable.h"
#include <X3DAudio.h>
#include <XAudio2.h>
#include <XAudio2fx.h>
#include <string>

#define fPI 3.14159265358979323846f


/*!
*@brief	仮想ボタン定義。
*/
enum EnButton{
	enButtonUp,			//!<上。
	enButtonDown,		//!<下。
	enButtonLeft,		//!<左。
	enButtonRight,		//!<右。
	enButtonA,			//!<Aボタン。
	enButtonB,			//!<Bボタン。
	enButtonX,			//!<Xボタン。
	enButtonY,			//!<Yボタン。
	enButtonSelect,		//!<セレクトボタン。
	enButtonStart,		//!<スタートボタン。
	enButtonRB1,		//!<RB1ボタン。
	enButtonRB2,		//!<RB2ボタン。
	enButtonRB3,		//!<RB3ボタン。
	enButtonLB1,		//!<LB1ボタン。
	enButtonLB2,		//!<LB2ボタン。
	enButtonLB3,		//!<LB3ボタン。
	enButtonNum,		//!<ボタンの数。
};


//ほとんどのゲッターをconst参照にしているのは、
//const参照にすると早くなる、
//なぜ早いかと言うとD3DXVECTOR3などの構造体を値渡しにするとfloat＊3要素のコピーが発生するが参照渡しにすると構造体のアドレス分(4バイトもしくは8バイト)のコピーで済むから。
//D3DXVECTORは参照の方が早い、
//SIMDという128ビットの変数があるアーキテクチャは値渡しの方が早い、
//ただ今はSIMDがあるアーキテクチャの方が多いから。

//手前に付いているconstの役割は戻値の情報を変えない参照と言うの明示的に教えている。
//後ろに付いているconstの役割は関数の中身でクラスの情報を変えないと言うのを明示的に教えている。変えないと宣言したのでconstオブジェクトの関数が呼べるようになる。

//値を変えてほしくない引数にconst参照を使っているのは渡された値が呼ばれた関数内で変更されるヒューマンエラーを起こさないようにするため。メンバ関数も同じ。

//namespaceを使う理由、
//namespaceを使うとstaticの時に発生する同名との衝突が起きなくなる。そう言う言語の使用。

//enumにclassを付けるとenum内で定義している名前同士の衝突が起きなくなるのでclassを付けいている。


//0.0fを書くのを繰り返すのがめんどうなのでグローバルで定義。
namespace {
	const float g_cTurnSpeed D3DXToRadian(10.0f);

	static const int FRAME_BUFFER_WITDH = 1920;			//フレームバッファのサイズ。
	static const int FRAME_BUFFER_HEIGHT = 1080;		//フレームバッファのサイズ。


	const D3DXVECTOR3 Vector3Zero = { 0.0f,0.0f,0.0f };
	const D3DXVECTOR3 Vector3One = { 1.0f,1.0f ,1.0f };
	const D3DXVECTOR3 Vector3Up = { 0.0f, 1.0f ,0.0f };
	const D3DXVECTOR3 Vector3Right = { 1.0f,0.0f,0.0f };
	const D3DXVECTOR3 Vector3Left = { -1.0f,0.0f,0.0f };
	const D3DXVECTOR3 Vector3Forward = { 0.0f,0.0f,1.0f };
	const D3DXVECTOR3 Vector3Back = { 0.0f,0.0f,-1.0f };
	const D3DXVECTOR2 Vector2Zero = { 0.0f,0.0f};
	const D3DXVECTOR2 Vector2One = { 1.0f,1.0f };
}