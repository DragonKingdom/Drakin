#pragma once
#include "BuildArea.h"

class NormalBuildArea : public BuildArea
{
public:
	NormalBuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos, float _angle, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd);
	~NormalBuildArea();
	void Draw();
	bool AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle);

	/**
	* �G���A���̍��W�Ɍ����������Ȃ������`�F�b�N����֐�
	* @param[in] �`�F�b�N���������W
	* @return �G���A���󂢂Ă����false
	*/
	bool AreaCheck(D3DXVECTOR3* _checkPos);

	/**
	* ���������z���ꂽ���Ƃ�`����֐�
	* @param[in] ���z���ꂽ�ꏊ
	* @return ����������true
	*/
	bool SetBuilding(D3DXVECTOR3* _setPos);

	bool GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _startPos);
	float GetAngleDegree(){ return D3DXToDegree(m_angle); };
	void GetBuildAreaData(std::vector<float>* _pBuildAreaVertexData, std::vector<float>* _pBuildAreaAngleData, std::vector<int>* _pBuildAreaFlag);

private:
	float	m_x;		/*���S���W*/
	float	m_y;		/*���S���W*/
	float	m_z;		/*���S���W*/
	float	m_w;		/*��*/
	float	m_h;		/*����*/
	float	m_tu[4];	/*�e�N�X�`�����W*/
	float	m_tv[4];	/*�e�N�X�`�����W*/
	float m_angle;
	int		m_length;
	int		m_roadLength;
	BYTE*	m_pAreaData;
	Vertex      m_Vertex;
	D3DXVECTOR3 m_pBuildArea[4];

	Font m_Font;
	int m_AreaCountX;
	int m_AreaCountZ;
	float MousePosX;
	float MousePosZ;

	void LeftRoadCreate();
	void RightRoadCreate();
};

