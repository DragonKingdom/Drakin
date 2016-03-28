#include "BuildAreaBuilder.h"
#include "BuildAreaPreviewer.h"
#include "BuildArea.h"

BuildAreaBuilder::BuildAreaBuilder():
m_pBuildAreaPreviewer(new BuildAreaPreviewer()),
m_isStartPosSet(false),
m_isEndPosSet(false)
{
}

BuildAreaBuilder::~BuildAreaBuilder()
{
	delete m_pBuildAreaPreviewer;
}

BuildArea* BuildAreaBuilder::AreaBuild()
{
	/// @todo BuildAreaƒNƒ‰ƒX‚Í–¢ŽÀ‘•‚È‚Ì‚Å‹ó
	BuildArea* pBuildArea = new BuildArea();

	return pBuildArea;
}

void BuildAreaBuilder::PreviewerDraw()
{
	m_pBuildAreaPreviewer->Draw();
}

void BuildAreaBuilder::StartPosSet(D3DXVECTOR3 _startPos)
{
	m_isStartPosSet = true;
	m_pBuildAreaPreviewer->StartPosSet(_startPos);
	m_StartPos = _startPos;
}

void BuildAreaBuilder::EndPosSet(D3DXVECTOR3 _endPos)
{
	m_isEndPosSet = true;
	m_pBuildAreaPreviewer->EndPosSet(_endPos);
	m_EndPos = _endPos;
}

void BuildAreaBuilder::InitStartPos()
{
	m_isStartPosSet = false;
	m_pBuildAreaPreviewer->InitStartPos();
	m_StartPos = D3DXVECTOR3(0, 0, 0);
}

void BuildAreaBuilder::InitEndPos()
{
	m_isEndPosSet = false;
	m_pBuildAreaPreviewer->InitEndPos();
	m_EndPos = D3DXVECTOR3(0, 0, 0);
}

