#include "HousePreviewer.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "graphicsDevice.h"
#include "HouseManager.h"

HousePreviewer::HousePreviewer():
m_pFbxModel(new FbxModel(GraphicsDevice::getInstance().GetDevice()))
{
	FbxFileManager::Get()->FileImport("fbx//house_red.fbx");
	FbxFileManager::Get()->GetModelData(m_pFbxModel);
}

HousePreviewer::~HousePreviewer()
{
	delete m_pFbxModel;
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
	// ƒ[ƒ‹ƒh•ÏŠ·s—ñ‚Ìì¬
	D3DXMATRIX World, PositionMatrix, RotationMatrix;
	D3DXMatrixIdentity(&World);

	// ‰ñ“]
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&World, &World, &RotationMatrix);

	// ˆÚ“®
	D3DXMatrixTranslation(&PositionMatrix, m_BuildPos.x, m_BuildPos.y, m_BuildPos.z);
	D3DXMatrixMultiply(&World, &World, &PositionMatrix);

	GraphicsDevice::getInstance().GetDevice()->SetTransform(D3DTS_WORLD, &World);

	m_pFbxModel->NonTextureDraw();
}
