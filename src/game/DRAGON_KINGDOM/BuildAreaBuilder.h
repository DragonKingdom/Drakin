#ifndef BUILDAREABUILDER_H
#define BUILDAREABUILDER_H

class BuildArea;
class BuildAreaPreviewer;

class BuildAreaBuilder
{
public:
	BuildAreaBuilder();
	~BuildAreaBuilder();
	BuildArea* AreaBuild();
	void PreviewerDraw();
	void StartPosSet(D3DXVECTOR3 _startPos);
	void EndPosSet(D3DXVECTOR3 _endPos);
	void InitStartPos();
	void InitEndPos();

private:
	BuildAreaPreviewer* m_pBuildAreaPreviewer;
	D3DXVECTOR3 m_StartPos;
	D3DXVECTOR3 m_EndPos;
	bool		m_isStartPosSet;
	bool		m_isEndPosSet;

};


#endif