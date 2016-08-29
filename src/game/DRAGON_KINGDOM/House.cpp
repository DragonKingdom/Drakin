#include "House.h"
#include "graphicsDevice.h"
#include "ShaderAssist.h"


House::House(D3DXVECTOR3 _housePos, float _angle, int _Type) :
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
	m_Status.Comfort = 10;
	m_Status.Landscape = 10;
	m_Status.Influence = 1000;
	m_Status.Age = 0;
}

House::~House()
{
	m_Texture.Release();
	delete m_pShaderAssist;
}

void House::Control()
{
	/// @todo 時間をうまくとる方法がぱっとでなかったからとりあえずこれで実装してる

	m_AgeCount++;
	if (m_AgeCount > 3600)
	{
		/// @todo 適当に上限作ってるだけ、仕様がわかり次第直す
		if (m_Status.Age < 100000)
		{
			m_Status.Age++;
		}
		
		m_AgeCount = 0;
	}
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
