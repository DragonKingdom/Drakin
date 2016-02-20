/**
 * @file   FadeInOut.h
 * @brief   �t�F�[�h�C���A�E�g�N���X�w�b�_
 *
 * @author matsumura
 */

#ifndef FADEINOUT_H
#define FADEINOUT_H


///  �t�F�[�h�C���A�E�g�N���X
class FadeInOut
{
public:
	explicit FadeInOut(BYTE _alpha);
	virtual ~FadeInOut();

	/// �t�F�[�h�C��
	/**
	 * @param  _fadeInTime �t�F�[�h�C������������܂ł̎���(�b)
	 * @return �ω���̃A���t�@�l
	 */
	inline BYTE FadeIn(int _fadeInTime) { return ChangeAlpha(0xff, _fadeInTime); }

	/// �t�F�[�h�A�E�g
	/**
	 * @param  _fadeOutTime �t�F�[�h�A�E�g����������܂ł̎���(�b)
	 * @return �ω���̃A���t�@�l
	 */
	inline BYTE FadeOut(int _fadeOutTime) { return ChangeAlpha(0x00, _fadeOutTime); }

	inline bool FadeInCompleted() { return (m_alpha == 0xff); }
	inline bool FadeOutCompleted() { return (m_alpha == 0x00); }
	inline BYTE GetAlpha() { return m_alpha; }

protected:
	BYTE ChangeAlpha(BYTE _target, int _time);

private:
	FadeInOut();

	BYTE m_alpha;

	DISALLOW_COPY_AND_ASSIGN(FadeInOut);
};

#endif // FADEINOUT_H
