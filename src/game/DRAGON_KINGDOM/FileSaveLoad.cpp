#include "FileSaveLoad.h"
#include <Windows.h>

FileSaveLoad::FileSaveLoad()
{
}

FileSaveLoad::~FileSaveLoad()
{
}


bool FileSaveLoad::FileLoadInit(char* _pFileName)
{
	// �t�@�C�����J��
	fopen_s(&m_pFile, _pFileName, "r");

	// �t�@�C���̃T�C�Y���擾����
	fseek(m_pFile, 0, SEEK_END);
	m_fileSize = ftell(m_pFile);
	fseek(m_pFile, 0, SEEK_SET);

	// �t�@�C�����̕����̒������m��
	m_pBuffer = new char[m_fileSize];
	m_pTmpBuffer = new char[m_fileSize];
	m_pGroupBuffer = new char[m_fileSize];
	ZeroMemory(m_pBuffer, m_fileSize);
	ZeroMemory(m_pTmpBuffer, m_fileSize);
	ZeroMemory(m_pGroupBuffer, m_fileSize);

	// �ǂݍ���
	fread(m_pBuffer, m_fileSize, 1, m_pFile);



	return true;
}

bool FileSaveLoad::FileLoadEnd()
{
	// �j��
	delete[] m_pGroupBuffer;
	delete[] m_pTmpBuffer;
	delete[] m_pBuffer;

	//������
	m_fileSize = 0;

	// �t�@�C�������
	fclose(m_pFile);
	m_pFile = NULL;

	return true;
}

bool FileSaveLoad::StepGroup(char* _pGroupName)
{
	// �t�@�C�����̃O���[�v�������Ă�������̕�������i�[
	char* StrBuffer = strstr(m_pBuffer, _pGroupName);
	char* context;
	strcpy_s(m_pTmpBuffer, m_fileSize, StrBuffer);

	// �O���[�v�̓�����K�܂ł̕�������i�[
	strcpy_s(m_pGroupBuffer, m_fileSize, strtok_s(m_pTmpBuffer, ";", &context));


	return true;
}

bool FileSaveLoad::StepinGroup(char* _pGroupName)
{
	// �O���[�v���̃O���[�v�������Ă�������̕�������i�[
	char* StrBuffer = strstr(m_pGroupBuffer, _pGroupName);
	char* context;
	strcpy_s(m_pTmpBuffer, m_fileSize, StrBuffer);

	// �O���[�v�̓�����K�܂ł̕�������i�[
	strcpy_s(m_pGroupBuffer, m_fileSize, strtok_s(m_pTmpBuffer, ";", &context));


	return true;
}

char* FileSaveLoad::GetCheckGroupName()
{
	char* context;
	strcpy_s(m_pTmpBuffer, m_fileSize, m_pGroupBuffer);

	// �O���[�v�̓�����K�܂ł̕�������i�[
	strtok_s(m_pTmpBuffer, "{", &context);

	return m_pTmpBuffer;
}

bool FileSaveLoad::GetGroupMember(std::vector<int>* _pGroupMemberData)
{
	// �O���[�v������tmp�o�b�t�@�ɕ�������ڂ�
	char* Str;
	char* context;
	strcpy_s(m_pTmpBuffer, m_fileSize, m_pGroupBuffer);

	// �ŏ��̃O���[�v���͖���
	Str = strtok_s(m_pTmpBuffer, "{},", &context);

	while (1)
	{
		Str = strtok_s(NULL, "{},", &context);
		
		if (Str == NULL)
		{
			// NULL�Ȃ�f�[�^�͂Ȃ��̂Ń��[�v���甲����
			break;
		}
		else
		{
			// NULL����Ȃ���΃f�[�^������̂Œǉ�
			_pGroupMemberData->push_back(atoi(Str));
		}
	}

	return true;
}

bool FileSaveLoad::GetGroupMember(std::vector<float>* _pGroupMemberData)
{
	// �O���[�v������tmp�o�b�t�@�ɕ�������ڂ�
	char* Str;
	char* context;
	strcpy_s(m_pTmpBuffer, m_fileSize, m_pGroupBuffer);

	// �ŏ��̃O���[�v���͖���
	Str = strtok_s(m_pTmpBuffer, "{},", &context);

	while (1)
	{
		Str = strtok_s(NULL, "{},", &context);

		if (Str == NULL)
		{
			// NULL�Ȃ�f�[�^�͂Ȃ��̂Ń��[�v���甲����
			break;
		}
		else
		{
			// NULL����Ȃ���΃f�[�^������̂Œǉ�
			_pGroupMemberData->push_back(static_cast<float>(atof(Str)));
		}
	}

	return true;
}

bool FileSaveLoad::GetGroupMember(std::vector<bool>* _pGroupMemberData)
{
	// �O���[�v������tmp�o�b�t�@�ɕ�������ڂ�
	char* Str;
	char* context;
	strcpy_s(m_pTmpBuffer, m_fileSize, m_pGroupBuffer);

	// �ŏ��̃O���[�v���͖���
	Str = strtok_s(m_pTmpBuffer, "{},", &context);

	while (1)
	{
		Str = strtok_s(NULL, "{},", &context);

		if (Str == NULL)
		{
			// NULL�Ȃ�f�[�^�͂Ȃ��̂Ń��[�v���甲����
			break;
		}
		else
		{
			// NULL����Ȃ���΃f�[�^������̂Œǉ�
			if (atoi(Str) == 0)
			{
				_pGroupMemberData->push_back(false);
			}
			else
			{
				_pGroupMemberData->push_back(true);
			}
		}
	}

	return true;
}

bool FileSaveLoad::GetGroupMember(std::vector<D3DXVECTOR3>* _pGroupMemberData)
{
	///@todo ������

	return true;
}



bool FileSaveLoad::FileSaveInit(char* _pFileName, int _FileSize)
{
	fopen_s(&m_pFile, _pFileName, "w");

	m_pBuffer = new char[_FileSize];
	m_pTmpBuffer = new char[_FileSize];
	m_pGroupBuffer = new char[_FileSize];
	ZeroMemory(m_pBuffer, _FileSize);
	ZeroMemory(m_pTmpBuffer, _FileSize);
	ZeroMemory(m_pGroupBuffer, _FileSize);

	m_fileSize = _FileSize;

	return true;
}

bool FileSaveLoad::FileSaveEnd()
{

	// �j��
	delete[] m_pGroupBuffer;
	delete[] m_pTmpBuffer;
	delete[] m_pBuffer;

	//������
	m_fileSize = 0;

	// �t�@�C�������
	fclose(m_pFile);
	m_pFile = NULL;

	return true;
}

bool FileSaveLoad::CreateGroup(char* _pGroupName, std::vector<int>* _pGroupMemberData)
{
	// �f�[�^���i�[����
	char DataBuffer[10];

	// �O���[�v���\������
	std::string Str = m_pBuffer;
	Str = Str + _pGroupName + "{";
	
	for (unsigned int i = 0; i < _pGroupMemberData->size(); i++)
	{
		sprintf_s(DataBuffer, sizeof(DataBuffer), "%d", (*_pGroupMemberData)[i]);
		Str = Str + DataBuffer + ",";
	}

	Str = Str + "};\n";

	strcpy_s(m_pBuffer, m_fileSize, Str.c_str());


	return true;
}


bool FileSaveLoad::FileSave()
{
	fprintf_s(m_pFile, m_pBuffer);

	return true;
}

