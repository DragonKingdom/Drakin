/**
 * @file   TitlePushToStart.h
 * @brief  タイトル画面の「PushToStart」表示クラスヘッダ
 *
 * @author matsumura
 */

#ifndef TITLEPUSHTOSTART_H
#define TITLEPUSHTOSTART_H

/// タイトル画面の「PushToStart」表示クラス
class TitlePushToStart
{
public:
	TitlePushToStart();
	virtual ~TitlePushToStart();

	void Control();
	void Draw();

	bool m_visible;

protected:

private:
	DISALLOW_COPY_AND_ASSIGN(TitlePushToStart);
};

#endif // TITLEPUSHTOSTART_H
