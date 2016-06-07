#ifndef BUILDAREAPREVIEWER_H
#define BUILDAREAPREVIEWER_H
class BuildAreaPreviewer
{
public:
	BuildAreaPreviewer();
	~BuildAreaPreviewer();

	/**
	* プレビューの描画関数
	*/
	void Draw();

	/**
	* 道の始点をセットする関数
	* @param [in] _startPos セットするxyz座標
	*/
	void StartPosSet(D3DXVECTOR3 _startPos);

	/**
	* 道の終点をセットする関数
	* @param [in] _endPos セットするxyz座標
	*/
	void EndPosSet(D3DXVECTOR3 _endPos);

	/**
	* セットした始点の初期化
	*/
	void InitStartPos();

	/**
	* セットした終点の初期化
	*/
	void InitEndPos();

private:
	D3DXVECTOR3	m_StartPos;
	D3DXVECTOR3	m_EndPos;
	float		m_angle;
	Vertex		m_vertex;
	Texture     m_Texture;
};



#endif