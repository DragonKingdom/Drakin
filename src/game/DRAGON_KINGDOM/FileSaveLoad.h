#ifndef FILESAVELOAD_H
#define FILESAVELOAD_H

#include <stdio.h>
#include <vector>
#include <string>
#include <d3dx9.h>

#define LARGE_SAVE_FILE 50000
#define NORMAL_SAVE_FILE 5000
#define SMALL_SAVE_FILE 500


/// @todo グループ内にグループを作成する機能は未実装


/**
 * セーブデータを読み書きするクラス
 */
class FileSaveLoad
{
public:
	FileSaveLoad();
	~FileSaveLoad();
	
	/**
	 * ファイルを読み込む
	 * @param[in] _pFileName 読み込むファイルの名前
	 * @return 成功したら:true 失敗したら:false
	 */
	bool FileLoadInit(char* _pFileName);

	/**
	 * ファイル読み込みの終了
	 * @return 成功したら:true 失敗したら:false
	 */
	bool FileLoadEnd();

	/**
	 * グループをチェックする
	 * @param[in] _pGroupName チェックするグループの名前
	 * @return 成功したら:true 失敗したら:false
	 */
	bool StepGroup(char* _pGroupName);

	/**
	* 現在チェックしているグループ内のグループをチェックする
	* @param[in] _pGroupName チェックするグループの名前
	* @return 成功したら:true 失敗したら:false
	*/
	bool StepinGroup(char* _pGroupName);

	/**
	 * 現在チェックしているグループを取得する
	 * @return 現在チェックしているグループの名前
	 */
	char* GetCheckGroupName();

	/**
	 * チェックしているグループのメンバを取得する
	 * @param[out] _pGroupMemberData データを格納するvectorのアドレス
	 * @return 成功したら:true 失敗したら:false
	 */
	bool GetGroupMember(std::vector<int>* _pGroupMemberData);

	/**
	* チェックしているグループのメンバを取得する
	* @param[out] _pGroupMemberData データを格納するvectorのアドレス
	* @return 成功したら:true 失敗したら:false
	*/
	bool GetGroupMember(std::vector<float>* _pGroupMemberData);

	/**
	* チェックしているグループのメンバを取得する
	* @param[out] _pGroupMemberData データを格納するvectorのアドレス
	* @return 成功したら:true 失敗したら:false
	*/
	bool GetGroupMember(std::vector<bool>* _pGroupMemberData);

	/**
	* チェックしているグループのメンバを取得する
	* @param[out] _pGroupMemberData データを格納するvectorのアドレス
	* @return 成功したら:true 失敗したら:false
	*/
	bool GetGroupMember(std::vector<std::string>* _pGroupMemberData);

	/**
	* チェックしているグループのメンバを取得する
	* @param[out] _pGroupMemberData データを格納するvectorのアドレス
	* @return 成功したら:true 失敗したら:false
	*/
	bool GetGroupMember(std::vector<D3DXVECTOR3>* _pGroupMemberData);



	/**
	 * ファイルを書き込む
	 * @param[in] _pFileName 書き込むファイルの名前
	 * @param[in] _FileSize 書き込むファイルの最大サイズ(バイト指定)
	 * @return 成功したら:true 失敗したら:false
	 */
	bool FileSaveInit(char* _pFileName, int _FileSize);

	/**
	 * ファイル書き込みの終了
	 * @return 成功したら:true 失敗したら:false
	 */
	bool FileSaveEnd();

	/**
	 * グループを作成する
	 * @param[in] _pGroupName 作成するグループの名前
	 * @param[in] セットするデータが入ったvectorのアドレス
	 * @return 成功したら:true 失敗したら:false
	 */
	bool CreateGroup(char* _pGroupName, std::vector<int>* _pGroupMemberData);

	/**
	* グループを作成する
	* @param[in] _pGroupName 作成するグループの名前
	* @param[in] セットするデータが入ったvectorのアドレス
	* @return 成功したら:true 失敗したら:false
	*/
	bool CreateGroup(char* _pGroupName, std::vector<float>* _pGroupMemberData);

	/**
	* グループを作成する
	* @param[in] _pGroupName 作成するグループの名前
	* @param[in] セットするデータが入ったvectorのアドレス
	* @return 成功したら:true 失敗したら:false
	*/
	bool CreateGroup(char* _pGroupName, std::vector<std::string>* _pGroupMemberData);

	/**
	 * ファイルをセーブする
	 * @return 成功したら:true 失敗したら:false
	 */
	bool FileSave();

private:
	// ファイルポインタ
	FILE*	m_pFile;

	// ファイルのサイズを格納する
	long	m_fileSize;

	// ファイル全体の文字列を格納する
	char*	m_pBuffer;

	// 一時的に文字列を格納する
	char*	m_pTmpBuffer;

	// 現在チェックしてるグループが格納される
	char*   m_pGroupBuffer;

	// ファイル読み込みモードになってるかのフラグ
	bool isFileLoadMode;

	// ファイル書き込みモードになってるかのフラグ
	bool isFileSaveMode;

};



#endif