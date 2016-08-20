#include "House.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "graphicsDevice.h"
#include "ShaderAssist.h"


House::House(D3DXVECTOR3 _housePos, float _angle, HouseType _Type) :
m_HousePos(_housePos),
m_Angle(_angle),
m_Type(_Type),
m_pShaderAssist(new ShaderAssist())
{
	m_FogTexture.Load("Resource\\image\\CLUTLight.jpg");


	// �v�Z�p�̍s��
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	// ��]
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// �ړ�
	D3DXMatrixTranslation(&PositionMatrix, m_HousePos.x, m_HousePos.y, m_HousePos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &PositionMatrix);
}

House::~House()
{
	m_FogTexture.Release();
	delete m_pShaderAssist;
}

void House::Draw()
{
}

void House::GetHouseData(std::vector<float>* _pHouseVertexData, std::vector<float>* _pHouseAngleData, std::vector<int>* _pHouseStatus)
{
	// ���W���
	_pHouseVertexData->push_back(m_HousePos.x);
	_pHouseVertexData->push_back(m_HousePos.y);
	_pHouseVertexData->push_back(m_HousePos.z);

	// �p�x
	_pHouseAngleData->push_back(m_Angle);

	// �Ƃ̃X�e�[�^�X
	_pHouseStatus->push_back(m_Type);
}
