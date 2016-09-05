#ifndef ROADPREVIEWER_H
#define ROADPREVIEWER_H


class RoadPreviewer
{
public:
	RoadPreviewer();
	~RoadPreviewer();
	
	/**
	 * プレビューの描画関数
	 */
	void Draw();

	void BuildModeSet(ROADMANAGER_ENUM::BUILD_TYPE _buildType){ m_BuildType = _buildType; }

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

	void ControlPosSet(D3DXVECTOR3 _controlPos){ m_ControlPos = _controlPos; }

	void InitControlPos(){ m_ControlPos = D3DXVECTOR3(0, 0, 0); };

	/**
	 * セットした始点の初期化
	 */
	void InitStartPos();

	/**
	 * セットした終点の初期化
	 */
	void InitEndPos();

private:
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3	pos;
		FLOAT	tu, tv;
	};

	void NormalDraw();

	void CurveDraw();

	void BezierLineCreate();
	float CalculateBezierLength();
	D3DXVECTOR3 QuadraticBezPoint(float _t);
	D3DXVECTOR3 QuadraticConstantBezPoint(float _t, int _divideNum);
	std::vector<D3DXVECTOR3> m_CenterLinePos;
	std::vector<D3DXVECTOR3> m_TmpCenterLinePos;

	D3DXVECTOR3	m_StartPos;
	D3DXVECTOR3 m_ControlPos;
	D3DXVECTOR3	m_EndPos;
	Vertex		m_vertex;
	Texture     m_Texture;
	ROADMANAGER_ENUM::BUILD_TYPE m_BuildType;

};


#endif