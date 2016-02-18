/**
 * @file   FadeInOut.cpp
 * @brief  フェードインアウトクラス実装
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
	// 何フレームかけてフェードイン/アウトするか
	int fadeInOutFrameCount = _time * 60;
	if(fadeInOutFrameCount <= 0) 
	{
		return m_alpha;
	}

	// 1フレームあたりのアルファ値の変化量
	BYTE changeValue = 0xff / fadeInOutFrameCount;

	int tempAlpha;	//  オーバーフローする可能性があるのでint
	bool canChangeAlpha = false;
	switch(_target) 
	{
	case 0x00:
		// フェードアウト
		tempAlpha = m_alpha - changeValue;
		canChangeAlpha = (0x00 < tempAlpha);
		break;
	case 0xff:
		// フェードイン
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
