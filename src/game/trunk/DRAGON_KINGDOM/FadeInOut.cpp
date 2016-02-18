/**
 * @file   FadeInOut.cpp
 * @brief  �t�F�[�h�C���A�E�g�N���X����
 *
 * @author matsumura
 */

#include "FadeInOut.h"

FadeInOut::FadeInOut(BYTE _alpha) :
	m_alpha(_alpha)
{
}

FadeInOut::~FadeInOut()
{
}

BYTE FadeInOut::ChangeAlpha(BYTE _target, int _time)
{
	// ���t���[�������ăt�F�[�h�C��/�A�E�g���邩
	int fadeInOutFrameCount = _time * 60;
	if(fadeInOutFrameCount <= 0) 
	{
		return m_alpha;
	}

	// 1�t���[��������̃A���t�@�l�̕ω���
	BYTE changeValue = 0xff / fadeInOutFrameCount;

	int tempAlpha;	//  �I�[�o�[�t���[����\��������̂�int
	bool canChangeAlpha = false;
	switch(_target) 
	{
	case 0x00:
		// �t�F�[�h�A�E�g
		tempAlpha = m_alpha - changeValue;
		canChangeAlpha = (0x00 < tempAlpha);
		break;
	case 0xff:
		// �t�F�[�h�C��
		tempAlpha = m_alpha + changeValue;
		canChangeAlpha = (0xff > tempAlpha);
		break;
	default:
		// fail safe
		return m_alpha;
		break;
	}

	if(canChangeAlpha) 
	{
		m_alpha = static_cast<BYTE>(tempAlpha);
	} 
	else 
	{
		m_alpha = _target;
	}

	return m_alpha;
}
