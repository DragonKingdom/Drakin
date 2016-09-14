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
#define CLIENT_WIDTH  1600
#define CLIENT_HEIGHT  900

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
	SCENE_GAME,			// ���߂����I�����ăQ�[���ɓ������Ƃ�
	SCENE_CONTINUE_GAME,	// ���������I�����ăQ�[���ɓ������Ƃ�
	SCENE_RESULT,
	SCENE_ENDING,
	FIN
};

#define WORLD_END_PLUS 33000.f
#define WORLD_END_MINUS -33000.f
#define ROAD_W_SIZE 500.f
#define ROAD_H_SIZE 500.f
#define BULDAREA_LINK 5


/// �Q�[���V�[���̏��
enum GAMESCENE_STATE
{
	GAMESCENE_NORMAL,
	GAMESCENE_PAUSE,
};

enum BUILD_STATE
{
	BUILD_NONE,
	BUILD_PRIVATEHOUSE_RANDOM,
	BUILD_PRIVATEHOUSE_RED,
	BUILD_PRIVATEHOUSE_BLUE,
	BUILD_PRIVATEHOUSE_YELLOW,
	BUILD_PRIVATEHOUSE_POOR,
	BUILD_PRIVATEHOUSE_RICH,
	BUILD_BLACKSMITH,
	BUILD_CHURCH,
	BUILD_CASTLE,
	BUILD_ROAD
};

namespace BUILDAREAMANAGER_ENUM
{
	enum STATE
	{
		START_POS_SET,
		END_POS_SET,
		CREATE
	};
	enum BUILD_TYPE
	{
		NORMAL,
		CURVE
	};
}

namespace ROADMANAGER_ENUM
{
	enum STATE
	{
		START_POS_SET,
		END_POS_SET,
		CREATE
	};

	enum BUILD_TYPE
	{
		NORMAL,
		CURVE
	};
}

#endif // COMMONDECLARATION_H
