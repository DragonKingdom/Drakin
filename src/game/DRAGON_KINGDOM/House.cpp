#include "House.h"
#include "FbxFileManager.h"
#include "FbxModel.h"
#include "graphicsDevice.h"
#include "ShaderAssist.h"


House::House(D3DXVECTOR3 _housePos, float _angle, HouseType _Type):
m_HousePos(_housePos),
m_Angle(_angle),
m_Type(_Type),
m_pModel(new FbxModel(GraphicsDevice::getInstance().GetDevice())),
m_pShaderAssist(new ShaderAssist())
{
	// �n���ꂽHouseType�ɂ���ēǂݍ��މƂ̎�ނ�ς���
	/*switch (m_Type)
	{
	case RED_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_red.fbx");

		break;
	case BLUE_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_blue.fbx");

		break;
	case YELLOW_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_yellow.fbx");

		break;
	case POOR_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_hinmin.fbx");

		break;	
	case RICH_HOUSE:
		FbxFileManager::Get()->FileImport("fbx//house_seleb.fbx");

		break;
	}*/

	/// @todo �Ƃ肠�����e�X�g�̂��߂�Normal�����o��

	FbxFileManager::Get()->FileImport("fbx//house_red.fbx");

	FbxFileManager::Get()->GetModelData(m_pModel);


	m_pShaderAssist->LoadTechnique("Effect\\HouseEffect.fx", "TShader", "m_WVPP");
	m_Texture.Load("Resource\\image\\CLUTLight.jpg");
	m_LightDir = m_pShaderAssist->GetParameterHandle("m_LightDir");
	m_Ambient = m_pShaderAssist->GetParameterHandle("m_Ambient");
	m_CLUTTU = m_pShaderAssist->GetParameterHandle("m_CLUTTU");
	m_FogColor = m_pShaderAssist->GetParameterHandle("m_FogColor");
	m_Param1 = m_pShaderAssist->GetParameterHandle("m_Param1");
	m_Param2 = m_pShaderAssist->GetParameterHandle("m_Param2");

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
	m_Texture.Release();
	delete m_pShaderAssist;
	delete m_pModel;
}

void House::Draw()
{
	m_pShaderAssist->Begin();
	//���z�̈ʒu���擾
	D3DXVECTOR4 LightDir = m_pShaderAssist->GetLightDir();
	D3DXMATRIX matInverse;
	D3DXVECTOR4 v;

	m_pShaderAssist->SetMatrix(&m_World);
	D3DXMatrixInverse(&matInverse, NULL, &m_World);
	D3DXVec4Transform(&v, &LightDir, &matInverse);
	D3DXVec4Normalize(&v, &v);
	m_pShaderAssist->SetParameter(m_LightDir, v);

	//���z���̕����x�N�g���̋t�x�N�g���Ə�����x�N�g���Ƃ̓��ς��v�Z
	//���̒l���J���[���b�N�A�b�v�e�[�u���� TU �����̎Q�ƈʒu�ƂȂ�
	LightDir *= -1.0f;
	D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	float dot = D3DXVec3Dot((D3DXVECTOR3*)&LightDir, &Up);
	//���̐��ɂȂ�Ȃ��悤�ɒ���
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
	GraphicsDevice::getInstance().GetDevice()->SetTexture(2, m_Texture.Get());
	m_pShaderAssist->BeginPass(0);
	// �`��
	m_pModel->Draw();
	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();

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
