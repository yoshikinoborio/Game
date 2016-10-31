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
#include <memory.h>
#include "Assert.h"

#define fPI 3.14159265358979323846f

const float g_cTurnSpeed D3DXToRadian(10.0f);

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