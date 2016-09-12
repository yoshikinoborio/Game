#pragma once
#include <d3d9.h>
#include <d3dx9effect.h>
#pragma warning( disable : 4996 ) 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <cstdlib>

#include "GraphicsDevice.h"
#include <memory.h>
#include "Assert.h"

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