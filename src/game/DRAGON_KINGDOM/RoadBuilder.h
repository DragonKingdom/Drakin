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
	void StartPosLinkSet(bool _startLink);
	void EndPosLinkSet(bool _endLink);
	bool BuildCheck(bool _roadLinkStart_StartPos, bool _roadLinkEnd_StartPos);
	bool BuildAngleCheck(float _roadAngle);
	void SetRoadStartAngle(float _roadStartAngle){ m_roadStartAngle = _roadStartAngle; }
	void SetRoadEndAngle(float _roadEndAngle){ m_roadEndAngle = _roadEndAngle; }

private:
	RoadPreviewer*	m_pRoadPreviewer;
	D3DXVECTOR3		m_StartPos;
	D3DXVECTOR3		m_EndPos;
	float			m_roadStartAngle;
	float			m_roadEndAngle;
	bool			m_StartPosLink;
	bool			m_EndPosLink;
	bool			m_isStartPointSet;
	bool			m_isEndPointSet;

};



#endif