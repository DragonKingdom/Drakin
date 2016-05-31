#ifndef GROUND_H
#define GROUND_H

class FbxModel;
class LSS;
class FbxFileManager;
class Sun;
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
	FbxModel* m_pGroundModel;
	FbxModel* m_pMountainModel;


	LSS* m_pLSS;
	FbxFileManager* m_pFbxModelManager;
	Sun*			m_pSun;

};
#endif