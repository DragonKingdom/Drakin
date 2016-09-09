/**
*@file Castle.h
*@brief 城クラスのｈ
*@autor haga
*@data 2016/09/09
*/
#ifndef CASTLE_H
#define CASTLE_H

using namespace std;
class FbxModel;
class ShaderAssist;


class Castle
{
public:

	/**
	*城のステータス<br>
	*2016/09/09 ステータスが決まりきっていないため中は耐久度と年数だけ実装
	*/
	struct Status
	{
		int Hp;		//!<耐久度
		int Age;	//!<年齢	
	};

	/**
	*コンストラクタ
	* @param[in] _castlePos 城を建てる座標
	* @param[in] _angle 角度
	*/
	Castle(D3DXVECTOR3 _castlePos, float _angle);
	/**デストラクタ*/
	~Castle();
	/**コントロール関数*/
	void Control();
	/**描画関数*/
	void Draw();
	/**城の位置を取得する関数*/
	D3DXVECTOR3 GetCastlePos(){ return m_CastlePos; }

private:
	std::vector<FbxModel*>				m_Model;			//!<モデルを格納する変数
	D3DXVECTOR3							m_CastlePos;		//!<城の座標
	float								m_Angle;			//!<城の角度
	D3DXMATRIX							m_World;			//!<ワールド変換行列
	Status								m_MainStatus;		//!<城のステータス
	int									m_AgeCount;			//!<年齢をカウントするための変数 (修正予定)

	/**描画関連*/
	ShaderAssist*						m_pShaderAssist;
	Texture								m_Texture;
	D3DXHANDLE							m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;

};


#endif

