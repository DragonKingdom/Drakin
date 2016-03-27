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
	float x;	/*���S���W*/
	float y;	/*���S���W*/
	float z;	/*���S���W*/
	float w;	/*��*/
	float h;	/*����*/
	float angle;	/*�X��*/
	BYTE AreaData;	/*�G���A�̏�ɉ�����������Ă邩*/


};


#endif