#ifndef BUILDAREA_H
#define BUILDAREA_H

class LSS;
class BuildArea
{
public:
	BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos, float _angle, float _roadLinkStartAngle, float _roadLinkEndAngle, bool _roadLinkStart, bool roadLinkEnd);
	~BuildArea();
	void Draw();
	bool AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle);
	void GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _roadLinkStartAngle, float* _roadLinkEndAngle, bool* _startLinkFlag, bool* _endLinkFlag);
	float GetAngleDegree(){ return D3DXToDegree(m_angle); };
private:
	Vertex      m_Vertex;
	Texture		m_Texture;
	D3DXVECTOR3 m_RoadStartPos;	/*対応する道の始点*/
	D3DXVECTOR3 m_RoadEndPos;	/*対応する道の終点*/
	D3DXVECTOR3 m_pBuildArea[4];
	bool  m_isLeft;/*道に対して左にあるAreaかのフラグ*/
	float m_x;	/*中心座標*/
	float m_y;	/*中心座標*/
	float m_z;	/*中心座標*/
	float m_w;	/*幅*/
	float m_h;	/*高さ*/
	float m_tu[4];	/*テクスチャ座標*/
	float m_tv[4];	/*テクスチャ座標*/
	float m_angle;	/*傾き*/
	float m_roadStartLinkAngle; /*道が繋がっていた場所からの角度*/ 
	float m_roadEndLinkAngle; /*道が繋がっていた場所からの角度*/
	int	  m_length;
	BYTE  m_AreaData;	/*エリアの上に何か乗っかってるか*/
	
	int m_Z;
	Font m_Font;
	int m_AreaCountX;
	int m_AreaCountZ;
	float MousePosX;
	float MousePosZ;

	//シェーダーを適用するクラス
	LSS* m_pLSS;

	//無理やりここで太陽の位置を出しているので今後消す予定
	D3DXVECTOR4 m_DirectionalVec;
	D3DXVECTOR4 m_UpVec;
	D3DXVECTOR4 m_SunPos;
	//太陽の角度
	float SunRotation;
	//太陽の半径
	float SunRadius;
	//----------------------------------------------

};


#endif