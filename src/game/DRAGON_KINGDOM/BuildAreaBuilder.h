#ifndef BUILDAREABUILDER_H
#define BUILDAREABUILDER_H

class BuildArea;
class BuildAreaPreviewer;

class BuildAreaBuilder
{
public:
	BuildAreaBuilder();
	~BuildAreaBuilder();
	BuildArea* AreaBuild(bool _isLeft, float _roadStartAngle, float _roadEndAngle);
	void PreviewerDraw();
	void StartPosSet(D3DXVECTOR3 _startPos);
	void EndPosSet(D3DXVECTOR3 _endPos);
	void StartPosLinkSet(bool _startLink);
	void EndPosLinkSet(bool _endLink);
	void InitStartPos();
	void InitEndPos();
	bool BuildCheck(float _roadStartAngle, float _roadEndAngle, bool roadLinkStart_StartPos, bool roadLinkEnd_StartPos);

private:
	bool BuildAngleCheck(float _roadAngle);

	BuildAreaPreviewer* m_pBuildAreaPreviewer;
	D3DXVECTOR3 m_StartPos;
	D3DXVECTOR3 m_EndPos;
	bool		m_StartPosLink;
	bool		m_EndPosLink;
	bool		m_isStartPosSet;
	bool		m_isEndPosSet;

};


#endif