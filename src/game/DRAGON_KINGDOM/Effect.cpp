#include "stdafx.h"
#include "Effect.h"


Effect::Effect(char* _fileName, float _scale, int _texNum, int _playSpeed) :
m_TextureNum(_texNum),
m_PlaySpeed(_playSpeed),
m_Angle(0),
m_Scale(_scale),
m_Pos(D3DXVECTOR3(0,0,0))
{
	FbxFileManager::Get()->FileImport(_fileName);
	FbxFileManager::Get()->GetModelData(&m_Model);
}

Effect::~Effect()
{
	for (int i = 0; i < m_pTextureArray.size();i++)
	{
		m_pTextureArray[i]->Release();
	}
}

void Effect::Control()
{
	// ŒvŽZ—p‚Ìs—ñ
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX PositionMatrix;

	// ‰ñ“]
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixIdentity(&RotationMatrix);
	D3DXMatrixRotationY(&RotationMatrix, m_Angle);
	D3DXMatrixMultiply(&m_World, &m_World, &RotationMatrix);
	D3DXMatrixScaling(&m_World, m_Scale, m_Scale, m_Scale);
	// ˆÚ“®
	D3DXMatrixTranslation(&PositionMatrix, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_World, &m_World, &PositionMatrix);

	m_Time++;
	if (m_Time == m_PlaySpeed * m_MaxTextureNum)
	{
		m_Time = 0;
	}

	if (m_Time)
	{
		m_TextureNum = m_Time / m_PlaySpeed;
	}
	else
	{
		m_TextureNum = 0;
	}
}

void Effect::Draw()
{
	GraphicsDevice::getInstance().GetDevice()->SetTexture(0, m_pTextureArray[m_TextureNum]->Get());
	for (unsigned int i = 0; i < m_Model.size(); i++)
	{
		m_Model[i]->EffectDraw();
	}
}

void Effect::PushTexture(char* _str)
{
	Texture* pTexture = new Texture;
	pTexture->Load(_str);
	m_pTextureArray.push_back(pTexture);
}