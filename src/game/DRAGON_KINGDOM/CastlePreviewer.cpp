#include "stdafx.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "graphicsDevice.h"
#include "CastlePreviewer.h"


// �R���X�g���N�^
CastlePreviewer::CastlePreviewer()
{
	FbxFileManager::Get()->FileImport("fbx//house_red.fbx");
	FbxFileManager::Get()->GetModelData(&m_FbxModel);
}

// �f�X�g���N�^
CastlePreviewer::~CastlePreviewer()
{
	for (unsigned int i = 0; i < m_FbxModel.size(); i++)
	{
		delete m_FbxModel[i];
	}
}


// ���W���Z�b�g
void CastlePreviewer::SetBuildPos(D3DXVECTOR3* _BuildPos)
{
	m_BuildPos = (*_BuildPos);
}

// �p�x���Z�b�g
void CastlePreviewer::SetAngle(float* _angle)
{
	m_Angle = (*_angle);
}

// �`��
void CastlePreviewer::Draw()
{
	// ���[���h�ϊ��s��̍쐬
	D3DXMATRIX World, PositionMatrix, RotationMatrix;
	D3DXMatrixIdentity(&World);

	// ��]
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&World, &World, &RotationMatrix);

	// �ړ�
	D3DXMatrixTranslation(&PositionMatrix, m_BuildPos.x, m_BuildPos.y, m_BuildPos.z);
	D3DXMatrixMultiply(&World, &World, &PositionMatrix);

	GraphicsDevice::getInstance().GetDevice()->SetTransform(D3DTS_WORLD, &World);
	GraphicsDevice::getInstance().GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (unsigned int i = 0; i < m_FbxModel.size(); i++)
	{
		m_FbxModel[i]->NonTextureDraw();
	}
}
