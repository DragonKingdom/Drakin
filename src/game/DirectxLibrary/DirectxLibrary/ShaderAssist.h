#ifndef SHADERASSIST_H
#define SHADERASSIST_H
#include <d3dx9.h>
class ShaderAssist
{
private:
	LPDIRECT3DDEVICE9	m_pDevice;
	LPD3DXEFFECT		m_pEffect;

	// @todo ���͂܂��g���ĂȂ����V�F�[�_�[�ŃJ�����̍��W���g�����Ƃ������̂ō���Ă���
	static const D3DXVECTOR4*  m_pCameraPos;
	static const D3DXVECTOR4*  m_pLightDirection;
	D3DXHANDLE			m_pTechnique;
	//�ϊ��ςݍs����i�[����ꏊ
	D3DXHANDLE			m_pWVPP;
	D3DXMATRIX			m_matView, m_matProj;
public:
	ShaderAssist();
	~ShaderAssist();
	/**
	* �V�F�[�_�[�̃p�����[�^�̃n���h�����擾����
	* @param[in] _paramName �p�����[�^�̕�����
	* @return �p�����[�^�̃n���h����Ԃ�
	*/
	D3DXHANDLE GetParameterHandle(const char* _paramName);
	/**
	* �V�F�[�_�[�̃p�����[�^�ɕϐ����Z�b�g����
	* @param[in] _ParamHandle ���ꂽ���p�����[�^�̃n���h��
	* @param[in] ���ꂽ���ϐ�
	* @return �p�����[�^�̃n���h����Ԃ�
	*/
	void SetParameter(D3DXHANDLE _ParamHandle, D3DXVECTOR4 _vector4);
	void SetParameter(D3DXHANDLE _ParamHandle, float _float);
	void SetParameter(D3DXHANDLE _ParamHandle, D3DXMATRIX _matrix);

	void SetLightDir(D3DXVECTOR4* _pLightDirection){ m_pLightDirection = _pLightDirection; };
	/**
	* �V�F�[�_�[�̃p�����[�^�̃n���h�����擾����
	* @param[in] _pFxFileName fx�t�@�C���̃p�X
	* @param[in] _entryPoint fx�t�@�C���̃G���g���|�C���g��
	* @param[in] _worldViewProjection �V�F�[�_�[�ł������W�ϊ��ςݍs�������p�����[�^
	* @return ���������S_OK��Ԃ�
	*/
	HRESULT LoadTechnique(char* _pFxFileName,const char* _entryPoint, const char* _worldViewProjection);
	void Begin();
	void BeginPass(UINT _Pass);
	void SetMatrix(D3DXMATRIX* _pMatWorld);
	void EndPass();
	void End();

};
#endif