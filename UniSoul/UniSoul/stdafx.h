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


//�قƂ�ǂ̃Q�b�^�[��const�Q�Ƃɂ��Ă���̂́A
//const�Q�Ƃɂ���Ƒ����Ȃ�A
//�Ȃ��������ƌ�����D3DXVECTOR3�Ȃǂ̍\���̂�l�n���ɂ����float��3�v�f�̃R�s�[���������邪�Q�Ɠn���ɂ���ƍ\���̂̃A�h���X��(4�o�C�g��������8�o�C�g)�̃R�s�[�ōςނ���B
//D3DXVECTOR�͎Q�Ƃ̕��������A
//SIMD�Ƃ���128�r�b�g�̕ϐ�������A�[�L�e�N�`���͒l�n���̕��������A
//��������SIMD������A�[�L�e�N�`���̕�����������B

//��O�ɕt���Ă���const�̖����͖ߒl�̏���ς��Ȃ��Q�Ƃƌ����̖����I�ɋ����Ă���B
//���ɕt���Ă���const�̖����͊֐��̒��g�ŃN���X�̏���ς��Ȃ��ƌ����̂𖾎��I�ɋ����Ă���B�ς��Ȃ��Ɛ錾�����̂�const�I�u�W�F�N�g�̊֐����Ăׂ�悤�ɂȂ�B

//�l��ς��Ăق����Ȃ�������const�Q�Ƃ��g���Ă���͓̂n���ꂽ�l���Ă΂ꂽ�֐����ŕύX�����q���[�}���G���[���N�����Ȃ��悤�ɂ��邽�߁B�����o�֐��������B

//namespace���g�����R�A
//namespace���g����static�̎��ɔ������铯���Ƃ̏Փ˂��N���Ȃ��Ȃ�B������������̎g�p�B

//enum��class��t�����enum���Œ�`���Ă��閼�O���m�̏Փ˂��N���Ȃ��Ȃ�̂�class��t�����Ă���B


//0.0f�������̂��J��Ԃ��̂��߂�ǂ��Ȃ̂ŃO���[�o���Œ�`�B
namespace {
	const float g_cTurnSpeed D3DXToRadian(10.0f);

	static const int FRAME_BUFFER_WITDH = 1920;			//�t���[���o�b�t�@�̃T�C�Y�B
	static const int FRAME_BUFFER_HEIGHT = 1080;		//�t���[���o�b�t�@�̃T�C�Y�B


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