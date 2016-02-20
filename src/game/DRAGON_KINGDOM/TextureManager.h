#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <vector>
#include <map>
#include <texture.h>

class TextureManager
{
public:
	/// Logo�V�[���Ŏg�p����e�N�X�`����ID
	enum LOGO_SCENE_TEX
	{
		TEAM_LOGO
	};
	/// Title�V�[���Ŏg�p����e�N�X�`����ID
	enum TITLE_SCENE_TEX
	{
		TITLE,
		BG,
		MENU,
	};
	/// Game�V�[���Ŏg�p����e�N�X�`����ID
	enum GAME_SCENE_TEX
	{
		TELOP,
		WINDOW,
		UI,
	};
private:
	TextureManager();

	/// �V�[��ID�ƁA���̃V�[���Ń��[�h����t�@�C�����̘A�z�z��
	std::map<SceneID, const wchar_t**> m_loadFileNameMap;

	std::vector<Texture> m_texList;	///< �ǂݍ��܂�Ă���e�N�X�`�����
public:
	static TextureManager& getInstance() 
	{
		static TextureManager instance;
		return instance;
	}
	/**
	 * �e�N�X�`���̃��[�h
	 * @param _sceneID �g�p����摜ID
	 */
	void Load(SceneID _sceneID);
	/**
	 * �e�N�X�`���̊J��
	 */
	void Release();
	/**
	 * �e�N�X�`���擾
	 * @param	_no �e�N�X�`���ԍ�
	 * @return �e�N�X�`�����
	 */
	const Texture& Get(int _no);	// �摜�擾
};

#endif
