#ifndef ROADMANAGER_H
#define ROADMANAGER_H
#include "Road.h"
class CrossingManager;
class BuildAreaManager;
#define MAXROADLENGTH 500
#define ROADLINESPACE 30
#define CROSSCHECKSPACE 2
#define MIN_ROAD_LENGTH 30
#define PREVIEWROADSIZE 8
class RoadManager
{
private:
	std::vector<Road> m_Road;
	Road* m_pCurrentRoad;
	D3DXVECTOR2 m_startPos;
	D3DXVECTOR2 m_endPos;
	bool m_setStartPos;
	bool m_controlFlag;
	D3DXVECTOR2 m_controlPos;
	CrossingManager* m_pCrossingManager;
	BuildAreaManager* m_pBuildAreaManager;
	D3DXVECTOR3 m_previewRoad[PREVIEWROADSIZE];
	D3DXVECTOR3 m_previewLeft[PREVIEWROADSIZE];
	D3DXVECTOR3 m_previewRight[PREVIEWROADSIZE];
	float m_previewRoadAngle[PREVIEWROADSIZE];

	D3DXVECTOR3 m_prevMousePos;
	LPDIRECT3DDEVICE9 m_pDevice;
public:
	RoadManager(CrossingManager* _cross,BuildAreaManager* _build);
	~RoadManager();
	bool GetStartflag(){ return m_setStartPos; }
	std::vector<Road> GetRoad(){return m_Road;}
	void SetControlPos(float x, float y);
	void SetPos(float x, float y);
	void CleanSetPos();
	void SetRoad();
	void Draw();
	void PreviewDraw();
	void PreviewRoadControl(D3DXVECTOR3);
	void PreviewSet();
};

#endif