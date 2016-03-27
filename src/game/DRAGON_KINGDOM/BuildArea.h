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
	float x;	/*中心座標*/
	float y;	/*中心座標*/
	float z;	/*中心座標*/
	float w;	/*幅*/
	float h;	/*高さ*/
	float angle;	/*傾き*/
	BYTE AreaData;	/*エリアの上に何か乗っかってるか*/


};


#endif