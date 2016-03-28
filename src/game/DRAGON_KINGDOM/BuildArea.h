#ifndef BUILDAREA_H
#define BUILDAREA_H


class BuildArea
{
public:
	BuildArea();
	~BuildArea();
	void Draw();

private:
	Vertex      m_Vertex;
	Texture		m_Texture;
	D3DXVECTOR3 m_RoadStartPos;	/*�Ή����铹�̎n�_*/
	D3DXVECTOR3 m_RoadEndPos;	/*�Ή����铹�̏I�_*/
	float m_x;	/*���S���W*/
	float m_y;	/*���S���W*/
	float m_z;	/*���S���W*/
	float m_w;	/*��*/
	float m_h;	/*����*/
	float m_angle;	/*�X��*/
	BYTE  m_AreaData;	/*�G���A�̏�ɉ�����������Ă邩*/


};


#endif