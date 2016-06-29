#ifndef GROUND_H
#define GROUND_H

class FbxModel;
class FbxFileManager;
class Sun;
class ShaderAssist;

class Ground
{
public:
	Ground(Sun* pSun);
	~Ground();
	void Control();
	void Draw();

private:
	struct CUSTOMVERTEX
	{
		D3DXVECTOR3	pos;
		FLOAT	tu, tv;
	};
	Vertex* m_pVertex;
	LPDIRECT3DDEVICE9 m_pDevice;
	D3DXHANDLE m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;
	FbxModel* m_pGroundModel;
	FbxModel* m_pMountainModel;
	ShaderAssist*		m_pShaderAssist;
	//フォグの色に使うテクスチャ
	Texture m_Texture;
	FbxFileManager* m_pFbxModelManager;
	Sun*			m_pSun;

};
#endif