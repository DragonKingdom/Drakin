#ifndef CURVEBUILDAREA_H
#define CURVEBUILDAREA_H
#include "BuildArea.h"
class CurveBuildArea : public BuildArea
{
public:
	CurveBuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadControlPos, D3DXVECTOR3 _roadEndPos, D3DXVECTOR3 _EndPos, float _roadStartAngle, float _roadEndAngle, bool _roadLinkStart, bool _roadLinkEnd);

	~CurveBuildArea();
	void Draw();
	bool AreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle);
	bool CurveAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle, int _array);

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
	//bool SetBuilding(D3DXVECTOR3* _setPos){};

	bool GetStartOrEndPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _outputPos, float* _outputAngleDegree, bool* _startPos);
	//float GetAngleDegree(){ return D3DXToDegree(m_angle); };
	//void GetBuildAreaData(std::vector<float>* _pBuildAreaVertexData, std::vector<float>* _pBuildAreaAngleData, std::vector<int>* _pBuildAreaFlag){};

private:
	D3DXVECTOR3 m_ControlPos;
	D3DXVECTOR3** m_ppCurveBuildArea;
	bool** m_AreaExcist; //�r���h�G���A�����݂��Ă��邩�H
	std::vector<D3DXVECTOR3> m_CenterLinePos;//�Ȑ��̃r���h�G���A�����Ƃ��Ɏg��
	std::vector<D3DXVECTOR3> m_TmpCenterLinePos;//�Ȑ��̃r���h�G���A�����Ƃ��̒��_�ꎞ�ۑ�

	std::vector<float> m_Angle;
	std::vector<float> m_x;		/*���S���W*/;
	std::vector<float> m_y;		/*���S���W*/;
	std::vector<float> m_z;		/*���S���W*/;
	std::vector<float> m_w;		/*��*/;
	BYTE*		m_pAreaData;
	int m_AreaCountX;
	int m_AreaCountZ;

	/*�����͌Œ�Ȃ̂ł���Ȃ�*/
	float CalculateBezierLength();
	D3DXVECTOR3 QuadraticBezPoint(float _t);
	D3DXVECTOR3 QuadraticConstantBezPoint(int _divideNum, int _nowCnt);
	void LeftRoadCreate();
	void RightRoadCreate();
	bool CurveAreaCheck(D3DXVECTOR3* _checkPos, int _array);

};
#endif
