#ifndef EFFECT_H
#define EFFECT_H
#include <vector>
#include "FbxFileManager.h"
#include "FbxModel.h"

class Effect
{
public:
	Effect(char* _fileName,float _scale,int _texNum,int _playSpeed);
	~Effect();
	void Control();
	void Draw();
	void PushTexture(char* _str);
	
	void		SetPos(D3DXVECTOR3 _pos){ m_Pos = _pos; };
	D3DXVECTOR3 GetPos(){ return m_Pos; };
	int			GetTextureNum(){ return m_MaxTextureNum; };
	void		SetScale(float _scale){ m_Scale = _scale; };
	void		SetAngle(float _angle){ m_Angle = _angle; };
private:
	std::vector<FbxModel*> m_Model;
	D3DXVECTOR3			   m_Pos;
	std::vector<Texture*>  m_pTextureArray;
	int					   m_MaxTextureNum;
	int					   m_TextureNum;
	int					   m_Time;
	int					   m_PlaySpeed; //何フレームでテクスチャが切り替わるか
	float				   m_Angle;
	float				   m_Scale;
	D3DXMATRIX			   m_World;
};
#endif