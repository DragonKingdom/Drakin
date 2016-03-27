#include "BuildAreaBuilder.h"
#include "BuildAreaPreviewer.h"


BuildAreaBuilder::BuildAreaBuilder():
m_pBuildAreaPreviewer(new BuildAreaPreviewer())
{
}

BuildAreaBuilder::~BuildAreaBuilder()
{
	delete m_pBuildAreaPreviewer;
}

void /* BuildArea* */ BuildAreaBuilder::AreaBuild()
{

}

void BuildAreaBuilder::PreviewerDraw()
{
	m_pBuildAreaPreviewer->Draw();
}
