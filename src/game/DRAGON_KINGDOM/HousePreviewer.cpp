#include "HousePreviewer.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "graphicsDevice.h"
#include "HouseManager.h"

HousePreviewer::HousePreviewer()
{
	FbxFileManager::Get()->FileImport("fbx//house_red.fbx");
	FbxFileManager::Get()->GetModelData(&m_FbxModel);
}

HousePreviewer::~HousePreviewer()
{
	for (unsigned int i = 0; i < m_FbxModel.size(); i++)
	{
		delete m_FbxModel[i];
	}
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

	for (unsigned int i = 0; i < m_FbxModel.size(); i++)
	{
		m_FbxModel[i]->NonTextureDraw();
	}
}
