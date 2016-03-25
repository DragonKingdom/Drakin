#ifndef ROADBUILDER_H
#define ROADBUILDER_H

class Road;
class RoadPreviewer;


class RoadBuilder
{
public:
	RoadBuilder();
	~RoadBuilder();
	void StartPosSet(const D3DXVECTOR3 _startPos);
	void EndPosSet(const D3DXVECTOR3 _endPos);
	void InitStartPos();
	void InitEndPos();
	Road* RoadBuild();
	void  PreviewerDraw();

private:
	RoadPreviewer*	m_pRoadPreviewer;
	D3DXVECTOR3		m_StartPos;
	D3DXVECTOR3		m_EndPos;
	bool			m_isStartPointSet;
	bool			m_isEndPointSet;

};



#endif