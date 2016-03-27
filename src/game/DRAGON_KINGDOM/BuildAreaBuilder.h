#ifndef BUILDAREABUILDER_H
#define BUILDAREABUILDER_H

class BuildArea;
class BuildAreaPreviewer;

class BuildAreaBuilder
{
public:
	BuildAreaBuilder();
	~BuildAreaBuilder();
	void /* BuildArea* */ AreaBuild();
	void  PreviewerDraw();

private:
	BuildAreaPreviewer* m_pBuildAreaPreviewer;

};


#endif