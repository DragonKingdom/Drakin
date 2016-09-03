/***
*@file Church.h
*@brief 教会のクラス
*
*/
#ifndef CHURCH_H
#define CHURCH_H

/**教会のコスト*/
#define CHURCH_COST 1000

#include "House.h"
/**
*教会クラス
*
*/
class Church :public House
{
public:
	//コンストラクタ
	Church(D3DXVECTOR3 _housePos, float _angle, int _Type);
	//デストラクタ
	virtual~Church();
	//コントロール関数
	virtual BUILD_STATE Control();
	//描画関数
	virtual void Draw();
	//
	virtual Status	GetMainStatus(){ return Status{ 500.f, 10.f, 1000.f, 0 }; };
};

#endif