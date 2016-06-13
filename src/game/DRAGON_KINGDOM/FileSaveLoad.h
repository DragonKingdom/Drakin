#ifndef FILESAVELOAD_H
#define FILESAVELOAD_H

#include <stdio.h>
#include <vector>
#include <string>
#include <d3dx9.h>

#define LARGE_SAVE_FILE 50000
#define NORMAL_SAVE_FILE 5000
#define SMALL_SAVE_FILE 500


/// @todo �O���[�v���ɃO���[�v���쐬����@�\�͖�����


/**
 * �Z�[�u�f�[�^��ǂݏ�������N���X
 */
class FileSaveLoad
{
public:
	FileSaveLoad();
	~FileSaveLoad();
	
	/**
	 * �t�@�C����ǂݍ���
	 * @param[in] _pFileName �ǂݍ��ރt�@�C���̖��O
	 * @return ����������:true ���s������:false
	 */
	bool FileLoadInit(char* _pFileName);

	/**
	 * �t�@�C���ǂݍ��݂̏I��
	 * @return ����������:true ���s������:false
	 */
	bool FileLoadEnd();

	/**
	 * �O���[�v���`�F�b�N����
	 * @param[in] _pGroupName �`�F�b�N����O���[�v�̖��O
	 * @return ����������:true ���s������:false
	 */
	bool StepGroup(char* _pGroupName);

	/**
	* ���݃`�F�b�N���Ă���O���[�v���̃O���[�v���`�F�b�N����
	* @param[in] _pGroupName �`�F�b�N����O���[�v�̖��O
	* @return ����������:true ���s������:false
	*/
	bool StepinGroup(char* _pGroupName);

	/**
	 * ���݃`�F�b�N���Ă���O���[�v���擾����
	 * @return ���݃`�F�b�N���Ă���O���[�v�̖��O
	 */
	char* GetCheckGroupName();

	/**
	 * �`�F�b�N���Ă���O���[�v�̃����o���擾����
	 * @param[out] _pGroupMemberData �f�[�^���i�[����vector�̃A�h���X
	 * @return ����������:true ���s������:false
	 */
	bool GetGroupMember(std::vector<int>* _pGroupMemberData);

	/**
	* �`�F�b�N���Ă���O���[�v�̃����o���擾����
	* @param[out] _pGroupMemberData �f�[�^���i�[����vector�̃A�h���X
	* @return ����������:true ���s������:false
	*/
	bool GetGroupMember(std::vector<float>* _pGroupMemberData);

	/**
	* �`�F�b�N���Ă���O���[�v�̃����o���擾����
	* @param[out] _pGroupMemberData �f�[�^���i�[����vector�̃A�h���X
	* @return ����������:true ���s������:false
	*/
	bool GetGroupMember(std::vector<bool>* _pGroupMemberData);

	/**
	* �`�F�b�N���Ă���O���[�v�̃����o���擾����
	* @param[out] _pGroupMemberData �f�[�^���i�[����vector�̃A�h���X
	* @return ����������:true ���s������:false
	*/
	bool GetGroupMember(std::vector<std::string>* _pGroupMemberData);

	/**
	* �`�F�b�N���Ă���O���[�v�̃����o���擾����
	* @param[out] _pGroupMemberData �f�[�^���i�[����vector�̃A�h���X
	* @return ����������:true ���s������:false
	*/
	bool GetGroupMember(std::vector<D3DXVECTOR3>* _pGroupMemberData);



	/**
	 * �t�@�C������������
	 * @param[in] _pFileName �������ރt�@�C���̖��O
	 * @param[in] _FileSize �������ރt�@�C���̍ő�T�C�Y(�o�C�g�w��)
	 * @return ����������:true ���s������:false
	 */
	bool FileSaveInit(char* _pFileName, int _FileSize);

	/**
	 * �t�@�C���������݂̏I��
	 * @return ����������:true ���s������:false
	 */
	bool FileSaveEnd();

	/**
	 * �O���[�v���쐬����
	 * @param[in] _pGroupName �쐬����O���[�v�̖��O
	 * @param[in] �Z�b�g����f�[�^��������vector�̃A�h���X
	 * @return ����������:true ���s������:false
	 */
	bool CreateGroup(char* _pGroupName, std::vector<int>* _pGroupMemberData);

	/**
	* �O���[�v���쐬����
	* @param[in] _pGroupName �쐬����O���[�v�̖��O
	* @param[in] �Z�b�g����f�[�^��������vector�̃A�h���X
	* @return ����������:true ���s������:false
	*/
	bool CreateGroup(char* _pGroupName, std::vector<float>* _pGroupMemberData);

	/**
	* �O���[�v���쐬����
	* @param[in] _pGroupName �쐬����O���[�v�̖��O
	* @param[in] �Z�b�g����f�[�^��������vector�̃A�h���X
	* @return ����������:true ���s������:false
	*/
	bool CreateGroup(char* _pGroupName, std::vector<std::string>* _pGroupMemberData);

	/**
	 * �t�@�C�����Z�[�u����
	 * @return ����������:true ���s������:false
	 */
	bool FileSave();

private:
	// �t�@�C���|�C���^
	FILE*	m_pFile;

	// �t�@�C���̃T�C�Y���i�[����
	long	m_fileSize;

	// �t�@�C���S�̂̕�������i�[����
	char*	m_pBuffer;

	// �ꎞ�I�ɕ�������i�[����
	char*	m_pTmpBuffer;

	// ���݃`�F�b�N���Ă�O���[�v���i�[�����
	char*   m_pGroupBuffer;

	// �t�@�C���ǂݍ��݃��[�h�ɂȂ��Ă邩�̃t���O
	bool isFileLoadMode;

	// �t�@�C���������݃��[�h�ɂȂ��Ă邩�̃t���O
	bool isFileSaveMode;

};



#endif