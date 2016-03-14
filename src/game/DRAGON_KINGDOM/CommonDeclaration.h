/**
 * @file   CommonDeclaration.h
 * @brief  �Q�[���S�̂Ŏg�p�����}�N���萔�Aenum�Astruct����Z�߂��t�@�C��
 *
 * @author matsumura
 */

#ifndef COMMONDECLARATION_H
#define COMMONDECLARATION_H

/////////////////////////////////////////////////////////
// define
/////////////////////////////////////////////////////////
#define CLIENT_WIDTH  1263
#define CLIENT_HEIGHT  710

/// �R�s�[�R���X�g���N�^��=���Z�q�֐��𖳌��ɂ���}�N��
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)


/////////////////////////////////////////////////////////
// enum
/////////////////////////////////////////////////////////

/// �V�[���ԍ�
enum SceneID 
{
	SCENE_LOGO,
	SCENE_OPENING,
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_ENDING,
	FIN
};

/// �Q�[���V�[���̏��
enum GAMESCENE_STATE
{
	GAMESCENE_NORMAL,
	GAMESCENE_PAUSE,
};

//���̂�������
enum GAME_STATE
{
	STATE_NONE,
	STATE_BUILD_ROAD,
	STATE_BUILD_HOUSE,
};

enum BUILD_STATE{
	BUILD_HOUSE,
	BUILD_ROAD
};


#endif // COMMONDECLARATION_H
