#ifndef BUILDAREA_H
#define BUILDAREA_H

class BuildArea
{
public:
	BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos, float _angle, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd, BUILDAREAMANAGER_ENUM::BUILD_TYPE _buildType);
	BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _controlPos, D3DXVECTOR3 _roadEndPos, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd, BUILDAREAMANAGER_ENUM::BUILD_TYPE _buildType);
	~BuildArea();
	void Draw();
	bool AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle);

	/**
	 * エリア内の座標に建物が歩かないかをチェックする関数
	 * @param[in] チェックしたい座標
	 * @return エリアが空いていればfalse
	 */
	bool AreaCheck(D3DXVECTOR3* _checkPos);

	/**
	 * 建物が建築されたことを伝える関数
	 * @param[in] 建築された場所
	 * @return 成功したらtrue
	 */
	bool SetBuilding(D3DXVECTOR3* _setPos);

	bool GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _startPos);
	float GetAngleDegree(){ return D3DXToDegree(m_angle); };
	void GetBuildAreaData(std::vector<float>* _pBuildAreaVertexData, std::vector<float>* _pBuildAreaAngleData, std::vector<int>* _pBuildAreaFlag);

private:
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
	D3DXVECTOR3 m_pBuildArea[4];
	D3DXVECTOR3** m_ppCurveBuildArea;
	BUILDAREAMANAGER_ENUM::BUILD_TYPE m_buildType;
	std::vector<D3DXVECTOR3> m_CenterLinePos;//曲線のビルドエリアを作るときに使う
	std::vector<D3DXVECTOR3> m_TmpCenterLinePos;//曲線のビルドエリアを作るときの頂点一時保存

	bool** m_AreaExcist; //ビルドエリアが存在しているか？

	bool	m_isLeft;	/*道に対して左にあるAreaかのフラグ*/
	float	m_x;		/*中心座標*/
	float	m_y;		/*中心座標*/
	float	m_z;		/*中心座標*/
	float	m_w;		/*幅*/
	float	m_h;		/*高さ*/
	float	m_tu[4];	/*テクスチャ座標*/
	float	m_tv[4];	/*テクスチャ座標*/
	float	m_angle;	/*傾き*/
	float	m_roadStartAngle;	/*道が繋がっていた場所からの角度*/
	float	m_roadEndAngle;		/*道が繋がっていた場所からの角度*/
	int		m_length;
	int		m_roadLength;
	BYTE*	m_pAreaData;
	bool	m_StartLink;
	bool	m_EndLink;


	Font m_Font;
	int m_AreaCountX;
	int m_AreaCountZ;
	float MousePosX;
	float MousePosZ;

	float CalculateBezierLength();
	D3DXVECTOR3 QuadraticBezPoint(float _t);
	D3DXVECTOR3 QuadraticConstantBezPoint(int _divideNum,int _nowCnt);
	bool RoadAngleCheck(float _roadAngle);

};


#endif