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
	void Draw(int _Type);

private:
	/// 家を描画する3D座標
	D3DXVECTOR3 m_BuildPos;

	/// 描画する家の角度
	float		m_Angle;

	/// 家のモデルを格納してるクラス
	std::vector<FbxModel*>   m_FbxModelHouse;

	/// 教会のモデルを格納しているクラス
	std::vector<FbxModel*>   m_FbxModelChurch;

	/// 鍛冶屋のモデルを格納しているクラス
	std::vector<FbxModel*>   m_FbxModelSmith;
};


#endif