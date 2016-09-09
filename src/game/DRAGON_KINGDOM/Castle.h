/**
*@file Castle.h
*@brief ��N���X�̂�
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
	*��̃X�e�[�^�X<br>
	*2016/09/09 �X�e�[�^�X�����܂肫���Ă��Ȃ����ߒ��͑ϋv�x�ƔN����������
	*/
	struct Status
	{
		int Hp;		//!<�ϋv�x
		int Age;	//!<�N��	
	};

	/**
	*�R���X�g���N�^
	* @param[in] _castlePos ������Ă���W
	* @param[in] _angle �p�x
	*/
	Castle(D3DXVECTOR3 _castlePos, float _angle);
	/**�f�X�g���N�^*/
	~Castle();
	/**�R���g���[���֐�*/
	void Control();
	/**�`��֐�*/
	void Draw();
	/**��̈ʒu���擾����֐�*/
	D3DXVECTOR3 GetCastlePos(){ return m_CastlePos; }

private:
	std::vector<FbxModel*>				m_Model;			//!<���f�����i�[����ϐ�
	D3DXVECTOR3							m_CastlePos;		//!<��̍��W
	float								m_Angle;			//!<��̊p�x
	D3DXMATRIX							m_World;			//!<���[���h�ϊ��s��
	Status								m_MainStatus;		//!<��̃X�e�[�^�X
	int									m_AgeCount;			//!<�N����J�E���g���邽�߂̕ϐ� (�C���\��)

	/**�`��֘A*/
	ShaderAssist*						m_pShaderAssist;
	Texture								m_Texture;
	D3DXHANDLE							m_LightDir, m_Ambient, m_CLUTTU, m_FogColor, m_Param1, m_Param2;

};


#endif

