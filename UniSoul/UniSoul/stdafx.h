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

const float g_cTurnSpeed D3DXToRadian(10.0f);

/*!
*@brief	���z�{�^����`�B
*/
enum EnButton{
	enButtonUp,			//!<��B
	enButtonDown,		//!<���B
	enButtonLeft,		//!<���B
	enButtonRight,		//!<�E�B
	enButtonA,			//!<A�{�^���B
	enButtonB,			//!<B�{�^���B
	enButtonX,			//!<X�{�^���B
	enButtonY,			//!<Y�{�^���B
	enButtonSelect,		//!<�Z���N�g�{�^���B
	enButtonStart,		//!<�X�^�[�g�{�^���B
	enButtonRB1,		//!<RB1�{�^���B
	enButtonRB2,		//!<RB2�{�^���B
	enButtonRB3,		//!<RB3�{�^���B
	enButtonLB1,		//!<LB1�{�^���B
	enButtonLB2,		//!<LB2�{�^���B
	enButtonLB3,		//!<LB3�{�^���B
	enButtonNum,		//!<�{�^���̐��B
};