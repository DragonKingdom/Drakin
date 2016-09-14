#ifndef BUILDAREABUILDER_H
#define BUILDAREABUILDER_H

class BuildArea;
class BuildAreaPreviewer;

class BuildAreaBuilder
{
public:
	BuildAreaBuilder();
	~BuildAreaBuilder();
	BuildArea* AreaBuild(bool _isLeft, BUILDAREAMANAGER_ENUM::BUILD_TYPE _buildType);
	BuildArea* NormalAreaBuild(bool _isLeft);
	BuildArea* CurveAreaBuild(bool _isLeft);

	void PreviewerDraw();
	void StartPosSet(D3DXVECTOR3 _startPos);
	void ControlPosSet(const D3DXVECTOR3 _controlPos);
	void EndPosSet(D3DXVECTOR3 _endPos);
	void StartPosLinkSet(bool _startLink);
	void EndPosLinkSet(bool _endLink);
	void SetRoadStartAngle(float _roadStartAngle){ m_roadStartAngle = _roadStartAngle; }
	void SetRoadEndAngle(float _roadEndAngle){ m_roadEndAngle = _roadEndAngle; }
	void InitStartPos();
	void InitControlPos();
	void InitEndPos();
	bool BuildCheck(bool roadLinkStart_StartPos, bool roadLinkEnd_StartPos);

private:
	bool BuildAngleCheck(float _roadAngle);

	BuildAreaPreviewer* m_pBuildAreaPreviewer;
	D3DXVECTOR3 m_StartPos;
	D3DXVECTOR3 m_ControlPos;
	D3DXVECTOR3 m_EndPos;
	float		m_roadStartAngle;
	float		m_roadEndAngle;
	bool		m_StartPosLink;
	bool		m_EndPosLink;
	bool		m_isStartPosSet;
	bool		m_isEndPosSet;

};


#endif