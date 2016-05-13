#ifndef BUILDAREA_H
#define BUILDAREA_H


class BuildArea
{
public:
	BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos, float _angle);
	~BuildArea();
	void Draw();
	bool AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle);

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
	int m_length;
	BYTE  m_AreaData;	/*エリアの上に何か乗っかってるか*/
	
	int m_Z;
	Font m_Font;
	int m_AreaCountX;
	int m_AreaCountZ;

};


#endif