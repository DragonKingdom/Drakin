#ifndef ROAD_H
#define ROAD_H
#include <d3dx9.h>
#include <vector>
class Crossing;
#define ROAD_WIDTH 10.f

D3DXVECTOR3 QuadraticBezPoint( D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXVECTOR2 p3, float d );
class Road
{
private:
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3	pos;
		D3DCOLOR color;
	};
	enum STEP
	{
		STEP_FIRST,
		STEP_CONTROL,
		STEP_NEXT,
	};
	LPDIRECT3DDEVICE9 m_pDevice;
	std::vector<D3DXVECTOR3> m_centerLinePos;	// ìπÇÃç¿ïW
	std::vector<D3DXVECTOR3> m_l;
	std::vector<D3DXVECTOR3> m_r;
	std::vector<float> m_angle;		// éüÇÃì_Ç÷ÇÃäpìx
	Crossing* m_clossing[2];
	float m_length;
	float m_width;		// ìπïù
public:
	Road();
	~Road();
	void SetPos(D3DXVECTOR3);
	void SetSideRoad();
	void ShortenRoad(int);
	Road MakeInsertRoad(int);
	inline std::vector<D3DXVECTOR3> GetCenterLinePos(){return m_centerLinePos;}
	void Draw();
	inline float GetLength(){ return m_length; }
	inline void SetLength(float length){ m_length = length; }
	inline std::vector<float> GetAngle(){ return m_angle; }
};

#endif
