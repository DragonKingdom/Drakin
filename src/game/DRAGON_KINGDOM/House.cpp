#include "House.h"
#include "graphicsDevice.h"
#include "ShaderAssist.h"


House::House(D3DXVECTOR3 _housePos, float _angle, BUILD_STATE _Type) :
m_HousePos(_housePos),
m_Angle(_angle),
m_Type(_Type),
m_AgeCount(0),
m_pShaderAssist(new ShaderAssist())
{
	m_Texture.Load("Resource\\image\\CLUTLight.jpg");
	m_pShaderAssist->LoadTechnique("Effect\\HouseEffect.fx", "TShader", "WVPP");
	m_LightDir = m_pShaderAssist->GetParameterHandle("LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("Param2");

	// 計算用の行列
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	// 回転
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// 移動
	D3DXMatrixTranslation(&PositionMatrix, m_HousePos.x, m_HousePos.y, m_HousePos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &PositionMatrix);


	/// @todo 今はここでやってる
	// 適当にステータス初期化
	m_Status.Comfort = 10.f;
	m_Status.Landscape = 10.f;
	m_Status.Influence = 1000.f;
	m_Status.Age = 0;
	m_Status.Hp = 20;
	m_Status.DamagePoint = 0;

	// 補正値を初期化
	m_CorrectionStatus.Comfort = 0.f;
	m_CorrectionStatus.Influence = 0.f;
	m_CorrectionStatus.Landscape = 0.f;
	m_CorrectionStatus.Age = 0;
	m_CorrectionStatus.Hp = 0;

	// レベルをいれる
	m_houseLevel = LV1;

}

House::~House()
{
	m_Texture.Release();
	delete m_pShaderAssist;
}

BUILD_STATE House::Control()
{
	CountAge();

	return BUILD_NONE;

}

void House::Draw()
{

}

void House::GetHouseData(std::vector<float>* _pHouseVertexData, std::vector<float>* _pHouseAngleData, std::vector<int>* _pHouseStatus)
{
	// 座標情報
	_pHouseVertexData->push_back(m_HousePos.x);
	_pHouseVertexData->push_back(m_HousePos.y);
	_pHouseVertexData->push_back(m_HousePos.z);

	// 角度
	_pHouseAngleData->push_back(m_Angle);

	// 家のステータス
	_pHouseStatus->push_back(m_Type);
}

//年齢をカウントする関数(Houseを継承するクラスのすべてで使用予定)
void House::CountAge()
{
	/// @todo 時間をうまくとる方法がぱっとでなかったからとりあえずこれで実装してる

	m_AgeCount++;
	if (m_AgeCount > 3600)
	{
		/// @todo 適当に上限作ってるだけ、仕様がわかり次第直す
		if (m_BasicStatus.Age < 100000)
		{
			m_BasicStatus.Age++;
		}

		m_AgeCount = 0;
	}
}

/**建物が周囲に与える影響値を取得する関数*/
float House::GetInfluence()
{
	//中は継承クラスごとに異なる
	return 0.0f;
}

/**補正値を修正する関数*/
void House::SetCorrectionStatus(House::Status _Status)
{

	m_CorrectionStatus.Comfort += _Status.Comfort;
	m_CorrectionStatus.Influence += _Status.Influence;
	m_CorrectionStatus.Landscape += _Status.Landscape;
	m_CorrectionStatus.Hp += _Status.Hp;
}

/**建物本来のステータスと補正値を足して最終的なステータスを決定する*/
void House::DecisionHouseStatus()
{
	//建物のステータスを最終決定する
	m_Status.Age = m_BasicStatus.Age;
	m_Status.Comfort   = (m_BasicStatus.Comfort + m_CorrectionStatus.Comfort);
	m_Status.Influence = (m_BasicStatus.Influence + m_CorrectionStatus.Influence);
	m_Status.Landscape = (m_BasicStatus.Landscape + m_CorrectionStatus.Landscape);
	m_Status.Hp		   = (m_BasicStatus.Hp + m_CorrectionStatus.Hp) - m_Status.DamagePoint;
	
	//補正値を初期化
	m_CorrectionStatus.Comfort = 0.f;
	m_CorrectionStatus.Influence = 0.f;
	m_CorrectionStatus.Landscape = 0.f;
	m_CorrectionStatus.Hp = 0;
	
}

bool House::UpDateHouseData()
{
	m_Status.Hp = (m_BasicStatus.Hp + m_CorrectionStatus.Hp) - m_Status.DamagePoint;
	if (m_Status.Hp <= 0)
	{
		return true;
	}
	return false;
}