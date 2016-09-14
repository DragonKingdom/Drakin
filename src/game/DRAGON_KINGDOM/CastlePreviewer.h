/**
*@file CastlePreviewer.h
*@brief 城のプレビュー表示クラスのヘッダー
*@author haga
*@data 2016/09/10
*/
#ifndef CASTLE_PREVIEWER_H
#define CASTLE_PREVIEWER_H

class FbxModel;

class CastlePreviewer
{
public:
	/**コンストラクタ*/
	CastlePreviewer();
	/**デストラクタ*/
	~CastlePreviewer();

	void SetBuildPos(D3DXVECTOR3* _buildPos);
	void SetAngle(float* _angle);
	void Draw();

private:

	/// 城のを描画する座標*/
	D3DXVECTOR3 m_BuildPos;
	/// 描画する家の角度
	float		m_Angle;
	/// 家のモデルを格納してるクラス
	std::vector<FbxModel*>   m_FbxModel;

};

#endif //CASTLE_PREVIEWER_H

