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
	void SetDrawState(bool _isBuild);
	void Draw();

private:
	/// ‰Æ‚ğ•`‰æ‚·‚é3DÀ•W
	D3DXVECTOR3 m_BuildPos;

	/// •`‰æ‚·‚é‰Æ‚ÌŠp“x
	float		m_Angle;

	/// ‰Æ‚Ìƒ‚ƒfƒ‹‚ğŠi”[‚µ‚Ä‚éƒNƒ‰ƒX
	FbxModel*	m_pHouseModel;


};


#endif