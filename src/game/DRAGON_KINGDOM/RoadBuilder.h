#ifndef ROADBUILDER_H
#define ROADBUILDER_H

class Road;
class RoadPreviewer;


class RoadBuilder
{
public:
	RoadBuilder();
	~RoadBuilder();
	void StartPosSet(const D3DXVECTOR2 _startPos);
	void EndPosSet(const D3DXVECTOR2 _endPos);
	Road* RoadBuild();
	void  PreviewerDraw();

private:
	RoadPreviewer*	m_pRoadPreviewer;
	D3DXVECTOR2		m_StartPos;
	D3DXVECTOR2		m_EndPos;


};



#endif