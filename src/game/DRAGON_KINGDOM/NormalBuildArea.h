#ifndef NORMALBUILDAREA_H
#define NORMALBUILDAREA_H
#include "BuildArea.h"

class NormalBuildArea : public BuildArea
{
public:
	NormalBuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos, D3DXVECTOR3 _EndPos, float _angle, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd);
	~NormalBuildArea();
	void Draw();
	bool AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle, int _Type);

	/**
	* エリア内の座標に建物が歩かないかをチェックする関数
	* @param[in] チェックしたい座標
	* @return エリアが空いていればfalse
	*/
	bool AreaCheck(D3DXVECTOR3* _checkPos, int _Type);

	/**
	* 建物が建築されたことを伝える関数
	* @param[in] 建築された場所
	* @return 成功したらtrue
	*/
	bool  SetBuilding(D3DXVECTOR3* _setPos, int _Type);

	bool UnSetBuilding(D3DXVECTOR3* _setPos);

	bool  GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _startPos);
	float GetAngleDegree(){ return D3DXToDegree(m_angle); };
	void  GetBuildAreaData(std::vector<float>* _pBuildAreaVertexData, std::vector<float>* _pBuildAreaAngleData, std::vector<int>* _pBuildAreaFlag);

private:
	D3DXVECTOR3 m_pBuildArea[4];
	Vertex      m_Vertex;
	float		m_x;		/*中心座標*/
	float		m_y;		/*中心座標*/
	float		m_z;		/*中心座標*/
	float		m_w;		/*幅*/
	float		m_h;		/*高さ*/
	float		m_tu[4];	/*テクスチャ座標*/
	float		m_tv[4];	/*テクスチャ座標*/
	float		m_angle;
	int			m_length;
	int			m_roadLength;
	BYTE*		m_pAreaData;

	Font		m_Font;
	int			m_AreaCountX;
	int			m_AreaCountZ;
	float		MousePosX;
	float		MousePosZ;

	void LeftRoadCreate();
	void RightRoadCreate();
};

#endif