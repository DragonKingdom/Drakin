#ifndef CLICKPOSCONVERTER_H
#define CLICKPOSCONVERTER_H

#include "CameraController.h"

class ClickPosConverter
{
public:
	ClickPosConverter(CameraController*);
	~ClickPosConverter();
	void Convert(D3DXVECTOR3*, float, float, float,D3DXMATRIX* ,D3DXMATRIX*);
	D3DXVECTOR3* ConvertForLoad(D3DXVECTOR3*,int,int);
private:
	CameraController* m_pCameraController;
};

#endif