/**
*
*
*/
#include "stdafx.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "ShaderAssist.h"
#include "Church.h"


Church::Church(D3DXVECTOR3 _housePos, float _angle, BUILD_STATE _Type) :
House(_housePos, _angle, _Type)
{
	FbxFileManager::Get()->FileImport("fbx//eff1.fbx");
	FbxFileManager::Get()->GetModelData(&m_Model);
	m_BasicStatus = GetMainStatus();
	m_Array = 0;
	m_Time = 0;
	m_testTexture[0].Load("..//sourceimages//redeffect.0000.png");
	m_testTexture[1].Load("..//sourceimages//redeffect.0001.png");
	m_testTexture[2].Load("..//sourceimages//redeffect.0002.png");
	m_testTexture[3].Load("..//sourceimages//redeffect.0003.png");
	m_testTexture[4].Load("..//sourceimages//redeffect.0004.png");
	m_testTexture[5].Load("..//sourceimages//redeffect.0005.png");
	m_testTexture[6].Load("..//sourceimages//redeffect.0006.png");
	m_testTexture[7].Load("..//sourceimages//redeffect.0007.png");
	m_testTexture[8].Load("..//sourceimages//redeffect.0008.png");
	m_testTexture[9].Load("..//sourceimages//redeffect.0009.png");
}


Church::~Church()
{
	for (unsigned int i = 0; i < m_Model.size(); i++)
	{
		delete m_Model[i];
	}

}

//�R���g���[���֐�
BUILD_STATE Church::Control()
{
	CountAge();

	m_Time++;
	if (m_Time == 60)
	{
		m_Time = 0;
	}

	if (m_Time < 6)
	{
		m_Array = 1;
	}
	else if (m_Time < 12)
	{
		m_Array = 1;
	}
	else if (m_Time < 18)
	{
		m_Array = 2;
	}
	else if (m_Time < 24)
	{
		m_Array = 3;
	}
	else if (m_Time < 30)
	{
		m_Array = 4;
	}
	else if (m_Time < 36)
	{
		m_Array = 5;
	}
	else if (m_Time < 42)
	{
		m_Array = 6;
	}
	else if (m_Time < 48)
	{
		m_Array = 7;
	}
	else if (m_Time < 54)
	{
		m_Array = 8;
	}
	else if (m_Time < 60)
	{
		m_Array = 9;
	}
	return BUILD_CHURCH;

}
/**���������͂ɗ^����e���l���擾����֐�*/
float Church::GetInfluence()
{
	return (CHURCH_INFLUENCE + (CHURCH_INFLUENCE * m_BasicStatus.Age));
}

//2016/09/10���_Draw��NonTextureDraw�ɕύX
//�`��֐�
void Church::Draw()
{
	// �����͌��݂Q�N��������ς��悤�ɐݒ肵�Ă���
	// �����ɒB���Ă����烌�x���Q�ֈڍs����
	if (m_houseLevel == LV1 && m_BasicStatus.Age == 2)
	{
		for (unsigned int i = 0; i < m_Model.size(); i++)
		{
			delete m_Model[i];
		}
		m_Model.clear();
		FbxFileManager::Get()->FileImport("fbx//church.fbx");
		FbxFileManager::Get()->GetModelData(&m_Model);

		// �����Ń��x���Q�ɂ���
		m_houseLevel = LV2;
	}

	m_pShaderAssist->Begin();

	// ���z�̈ʒu���擾
	D3DXVECTOR4 LightDir = m_pShaderAssist->GetLightDir();
	D3DXMATRIX matInverse;
	D3DXVECTOR4 v;

	m_pShaderAssist->SetMatrix(&m_World);
	D3DXMatrixInverse(&matInverse, NULL, &m_World);
	D3DXVec4Transform(&v, &LightDir, &matInverse);
	D3DXVec4Normalize(&v, &v);
	m_pShaderAssist->SetParameter(m_LightDir, v);

	// ���z���̕����x�N�g���̋t�x�N�g���Ə�����x�N�g���Ƃ̓��ς��v�Z
	// ���̒l���J���[���b�N�A�b�v�e�[�u���� TU �����̎Q�ƈʒu�ƂȂ�
	LightDir *= -1.0f;
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	float dot = D3DXVec3Dot((D3DXVECTOR3*)&LightDir, &Up);

	// ���̐��ɂȂ�Ȃ��悤�ɒ���
	dot = (1.0f + dot) * 0.5f;
	m_pShaderAssist->SetParameter(m_CLUTTU, dot);

	D3DXVECTOR4 ambient = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	m_pShaderAssist->SetParameter(m_Ambient, ambient);

	// �t�H�O�̌v�Z���̐��l��ݒ�
	m_pShaderAssist->SetParameter(m_Param1, 60000.0f);
	m_pShaderAssist->SetParameter(m_Param2, 0.5f);

	// �t�H�O�̐F��ݒ�
	ambient = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pShaderAssist->SetParameter(m_FogColor, ambient);
	GraphicsDevice::getInstance().GetDevice()->SetTexture(0, m_testTexture[m_Array].Get());
	GraphicsDevice::getInstance().GetDevice()->SetTexture(2, m_Texture.Get());
	m_pShaderAssist->BeginPass(0);

	for (unsigned int i = 0; i < m_Model.size(); i++)
	{
		m_Model[i]->NonTextureDraw();
	}

	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();

}

