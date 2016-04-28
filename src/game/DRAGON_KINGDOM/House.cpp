#include "House.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "graphicsDevice.h"

House::House(D3DXVECTOR3 _housePos, float _angle):
m_HousePos(_housePos),
m_Angle(_angle),
m_pModel(new FbxModel(GraphicsDevice::getInstance().GetDevice()))
{
	FbxFileManager::Get()->FileImport("fbx//house.fbx");
	FbxFileManager::Get()->GetModelData(m_pModel);

	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;


	// ‰ñ“]
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);

	// ˆÚ“®
	D3DXMatrixTranslation(&PositionMatrix, m_HousePos.x, m_HousePos.y, m_HousePos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &PositionMatrix);
	
}

House::~House()
{
	delete m_pModel;
}

void House::Draw()
{
	GraphicsDevice::getInstance().GetDevice()->SetTransform(D3DTS_WORLD, &m_World);
	m_pModel->Draw();
}


