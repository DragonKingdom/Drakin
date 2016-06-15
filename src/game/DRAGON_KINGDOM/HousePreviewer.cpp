#include "HousePreviewer.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "graphicsDevice.h"

HousePreviewer::HousePreviewer():
m_pHouseModel(new FbxModel(GraphicsDevice::getInstance().GetDevice()))
{
	FbxFileManager::Get()->FileImport("fbx//house_red.fbx");
	FbxFileManager::Get()->GetModelData(m_pHouseModel);
}

HousePreviewer::~HousePreviewer()
{
	delete m_pHouseModel;
}

void HousePreviewer::SetBuildPos(D3DXVECTOR3* _BuildPos)
{
	m_BuildPos = (*_BuildPos);
}

void HousePreviewer::SetAngle(float* _angle)
{
	m_Angle = (*_angle);
}

void HousePreviewer::Draw()
{
	D3DXMATRIX World, PositionMatrix, RotationMatrix;
	D3DXMatrixIdentity(&World);

	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&World, &World, &RotationMatrix);

	D3DXMatrixTranslation(&PositionMatrix, m_BuildPos.x, m_BuildPos.y, m_BuildPos.z);
	D3DXMatrixMultiply(&World, &World, &PositionMatrix);

	GraphicsDevice::getInstance().GetDevice()->SetTransform(D3DTS_WORLD, &World);

	m_pHouseModel->NonTextureDraw();
}
