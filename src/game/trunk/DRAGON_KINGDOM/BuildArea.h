#ifndef BUILDAREA_H
#define BUILDAREA_H
#include <d3dx9.h>
#include <Model.h>
#define BUILD_SIZE 200.f
#define BUILD_TIME 30
class BuildArea
{
public:
	enum BUILD_TYPE
	{
		HOUSE,
	};
	enum AREA_STATE
	{
		STATE_FREE,
		STATE_CREATE,
		STATE_BUILD,
	};
	
	BuildArea(D3DXVECTOR3,float);
	~BuildArea();
	void AreaDraw(LPDIRECT3DDEVICE9 _device);
	void BuildDraw(LPDIRECT3DDEVICE9 _device,Model* _model);
private:

	struct CUSTOMVERTEX
	{
		D3DXVECTOR3	pos;
		D3DCOLOR color;
	};
	D3DXVECTOR3 m_pos;
	float m_angle;
	AREA_STATE m_state;
	BUILD_TYPE m_buildType;
	int m_createTime;
public:
	void TimeIncrement();
	D3DXVECTOR3 GetPos(){ return m_pos; }
	AREA_STATE GetState(){ return m_state; }
	void SetState(AREA_STATE _state){ m_state = _state; }
	void SetBuild(BUILD_TYPE _type){ m_buildType = _type; }
	void SetCreateTime(int _time){ m_createTime = _time; }
};

#endif