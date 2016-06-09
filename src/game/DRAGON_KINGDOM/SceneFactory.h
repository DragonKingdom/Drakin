/**
 * @file   SceneFactory.h
 * @brief  �V�[���t�@�N�g���[�N���X�w�b�_
 *
 * @author matsumura
 */

#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H

class Scene;
class FileSaveLoad;

/// �V�[���t�@�N�g���[�N���X
/**
 * �e�V�[���𐶐�����t�@�N�g���[�N���X
 * @attention �{�N���X�̓V���O���g���N���X�Ȃ̂�new�ł��Ȃ�
 */
class SceneFactory
{
public:
	/// �t�@�N�g���[�̃C���X�^���X�擾
	/**
	 * new�����A�{���\�b�h�ŃC���X�^���X���擾���邱��
	 * @return �t�@�N�g���[�̃C���X�^���X
	 */
	static SceneFactory& Instance() {
		static SceneFactory instance;
		return instance;
	}

	/// �V�[���N���X�̐���
	/**
	 * @param _sceneID ��������N���X�̃V�[��ID
	 * @return �V�[���N���X�̃C���X�^���X
	 */
	Scene* CreateScene(SceneID _sceneID);

	/*
	 * ������
	 */
	void Init(FileSaveLoad* _pFileSaveLoad)
	{
		m_pFileSaveLoad = _pFileSaveLoad;
	}

	virtual ~SceneFactory() {}

private:
	SceneFactory() {}
	DISALLOW_COPY_AND_ASSIGN(SceneFactory);
	FileSaveLoad* m_pFileSaveLoad;

};

#endif // SCENEFACTORY_H
