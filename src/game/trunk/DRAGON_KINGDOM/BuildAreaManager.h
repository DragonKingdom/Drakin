#ifndef BUILDAREAMANAGER_H
#define BUILDAREAMANAGER_H
#include "BuildArea.h"
#include <vector>
#include <Model.h>
#include "GameData.h"
class BuildAreaManager
{
public:
	Model* m_pModel;
	BuildAreaManager();
	~BuildAreaManager();
	void AddBuildArea(D3DXVECTOR3 pos, float angle);
	void Update();
	void Draw();

	bool PutBuild(D3DXVECTOR3 _pos, BuildArea::BUILD_TYPE _type);
private:
	LPDIRECT3DDEVICE9 m_pDevice;
	GameData* m_pGameData;
	std::vector<BuildArea> m_buildArea;

	int m_currentTime;
};

#endif