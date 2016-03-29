#ifndef BUILDAREA_H
#define BUILDAREA_H


class BuildArea
{
public:
	BuildArea();
	~BuildArea();
	void Draw();

private:
	Vertex      m_Vertex;
	Texture		m_Texture;
	D3DXVECTOR3 m_RoadStartPos;	/*対応する道の始点*/
	D3DXVECTOR3 m_RoadEndPos;	/*対応する道の終点*/
	float m_x;	/*中心座標*/
	float m_y;	/*中心座標*/
	float m_z;	/*中心座標*/
	float m_w;	/*幅*/
	float m_h;	/*高さ*/
	float m_angle;	/*傾き*/
	BYTE  m_AreaData;	/*エリアの上に何か乗っかってるか*/


};


#endif