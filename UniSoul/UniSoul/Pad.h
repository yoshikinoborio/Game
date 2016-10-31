#pragma once

#include "XInput.h"	//XInput API

#define		s_cast		static_cast

//�p�b�h�N���X
class Pad{
public:
	/*!
	 *@brief	�p�b�h�X�e�[�g�B
	 */
	struct PAD_STATE
	{
		XINPUT_STATE state;
		bool bConnected;
	};
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	Pad();
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	~Pad();
	/*!
	*@brief	�������B
	*@param[in]	padNo	�p�b�h�ԍ��B
	*/
	void Initialize(int padNo)
	{
		m_padNo = padNo;
	}
	/*!
	*@brief	�X�V�B
	*/
	void Update();
	/*!
	 *@brief	�{�^���̃g���K�[����B
	 *@return	true���Ԃ��Ă�����g���K�[���́B
	 */
	bool IsTrigger(EnButton button) const
	{
		//CH_ASSERT(button < enButtonNum, "button is invalid");
		return m_trigger[button] != 0;
	}
	/*!
	 *@brief	�{�^����������Ă��邩����B
	 *@return	true���Ԃ��Ă����牟����Ă���B
	 */
	bool IsPress(EnButton button) const
	{
		//CH_ASSERT(button < enButtonNum, "button is invalid");
		return m_press[button] != 0;
	}
	/*!
	*@brief	���X�e�B�b�N��X���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetLStickXF() const
	{
		return m_lStickX;
	}
	/*!
	*@brief	���X�e�B�b�N��Y���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetLStickYF() const
	{
		return m_lStickY;
	}
	/*!
	*@brief	�E�X�e�B�b�N��X���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetRStickXF() const
	{
		return m_rStickX;
	}
	/*!
	*@brief	�E�X�e�B�b�N��Y���̓��͗ʂ��擾�B
	*@return	-1.0�`1.0�̐��K�����ꂽ�l��Ԃ��B
	*/
	float GetRStickYF() const
	{
		return m_rStickY;
	}
	
private:
	PAD_STATE m_state;			//�p�b�h�X�e�[�g�B
	int m_padNo;				//�p�b�h�ԍ��B
	int m_trigger[enButtonNum];	//�g���K�[���͂̃t���O�B
	int m_press[enButtonNum];	//press���͂̃t���O�B
	float m_lStickX;			//���X�e�B�b�N��X���̓��͗ʁB
	float m_lStickY;			//���X�e�B�b�N��Y���̓��͗ʁB
	float m_rStickX;			//�E�X�e�B�b�N��X���̓��͗ʁB
	float m_rStickY;			//�E�X�e�B�b�N��Y���̓��͗ʁB
};