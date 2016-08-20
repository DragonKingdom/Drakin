#ifndef HOUSE_H
#define HOUSE_H

enum HouseType
{
	RED_HOUSE,
	BLUE_HOUSE,
	YELLOW_HOUSE,
	POOR_HOUSE,
	RICH_HOUSE,
	NORMAL_HOUSE,
	HOUSE_TYPE_MAX
};

class FbxModel;
class ShaderAssist;

class House
{
public:
	House(D3DXVECTOR3 _housePos, float _angle, HouseType _Type);
	virtual ~House();
	virtual void Draw();
	void GetHouseData(std::vector<float>* _pHouseVertexData, std::vector<float>* _pHouseAngleData, std::vector<int>* _pHouseStatus);

protected:
	std::vector<FbxModel*>	m_Model;
	D3DXVECTOR3				m_HousePos;
	float					m_Angle;
	D3DXMATRIX				m_World;
	HouseType				m_Type;
	ShaderAssist*			m_pShaderAssist;
	Texture					m_FogTexture;

	D3DXHANDLE m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;

private:
	
};

#endif