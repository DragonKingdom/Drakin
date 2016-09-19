#ifndef DUNGON_H
#define DUNGON_H

class FbxModel;
class ShaderAssist;
class RoadManager;

class Dungon
{
public:

	Dungon(D3DXVECTOR3 _dungonPos, float _angle, int _Type);
	 ~Dungon();
	void Control();
	void Draw();
	D3DXVECTOR3		GetDungonPos();
	void			GetDungonData(std::vector<float>* _pDungonVertexData, std::vector<float>* _pDungonAngleData);
	void            SetBuildPos(D3DXVECTOR3* _BuildPos);
	void            SetAngle(float* _angle);
private:
	D3DXVECTOR3				m_DungonPos;
	float					m_Angle;
	D3DXMATRIX				m_World;	// ワールド変換行列
	ShaderAssist*			m_pShaderAssist;
	Texture					m_Texture;
	D3DXHANDLE m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;
	std::vector<FbxModel*>   m_Model;

};

#endif