#ifndef HOUSE_H
#define HOUSE_H

//特殊建物が周りに及ぼす影響範囲（１単位１ブロック）
#define INFLUENCE_RANGE 5

#include "HouseBuilder.h"

class FbxModel;
class ShaderAssist;


class House
{
public:

	// ステータス
	struct Status
	{
		float Landscape;		// 景観
		float Comfort;			// 快適
		float Influence;		// 影響度
		int Age;				// 年齢
		int Hp;					// 耐久度
	};

	// 建物レベル
	enum Level
	{
		LV1,	//!<レベル1
		LV2,	//!<レベル2
		LVMAX
	};

	//	マップ補正倍率	//	追加
	struct CorrectPer
	{
		float Landscape;		// 景観
		float Comfort;			// 快適
		float Influence;		// 影響度
		float Hp;					// 耐久度
	};
	//

	House(D3DXVECTOR3 _housePos, float _angle, int _Type);
	virtual ~House();
	/**2016/09/03k型を変更 haga*/
	virtual BUILD_STATE Control();
	virtual void Draw();
	Status			GetHouseStatus(){ return m_Status; };
	virtual Status	GetMainStatus(){ return Status{ 10.f, 10.f, 1000.f, 0, 0 }; };
	D3DXVECTOR3		GetHousePos(){ return m_HousePos; };
	void			GetHouseData(std::vector<float>* _pHouseVertexData, std::vector<float>* _pHouseAngleData, std::vector<int>* _pHouseStatus);
	void			SetHouseStatus(House::Status _Status){ m_Status = _Status; };
	void			SetCorrectionStatus(House::Status _Status);
	/**2016/09/03追加 haga*/
	/**年齢をカウントする関数*/
	void			CountAge();
	/**建物が周囲に与える影響値を取得する関数*/
	virtual float GetInfluence();
	/**最終ステータスを決定する*/
	void			DecisionHouseStatus();
	
	

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
	House::Level			m_houseLevel;			// 家のレベル

	House::CorrectPer		m_CorrectPer;			//	マップ補正倍率

	ShaderAssist*			m_pShaderAssist;
	Texture					m_Texture;
	D3DXHANDLE m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;

	void House::HouseState();	//	追加

private:

};

#endif