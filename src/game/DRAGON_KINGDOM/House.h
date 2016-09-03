#ifndef HOUSE_H
#define HOUSE_H

#include "HouseBuilder.h"

class FbxModel;
class ShaderAssist;


class House
{
public:
	struct Status
	{
		float Landscape;		// 景観
		float Comfort;			// 快適
		float Influence;		// 影響度
		int Age;				// 年齢
	};

	House(D3DXVECTOR3 _housePos, float _angle, int _Type);
	virtual ~House();
	/**2016/09/03k型を変更 haga*/
	virtual BUILD_STATE Control();
	virtual void Draw();
	Status			GetHouseStatus(){ return m_Status; };
	virtual Status	GetMainStatus(){ return Status{ 10.f, 10.f, 1000.f, 0 }; };
	D3DXVECTOR3		GetHousePos(){ return m_HousePos; };
	void			GetHouseData(std::vector<float>* _pHouseVertexData, std::vector<float>* _pHouseAngleData, std::vector<int>* _pHouseStatus);
	void			SetHouseStatus(House::Status _Status){ m_Status = _Status; };
	/**2016/09/03追加 haga*/
	/**年齢をカウントする関数*/
	void			CountAge();
	/**2016/09/03追加 haga*/
	/**最終ステータスを決定する*/
	void			DecisionHouseStatus();

	//補正値取得用
	void			GetCorrectionStatus(){ m_CorrectionStatus.Landscape = 3; }
	

protected:
	std::vector<FbxModel*>	m_Model;
	D3DXVECTOR3				m_HousePos;
	float					m_Angle;
	D3DXMATRIX				m_World;				// ワールド変換行列
	int						m_Type;					// 建物の種類
	House::Status			m_Status;				// 建物のステータス(基本ステータス + 補正値)
	House::Status			m_BasicStatus;			// 建物の基本ステータス
	House::Status			m_CorrectionStatus;		// 他の建物からの補正値
	int						m_AgeCount;				// 年齢をカウントするための変数 (修正予定)

	ShaderAssist*			m_pShaderAssist;
	Texture					m_Texture;
	D3DXHANDLE m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;

private:

};

#endif