#ifndef BUILDAREA_H
#define BUILDAREA_H

class BuildArea
{
public:
	BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos, D3DXVECTOR3 _EndPos, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd);
	virtual ~BuildArea();
	virtual void Draw();
	//エリアの中心座標を求める
	virtual bool AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle, int _Type);

	/**
	 * エリア内の座標に建物があるかないかをチェックする関数
	 * @param[in] _checkPos	チェックしたい座標
	 * @param[in] _Type チェックした座標に建てる物
	 * @return エリアが空いていればfalse
	 */
	virtual bool AreaCheck(D3DXVECTOR3* _checkPos, int _Type);

	/**
	 * 建物が建築されたことを伝える関数
	 * @param[in] 建築された場所
	 * @param[in] 建築物
	 * @return 成功したらtrue
	 */
	virtual bool SetBuilding(D3DXVECTOR3* _setPos, int _Type);

	virtual bool UnSetBuilding(D3DXVECTOR3* _setPos);

	virtual bool GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _startPos);
	float GetAngleDegree(){ return D3DXToDegree(m_angle); };
	virtual void GetBuildAreaData(std::vector<float>* _pBuildAreaVertexData, std::vector<float>* _pBuildAreaAngleData, std::vector<int>* _pBuildAreaFlag);

protected:
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3	pos;
		FLOAT	tu, tv;
	};

	Vertex      m_Vertex;
	Texture		m_Texture;
	D3DXVECTOR3 m_RoadStartPos;	/*対応する道の始点*/
	D3DXVECTOR3 m_RoadEndPos;	/*対応する道の終点*/
	D3DXVECTOR3 m_StartPos;
	D3DXVECTOR3 m_ControlPos;
	D3DXVECTOR3 m_EndPos;

	bool	m_isLeft;	/*道に対して左にあるAreaかのフラグ*/
	float	m_tu[4];
	float	m_tv[4];
	float	m_angle;	/*傾き*/
	float	m_roadStartAngle;	/*道が繋がっていた場所からの角度*/
	float	m_roadEndAngle;		/*道が繋がっていた場所からの角度*/
	int		m_length;
	int		m_roadLength;
	BYTE*	m_pAreaData;
	bool	m_StartLink;
	bool	m_EndLink;


	Font m_Font;
	float MousePosX;
	float MousePosZ;

	bool RoadAngleCheck(float _roadAngle);

};


#endif