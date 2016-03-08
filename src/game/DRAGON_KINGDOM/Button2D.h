/**
 * @file   Button2D.h
 * @brief  2Dのボタンクラスヘッダ
 *
 * @author matsumura
 */

#ifndef BUTTON2D_H
#define BUTTON2D_H

/// 基準点種別
enum RefPoint
{
	kTopLeft,
	kCenter
};

/// 2Dのボタンクラス
/**
 * 自身がクリックされたことやマウスオーバーを取得できる。
 * UI部品等、2Dのボタンオブジェクトは本クラスを継承すると便利なはず。
 */
class InputDeviceFacade;

class Button2D
{
public:
	/// コンストラクタ
	/**
	 * 基準点は左上と中心のいずれかを指定できる
	 *
	 * @param _refPoint 基準点種別
	 * @param _position 基準座標
	 */
	Button2D(RefPoint _refPoint, D3DXVECTOR2 _position);
	virtual ~Button2D();

	Vertex::FRECT GetRect(){ return m_rect; }  //２/２６追加

protected:
	bool IsMouseOver();
	bool IsLeftClicked();
	void SetRect(float _width, float _height);

	D3DXVECTOR2 m_position;
	RefPoint m_refPoint;
	Vertex::FRECT m_rect;
	InputDeviceFacade* m_pIdf;

private:
	// 隠蔽
	Button2D();
	DISALLOW_COPY_AND_ASSIGN(Button2D);
};

#endif // BUTTON2D_H
