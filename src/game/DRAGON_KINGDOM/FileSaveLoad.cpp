#include "FileSaveLoad.h"
#include <Windows.h>

FileSaveLoad::FileSaveLoad():
isFileLoadMode(false),
isFileSaveMode(false)
{
}

FileSaveLoad::~FileSaveLoad()
{
}


bool FileSaveLoad::FileLoadInit(char* _pFileName)
{
	//ファイル読み込みまたは書き込みモードになってるなら処理を返す
	if (isFileLoadMode == true || isFileSaveMode == true)
	{
		return false;
	}

	// ファイルを開く
	fopen_s(&m_pFile, _pFileName, "r");
	if (m_pFile == NULL)
	{
		return false;
	}

	// ファイルのサイズを取得する
	fseek(m_pFile, 0, SEEK_END);
	m_fileSize = ftell(m_pFile);
	fseek(m_pFile, 0, SEEK_SET);

	// ファイル内の文字の長さ分確保
	m_pBuffer = new char[m_fileSize];
	m_pTmpBuffer = new char[m_fileSize];
	m_pGroupBuffer = new char[m_fileSize];
	ZeroMemory(m_pBuffer, m_fileSize);
	ZeroMemory(m_pTmpBuffer, m_fileSize);
	ZeroMemory(m_pGroupBuffer, m_fileSize);

	// 読み込み
	fread(m_pBuffer, m_fileSize, 1, m_pFile);

	// ファイル読み込み状態のフラグを立てる
	isFileLoadMode = true;

	return true;
}

bool FileSaveLoad::FileLoadEnd()
{
	//ファイル読み込みモードになってないなら処理を返す
	if (isFileLoadMode == false)
	{
		return false;
	}

	// 破棄
	delete[] m_pGroupBuffer;
	delete[] m_pTmpBuffer;
	delete[] m_pBuffer;

	// サイズ初期化
	m_fileSize = 0;

	// ファイルを閉じる
	fclose(m_pFile);
	m_pFile = NULL;

	// フラグを落とす
	isFileLoadMode = false;

	return true;
}

bool FileSaveLoad::StepGroup(char* _pGroupName)
{
	//ファイル読み込みモードになってないなら処理を返す
	if (isFileLoadMode == false)
	{
		return false;
	}

	// ファイル内のグループを見つけてそこからの文字列を格納
	char* StrBuffer = strstr(m_pBuffer, _pGroupName);
	char* context;
	strcpy_s(m_pTmpBuffer, m_fileSize, StrBuffer);

	// グループの頭から尻までの文字列を格納
	strcpy_s(m_pGroupBuffer, m_fileSize, strtok_s(m_pTmpBuffer, ";", &context));


	return true;
}

bool FileSaveLoad::StepinGroup(char* _pGroupName)
{
	//ファイル読み込みモードになってないなら処理を返す
	if (isFileLoadMode == false)
	{
		return false;
	}

	// グループ内のグループを見つけてそこからの文字列を格納
	char* StrBuffer = strstr(m_pGroupBuffer, _pGroupName);
	char* context;
	strcpy_s(m_pTmpBuffer, m_fileSize, StrBuffer);

	// グループの頭から尻までの文字列を格納
	strcpy_s(m_pGroupBuffer, m_fileSize, strtok_s(m_pTmpBuffer, ";", &context));


	return true;
}

char* FileSaveLoad::GetCheckGroupName()
{
	//ファイル読み込みモードになってないなら処理を返す
	if (isFileLoadMode == false)
	{
		return false;
	}

	char* context;
	strcpy_s(m_pTmpBuffer, m_fileSize, m_pGroupBuffer);

	// グループの頭から尻までの文字列を格納
	strtok_s(m_pTmpBuffer, "{", &context);

	return m_pTmpBuffer;
}

bool FileSaveLoad::GetGroupMember(std::vector<int>* _pGroupMemberData)
{
	//ファイル読み込みモードになってないなら処理を返す
	if (isFileLoadMode == false)
	{
		return false;
	}

	// グループ名からtmpバッファに文字列を移す
	char* Str;
	char* context;
	strcpy_s(m_pTmpBuffer, m_fileSize, m_pGroupBuffer);

	// 最初のグループ名は無視
	Str = strtok_s(m_pTmpBuffer, "{},", &context);

	while (1)
	{
		Str = strtok_s(NULL, "{},", &context);
		
		if (Str == NULL)
		{
			// NULLならデータはないのでループから抜ける
			break;
		}
		else
		{
			// NULLじゃなければデータがあるので追加
			_pGroupMemberData->push_back(atoi(Str));
		}
	}

	return true;
}

bool FileSaveLoad::GetGroupMember(std::vector<float>* _pGroupMemberData)
{
	//ファイル読み込みモードになってないなら処理を返す
	if (isFileLoadMode == false)
	{
		return false;
	}

	// グループ名からtmpバッファに文字列を移す
	char* Str;
	char* context;
	strcpy_s(m_pTmpBuffer, m_fileSize, m_pGroupBuffer);

	// 最初のグループ名は無視
	Str = strtok_s(m_pTmpBuffer, "{},", &context);

	while (1)
	{
		Str = strtok_s(NULL, "{},", &context);

		if (Str == NULL)
		{
			// NULLならデータはないのでループから抜ける
			break;
		}
		else
		{
			// NULLじゃなければデータがあるので追加
			_pGroupMemberData->push_back(static_cast<float>(atof(Str)));
		}
	}

	return true;
}

bool FileSaveLoad::GetGroupMember(std::vector<bool>* _pGroupMemberData)
{
	//ファイル読み込みモードになってないなら処理を返す
	if (isFileLoadMode == false)
	{
		return false;
	}

	// グループ名からtmpバッファに文字列を移す
	char* Str;
	char* context;
	strcpy_s(m_pTmpBuffer, m_fileSize, m_pGroupBuffer);

	// 最初のグループ名は無視
	Str = strtok_s(m_pTmpBuffer, "{},", &context);

	while (1)
	{
		Str = strtok_s(NULL, "{},", &context);

		if (Str == NULL)
		{
			// NULLならデータはないのでループから抜ける
			break;
		}
		else
		{
			// NULLじゃなければデータがあるので追加
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

bool FileSaveLoad::GetGroupMember(std::vector<std::string>* _pGroupMemberData)
{
	//ファイル読み込みモードになってないなら処理を返す
	if (isFileLoadMode == false)
	{
		return false;
	}

	// グループ名からtmpバッファに文字列を移す
	char* Str;
	char* context;
	strcpy_s(m_pTmpBuffer, m_fileSize, m_pGroupBuffer);

	// 最初のグループ名は無視
	Str = strtok_s(m_pTmpBuffer, "{},", &context);
	
	while (1)
	{
		Str = strtok_s(NULL, "{},", &context);

		if (Str == NULL)
		{
			// NULLならデータはないのでループから抜ける
			break;
		}
		else
		{
			// NULLじゃなければデータがあるので追加
			_pGroupMemberData->push_back(Str);
		}
	}

	return true;
}

bool FileSaveLoad::GetGroupMember(std::vector<D3DXVECTOR3>* _pGroupMemberData)
{
	//ファイル読み込みモードになってないなら処理を返す
	if (isFileLoadMode == false)
	{
		return false;
	}

	///@todo 未実装

	return true;
}



bool FileSaveLoad::FileSaveInit(char* _pFileName, int _FileSize)
{
	//ファイル読み込みまたは書き込みモードになってるなら処理を返す
	if (isFileLoadMode == true || isFileSaveMode == true)
	{
		return false;
	}

	fopen_s(&m_pFile, _pFileName, "w");

	m_pBuffer = new char[_FileSize];
	m_pTmpBuffer = new char[_FileSize];
	m_pGroupBuffer = new char[_FileSize];
	ZeroMemory(m_pBuffer, _FileSize);
	ZeroMemory(m_pTmpBuffer, _FileSize);
	ZeroMemory(m_pGroupBuffer, _FileSize);

	m_fileSize = _FileSize;

	isFileSaveMode = true;

	return true;
}

bool FileSaveLoad::FileSaveEnd()
{
	if (isFileSaveMode == false)
	{
		return false;
	}

	// 破棄
	delete[] m_pGroupBuffer;
	delete[] m_pTmpBuffer;
	delete[] m_pBuffer;

	//初期化
	m_fileSize = 0;

	// ファイルを閉じる
	fclose(m_pFile);
	m_pFile = NULL;

	isFileSaveMode = false;

	return true;
}

bool FileSaveLoad::CreateGroup(char* _pGroupName, std::vector<int>* _pGroupMemberData)
{
	if (isFileSaveMode == false)
	{
		return false;
	}

	// データを格納する
	char DataBuffer[30];

	// グループを構成する
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

bool FileSaveLoad::CreateGroup(char* _pGroupName, std::vector<std::string>* _pGroupMemberData)
{
	if (isFileSaveMode == false)
	{
		return false;
	}

	// データを格納する
	char DataBuffer[30];

	// グループを構成する
	std::string Str = m_pBuffer;
	Str = Str + _pGroupName + "{";

	for (unsigned int i = 0; i < _pGroupMemberData->size(); i++)
	{
		strcpy_s(DataBuffer, sizeof(DataBuffer), (*_pGroupMemberData)[i].c_str());
		Str = Str + DataBuffer + ",";
	}

	Str = Str + "};\n";

	strcpy_s(m_pBuffer, m_fileSize, Str.c_str());


	return true;
}

bool FileSaveLoad::FileSave()
{
	if (isFileSaveMode == false)
	{
		return false;
	}

	fprintf_s(m_pFile, m_pBuffer);

	return true;
}

