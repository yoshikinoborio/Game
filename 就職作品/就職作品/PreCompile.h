#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define USE_VSM		//��`��VSM���L���B

#define USE_ORTHO_PROJECTION

/*!
* @brief	��`��DirectX9�œ���
*/
#define TK_PLATFORM_DX9

#if defined( TK_PLATFORM_DX9 )
#include <windows.h>
#endif // #if defined( TK_PLATFORM_DX9 )
#include <memory>
#include <d3dx9.h>
#include <d3d9.h>
#pragma comment(lib,"Xinput.lib")
#ifdef _DEBUG
#include <DxErr.h>
#pragma comment(lib, "dxerr.lib")

#endif
#include <list>
#include <vector>
#include <map>
#include <algorithm>

