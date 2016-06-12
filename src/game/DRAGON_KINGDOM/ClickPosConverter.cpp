#include "ClickPosConverter.h"

ClickPosConverter::ClickPosConverter(CameraController* _camera) :
	m_pCameraController(_camera)
{
}

ClickPosConverter::~ClickPosConverter()
{
}

void ClickPosConverter::Convert(D3DXVECTOR3* pout, float _x, float _y, float fZ,D3DXMATRIX* matView, D3DXMATRIX* matProj)
{
	// �e�s��̋t�s����Z�o
   D3DXMATRIXA16 InvView, InvPrj, VP, InvViewport;
   D3DXMatrixInverse( &InvView, NULL, matView );
   D3DXMatrixInverse( &InvPrj, NULL, matProj );
   D3DXMatrixIdentity( &VP );
   VP._11 = (float)1280.f/2.0f; VP._22 = -(float)720.f/2.0f;
   VP._41 = (float)1280.f/2.0f; VP._42 = (float)720.f/2.0f;
   D3DXMatrixInverse( &InvViewport, NULL, &VP );

   // �t�ϊ�
   D3DXMATRIXA16 tmp = InvViewport * InvPrj * InvView;
   D3DXVec3TransformCoord( pout, &D3DXVECTOR3((float)_x,(float)_y,fZ), &tmp );
}


/// @ todo ���̊֐�����������Ƃǂ��ɂ��ł��Ȃ����̂��c
D3DXVECTOR3* ClickPosConverter::ConvertForLoad(D3DXVECTOR3* pout, int Sx, int Sy)
{
	// view,proj��p��
	D3DXVECTOR3 upVec = D3DXVECTOR3(0,1,0);   // �J�����̏������ݒ�
	float viewAngle = D3DXToRadian(90);       // ����p
	float aspect = (float)1280.f/ 720.f;      // �A�X�y�N�g��
	float nearZ = 1.f;                        // �ŋߓ_
	float farZ = 100000.f;                      // �ŉ��_

	// �r���[�ϊ��p�̍s��ɕϊ�
	D3DXMATRIX matView;

	D3DXMatrixLookAtLH(&matView, &m_pCameraController->GetEyePos(), &m_pCameraController->GetLookAtPos(), &upVec);
	// �ˉe�ϊ��p�̍s��ɕϊ�
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, viewAngle, aspect, nearZ, farZ);

   D3DXVECTOR3 nearpos;
   D3DXVECTOR3 farpos;
   D3DXVECTOR3 ray;
   Convert(&nearpos, (float)Sx, (float)Sy, 0.0f, &matView, &matProj);
   Convert(&farpos, (float)Sx, (float)Sy, 1.0f, &matView, &matProj);
   ray = farpos - nearpos;
   D3DXVec3Normalize( &ray, &ray );

   // ���Ƃ̌������N���Ă���ꍇ�͌�_��
   // �N���Ă��Ȃ��ꍇ�͉����̕ǂƂ̌�_���o��
   if( ray.y <= 0 ) 
   {
      // ����_
      float Lray = D3DXVec3Dot( &ray, &D3DXVECTOR3(0,1,0) );
      float LP0 = D3DXVec3Dot( &(-nearpos), &D3DXVECTOR3(0,1,0) );
      *pout = nearpos + (LP0/Lray)*ray;
   }
   else 
   {
      *pout = farpos;
   }

   return pout;
}