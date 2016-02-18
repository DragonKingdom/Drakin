/**
 * @file   FadeInOut.h
 * @brief   フェードインアウトクラスヘッダ
 *
 * @author matsumura
 */

#ifndef FADEINOUT_H
#define FADEINOUT_H


///  フェードインアウトクラス
class FadeInOut
{
public:
	explicit FadeInOut(BYTE _alpha);
	virtual ~FadeInOut();

	/// フェードイン
	/**
	 * @param  _fadeInTime フェードインが完了するまでの時間(秒)
	 * @return 変化後のアルファ値
	 */
	inline BYTE FadeIn(int _fadeInTime) { return ChangeAlpha(0xff, _fadeInTime); }

	/// フェードアウト
	/**
	 * @param  _fadeOutTime フェードアウトが完了するまでの時間(秒)
	 * @return 変化後のアルファ値
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
