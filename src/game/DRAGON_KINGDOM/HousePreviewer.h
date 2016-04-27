#ifndef HOUSEPREVIEWER_H
#define HOUSEPREVIEWER_H

class FbxModel;

class HousePreviewer
{
public:
	HousePreviewer();
	~HousePreviewer();
	void SetBuildPos(D3DXVECTOR3* _buildPos);
	void SetAngle(float* _angle);
	void Draw();

private:
	D3DXVECTOR3 m_BuildPos;
	float		m_Angle;
	FbxModel*	m_pFbxModel;

};


#endif