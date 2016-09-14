#include "HousePreviewer.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "graphicsDevice.h"
#include "HouseManager.h"

HousePreviewer::HousePreviewer()
{
	FbxFileManager::Get()->FileImport("fbx//house_red.fbx");
	FbxFileManager::Get()->GetModelData(&m_FbxModelHouse);

	FbxFileManager::Get()->FileImport("fbx//kyoukai_LV1.fbx");
	FbxFileManager::Get()->GetModelData(&m_FbxModelChurch);

	FbxFileManager::Get()->FileImport("fbx//kaziya.fbx");
	FbxFileManager::Get()->GetModelData(&m_FbxModelSmith);
}

HousePreviewer::~HousePreviewer()
{
	for (unsigned int i = 0; i < m_FbxModelHouse.size(); i++)
	{
		delete m_FbxModelHouse[i];
	}

	for (unsigned int i = 0; i < m_FbxModelChurch.size(); i++)
	{
		delete m_FbxModelChurch[i];
	}

	for (unsigned int i = 0; i < m_FbxModelSmith.size(); i++)
	{
		delete m_FbxModelSmith[i];
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

void HousePreviewer::Draw(int _Type)
{
	// ワールド変換行列の作成
	D3DXMATRIX World, PositionMatrix, RotationMatrix;
	D3DXMatrixIdentity(&World);

	// 回転
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&World, &World, &RotationMatrix);

	// 移動
	D3DXMatrixTranslation(&PositionMatrix, m_BuildPos.x, m_BuildPos.y, m_BuildPos.z);
	D3DXMatrixMultiply(&World, &World, &PositionMatrix);

	GraphicsDevice::getInstance().GetDevice()->SetTransform(D3DTS_WORLD, &World);

	// 建物の種類によって表示するプレビューを変える
	switch(_Type)
	{
	case BUILD_CHURCH:
		for (unsigned int i = 0; i < m_FbxModelChurch.size(); i++)
		{
			m_FbxModelChurch[i]->NonTextureDraw();
		}

		break;

	case BUILD_BLACKSMITH:
		for (unsigned int i = 0; i < m_FbxModelSmith.size(); i++)
		{
			m_FbxModelSmith[i]->NonTextureDraw();
		}

		break;

	default:
		for (unsigned int i = 0; i < m_FbxModelHouse.size(); i++)
		{
			m_FbxModelHouse[i]->NonTextureDraw();
		}
		break;

	}


}
