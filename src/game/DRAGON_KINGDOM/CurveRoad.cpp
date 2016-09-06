#include "stdafx.h"
#include "CurveRoad.h"
#include "ShaderAssist.h"
#include <graphicsDevice.h>
CurveRoad::CurveRoad(D3DXVECTOR3 _startPos, D3DXVECTOR3 _controlPos, D3DXVECTOR3 _endPos, float _angle) :
m_ControlPos(_controlPos),
Road(_startPos, _endPos, _angle)
{
	BezierLineCreate();
}

CurveRoad::~CurveRoad()
{
	delete[] m_pVertex;
	delete[] m_pAngle;
	delete[] m_pRightLinePos;
	delete[] m_pLeftLinePos;
}

void CurveRoad::BezierLineCreate()
{
	int length = static_cast<int>(CalculateBezierLength());
	// �G���A�̐�
	int NumZ = 0;
	int VecLength = 0;

	if (length % int(ROAD_H_SIZE) == int(ROAD_H_SIZE - 1))
	{
		NumZ = int(length / ROAD_W_SIZE) + 1;
		VecLength = int(NumZ * ROAD_H_SIZE);
	}
	else
	{
		NumZ = int(length / ROAD_W_SIZE);
		VecLength = int(NumZ * ROAD_H_SIZE);
	}
	int RoadNum = static_cast<int>(VecLength / ROAD_H_SIZE);

	m_pLeftLinePos   = new D3DXVECTOR3[RoadNum];
	m_pRightLinePos  = new D3DXVECTOR3[RoadNum];
	m_pAngle		 = new float[RoadNum];

	for (int i = 0; i < RoadNum; i++)
	{
		m_TmpCenterLinePos.push_back(QuadraticBezPoint(i * 1.f / (float)(RoadNum - 1)));
	}

	for (int i = 0; i < RoadNum; i++)
	{
		m_CenterLinePos.push_back(QuadraticConstantBezPoint(i * 1.f / (float)(RoadNum - 1),RoadNum));
	}

	for (int i = 0; i < RoadNum - 1; i++)
	{
		m_pAngle[i] =
			atan2(m_CenterLinePos[i + 1].z - m_CenterLinePos[i].z,
			m_CenterLinePos[i + 1].x - m_CenterLinePos[i].x);
	}
	m_pAngle[RoadNum - 1] =
		atan2(m_CenterLinePos[RoadNum - 1].z - m_CenterLinePos[RoadNum - 2].z,
		m_CenterLinePos[RoadNum - 1].x - m_CenterLinePos[RoadNum - 2].x);


	for (int i = 0; i < RoadNum; i++)
	{
		D3DXVECTOR3 p;
		p.x = m_CenterLinePos[i].x + ROAD_H_SIZE/2 * sin(m_pAngle[i]);
		p.y = 20.f;
		p.z = m_CenterLinePos[i].z + ROAD_H_SIZE/2 * -cos(m_pAngle[i]);

		m_pLeftLinePos[i] = p;

		p.x = m_CenterLinePos[i].x + -ROAD_H_SIZE/2 * sin(m_pAngle[i]);
		p.z = m_CenterLinePos[i].z + -ROAD_H_SIZE / 2 * -cos(m_pAngle[i]);
		m_pRightLinePos[i] = p;
	}

	//�E�ƍ��̒��_������̂�2�{
	m_pVertex = new CUSTOMVERTEX[RoadNum * 2];
	for (int i = 0; i < RoadNum; i++)
	{
		m_pVertex[i * 2].pos = m_pLeftLinePos[i];
		m_pVertex[i * 2].tu = 0.f;
		m_pVertex[i * 2].tv = i * 1.f / (m_CenterLinePos.size() - 1);
		m_pVertex[i * 2 + 1].pos = m_pRightLinePos[i];
		m_pVertex[i * 2 + 1].tu = 1.f;
		m_pVertex[i * 2 + 1].tv = i * 1.f / (m_CenterLinePos.size() - 1);
	}
}

float CurveRoad::CalculateBezierLength()
{
	float length = 0.f;
	// �x�W�F�Ȑ��̒��������߂�
	float t2 = 1;
	float t1 = 0;

	D3DXVECTOR3 p1 = m_StartPos;
	D3DXVECTOR3 p2 = m_ControlPos;
	D3DXVECTOR3 p3 = m_EndPos;

	float xa = 2 * (p1.x - 2 * p2.x + p3.x);
	float ya = 2 * (p1.z - 2 * p2.z + p3.z);

	float xb = -2 * p1.x + 2 * p2.x;
	float yb = -2 * p1.z + 2 * p2.z;

	float a = xa*xa + ya*ya;
	float b = 2 * (xa*xb + ya*yb);
	float c = xb*xb + yb*yb;
	float D = b*b - 4 * a*c;

	if (D)
	{
		float s1 = 2 * sqrt(a*(t1*(a*t1 + b) + c)) + 2 * a*t1 + b;
		float s2 = 2 * sqrt(a*(t2*(a*t2 + b) + c)) + 2 * a*t2 + b;
		length = (s2*s2 - s1*s1 - D*(4 * log(s2 / s1) + D*(1 / (s2*s2) - 1 / (s1*s1)))) / (32 * a*sqrt(a));
	}
	else if (a)
	{
		length = (abs(2 * a*t2 + b)*(2 * a*t2 + b) - abs(2 * a*t1 + b)*(2 * a*t1 + b)) / (8 * a*sqrt(a));
	}
	else
	{
		length = sqrt(c)*(t2 - t1);
	}
	return length;
}

D3DXVECTOR3 CurveRoad::QuadraticBezPoint(float _t)
{
	D3DXVECTOR3 vertex = D3DXVECTOR3(0, 20.f, 0);
	//���l�̈ꎞ�ۑ��ϐ�
	float valueTemp = (1.f - _t) * (1.f - _t);
	
	vertex.x += valueTemp * m_StartPos.x;
	vertex.z += valueTemp * m_StartPos.z;

	valueTemp = 2 * _t * (1 - _t);
	vertex.x += valueTemp * m_ControlPos.x;
	vertex.z += valueTemp * m_ControlPos.z;

	valueTemp = _t * _t;
	vertex.x += valueTemp * m_EndPos.x;
	vertex.z += valueTemp * m_EndPos.z;

	return vertex;
}

D3DXVECTOR3 CurveRoad::QuadraticConstantBezPoint(float _t,int _divideNum)
{
	int N = _divideNum;
	float ni = 1 / static_cast<float>(N);
	float tt = 0;
	float x, t = _t / static_cast<float>(_divideNum);
	float *dd = new float[N + 1];
	//D3DXVECTOR3 startPos;
	D3DXVECTOR3 endPos;
	//�n�߂̒�����0
	dd[0] = 0;

	for (int i = 1; i < N; i++)
	{
		tt += ni;
		endPos = QuadraticBezPoint(tt);
		float distance = pow((m_TmpCenterLinePos[i - 1].x - endPos.x)*(m_TmpCenterLinePos[i - 1].x - endPos.x)
			+ (m_TmpCenterLinePos[i - 1].z - endPos.z)*(m_TmpCenterLinePos[i - 1].z - endPos.z), 0.5);
		dd[i] = dd[i - 1] + distance;
	}

	//�����̍��v(=dd[N])�Ő��K��
	//�����dd��dd[0]=0<dd[1]<dd[2]<...<dd[N-1]<dd[N]=1�ƂȂ�
	for (int i = 1; i<N + 1; i++){
		dd[i] /= dd[N];
	}
	//�w�肳�ꂽt�������ł����Ɖ��Ԗڂ̋��k�ɂ��邩�����߂�
	int k = 0;
	for (int i = 0; i<N; i++, k++){
		if (dd[i] <= t && t <= dd[i + 1])break;
	}

	//t����ԓ��̂ǂ̂�����ɂ��邩�𒲂ׂ�
	//t=dd[k]�Ȃ�x=0,t=dd[k+1]�Ȃ�x=1,0<=x<=1
	x = (t - dd[k]) / (dd[k + 1] - dd[k]);
	//���̊����Ő��`��Ԃ��A��Ԓ���������
	x = (k*(1 - x) + (1 + k)*x)*ni;
	delete[] dd;
	return QuadraticBezPoint(x * _t);
}

void CurveRoad::Control()
{

}

void CurveRoad::Draw()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	m_pShaderAssist->Begin();
	//���z�̈ʒu���擾
	D3DXVECTOR4 LightDir = m_pShaderAssist->GetLightDir();
	D3DXMATRIX matInverse;
	D3DXVECTOR4 v;

	m_pShaderAssist->SetMatrix(&matWorld);
	D3DXMatrixInverse(&matInverse, NULL, &matWorld);
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
	GraphicsDevice::getInstance().GetDevice()->SetTexture(1, m_FogTexture.Get());
	m_pShaderAssist->BeginPass(0);

	GraphicsDevice::getInstance().GetDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	GraphicsDevice::getInstance().GetDevice()->SetTexture(0, m_Texture.Get());
	GraphicsDevice::getInstance().GetDevice()->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,
		m_CenterLinePos.size() * 2 - 2,
		m_pVertex,
		sizeof(CUSTOMVERTEX)
		);

	m_pShaderAssist->EndPass();
	m_pShaderAssist->End();
}

bool CurveRoad::GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _startPos)
{
	double length = pow((_checkPos->x - m_StartPos.x)*(_checkPos->x - m_StartPos.x) +
		(_checkPos->z - m_StartPos.z)*(_checkPos->z - m_StartPos.z), 0.5);

	float angle = atan2(m_CenterLinePos[1].z - m_CenterLinePos[0].z,
		m_CenterLinePos[1].x - m_CenterLinePos[0].x);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(angle);
		*_outputPos = m_StartPos;
		*_startPos = true;
		return true;
	}


	length = pow((_checkPos->x - m_EndPos.x)*(_checkPos->x - m_EndPos.x) +
		(_checkPos->z - m_EndPos.z)*(_checkPos->z - m_EndPos.z), 0.5);

	angle = atan2(m_CenterLinePos[m_CenterLinePos.size() - 1].z - m_CenterLinePos[m_CenterLinePos.size() - 2].z,
		m_CenterLinePos[m_CenterLinePos.size() - 1].x - m_CenterLinePos[m_CenterLinePos.size() - 2].x);

	if (length < 3000.f)
	{
		*_outputAngleDegree = D3DXToDegree(angle);
		*_outputPos = m_CenterLinePos[m_CenterLinePos.size() - 1];
		*_startPos = false;
		return true;
	}
	return false;
}
