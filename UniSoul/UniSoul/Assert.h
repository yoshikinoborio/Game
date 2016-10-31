#pragma once

/*!
*@brief	�A�T�[�g
*@param[in]	flag	�U�̂Ƃ��A�T�[�g���������܂��B
*/
static inline void Assert(bool flag)
{
	if (!flag){
		MessageBox(nullptr, "�G���[���������܂���", "�A�T�[�g", MB_OK);
		std::abort();
	}
}

#ifdef _DEBUG
#define 	CH_ASSERT( flg)	Assert( flg)
#else
#define 	CH_ASSERT(flg)
#endif 
