#ifndef CURVEBUILDAREA_H
#define CURVEBUILDAREA_H
#include "BuildArea.h"
class CurveBuildArea : public BuildArea
{
public:
	CurveBuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadControlPos, D3DXVECTOR3 _roadEndPos, D3DXVECTOR3 _EndPos, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd);

	~CurveBuildArea();
	void Draw();
	bool AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle);
	bool CurveAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle, int _array);

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
	//bool SetBuilding(D3DXVECTOR3* _setPos){};

	bool GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _startPos);
	//float GetAngleDegree(){ return D3DXToDegree(m_angle); };
	//void GetBuildAreaData(std::vector<float>* _pBuildAreaVertexData, std::vector<float>* _pBuildAreaAngleData, std::vector<int>* _pBuildAreaFlag){};

private:
	D3DXVECTOR3 m_ControlPos;
	D3DXVECTOR3** m_ppCurveBuildArea;
	bool** m_AreaExcist; //ビルドエリアが存在しているか？
	std::vector<D3DXVECTOR3> m_CenterLinePos;//曲線のビルドエリアを作るときに使う
	std::vector<D3DXVECTOR3> m_TmpCenterLinePos;//曲線のビルドエリアを作るときの頂点一時保存

	std::vector<float> m_Angle;
	std::vector<float> m_x;		/*中心座標*/;
	std::vector<float> m_y;		/*中心座標*/;
	std::vector<float> m_z;		/*中心座標*/;
	std::vector<float> m_w;		/*幅*/;
	BYTE*		m_pAreaData;
	int m_AreaCountX;
	int m_AreaCountZ;

	/*高さは固定なのでいらない*/
	float CalculateBezierLength();
	D3DXVECTOR3 QuadraticBezPoint(float _t);
	D3DXVECTOR3 QuadraticConstantBezPoint(int _divideNum, int _nowCnt);
	void LeftRoadCreate();
	void RightRoadCreate();
	bool CurveAreaCheck(D3DXVECTOR3* _checkPos, int _array);

};
#endif
