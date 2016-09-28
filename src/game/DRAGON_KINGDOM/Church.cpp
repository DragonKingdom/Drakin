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
	FbxFileManager::Get()->FileImport("fbx//kyoukai_LV1.fbx"); 
	FbxFileManager::Get()->GetModelData(&m_Model);

	m_ModelTexture.Load("..//sourceimages//kyoukaiUV.png");
	m_BasicStatus = GetMainStatus();
	m_Array = 0;
	m_Time = 0;
}


Church::~Church()
{
	m_Texture.Release();

	for (unsigned int i = 0; i < m_Model.size(); i++)
	{
		delete m_Model[i];
	}

}

//�R���g���[���֐�
BUILD_STATE Church::Control()
{
	CountAge();

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
		delete m_pShaderAssist;
		m_pShaderAssist = new ShaderAssist;
		m_pShaderAssist->LoadTechnique("Effect\\Church.fx", "TShader", "WVPP");
		m_LightDir = m_pShaderAssist->GetParameterHandle("LightDir");
		m_Ambient = m_pShaderAssist->GetParameterHandle("Ambient");
		m_CLUTTU = m_pShaderAssist->GetParameterHandle("CLUTTU");
		m_FogColor = m_pShaderAssist->GetParameterHandle("FogColor");
		m_Param1 = m_pShaderAssist->GetParameterHandle("Param1");
		m_Param2 = m_pShaderAssist->GetParameterHandle("Param2");

		FbxFileManager::Get()->FileImport("fbx//church_c.fbx");
		FbxFileManager::Get()->GetModelData(&m_Model);

		FbxFileManager::Get()->FileImport("fbx//church_g.fbx");
		FbxFileManager::Get()->GetModelData(&m_Model2);

		m_ModelTexture2[0].Load("..//sourceimages//church_UV1.png");
		m_ModelTexture2[1].Load("..//sourceimages//gardenUV.png");


		// �����Ń��x���Q�ɂ���
		m_houseLevel = LV2;
	}


	if (m_houseLevel == LV1)
	{
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
		GraphicsDevice::getInstance().GetDevice()->SetTexture(0, m_ModelTexture.Get());
		GraphicsDevice::getInstance().GetDevice()->SetTexture(2, m_Texture.Get());
		m_pShaderAssist->BeginPass(0);


		for (unsigned int i = 0; i < m_Model.size(); i++)
		{
			m_Model[i]->NonDraw();
		}
		


		m_pShaderAssist->EndPass();
		m_pShaderAssist->End();
	}
	else
	{
		{
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
			GraphicsDevice::getInstance().GetDevice()->SetTexture(0, m_ModelTexture2[0].Get());
			GraphicsDevice::getInstance().GetDevice()->SetTexture(2, m_Texture.Get());
			m_pShaderAssist->BeginPass(0);

			for (unsigned int i = 0; i < m_Model.size(); i++)
			{
				m_Model[i]->NonDraw();
			}

			m_pShaderAssist->EndPass();
			m_pShaderAssist->End();
		}


		{
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

			GraphicsDevice::getInstance().GetDevice()->SetTexture(0, m_ModelTexture2[1].Get());
			GraphicsDevice::getInstance().GetDevice()->SetTexture(2, m_Texture.Get());
			m_pShaderAssist->BeginPass(0);

			for (unsigned int i = 0; i < m_Model.size(); i++)
			{
				m_Model2[i]->NonDraw();
			}

			m_pShaderAssist->EndPass();
			m_pShaderAssist->End();
		}
	}
}

