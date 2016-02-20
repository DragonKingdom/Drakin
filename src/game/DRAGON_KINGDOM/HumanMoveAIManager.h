#ifndef HUMANMOVEAIMANAGER_H
#define HUMANMOVEAIMANAGER_H
#include <anim3DModel.h>
#include "HumanMoveAI.h"
#include <vector>
class HumanMoveAIManager
{
public:
	HumanMoveAIManager(CrossingManager*, RoadManager*);
	~HumanMoveAIManager();
private:
	LPDIRECT3DDEVICE9 m_pDevice;
	AnimModel* m_pModel;
	std::vector<HumanMoveAI> m_humanMoveAI;
	CrossingManager* m_pCrossingManager;
	RoadManager* m_pRoad;
public:
	void Control();
	void Draw();
	void AddHuman();
};

#endif	// HUMANMOVEAIMANAGER_H