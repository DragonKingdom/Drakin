/**
 * @file   BuildAreaManager.h
 * @brief  エリアの建設物情報の管理クラスh
 *
 * @author
 */

#ifndef BUILDAREAMANAGER_H
#define BUILDAREAMANAGER_H

class BuildAreaBuilder;
class BuildArea;
class InputDeviceFacade;
class StateManager;
class GameData;
class FileSaveLoad;
class ClickPosConverter;

class BuildAreaManager
{
public:
	BuildAreaManager(StateManager* _pStateManager, GameData* _pGameData, ClickPosConverter* _pClickPosConverter);
	~BuildAreaManager();

	/**
	 * Area生成の制御関数
	 */
	void AreaBuildControl();
	/**
	 * 描画関数
	 */
	void Draw();

	/**
	* エリアが空いてるかをチェックする関数(エリアがあるかは関係ない)
	* @param[in] _checkPos チェックしたい座標
	* @return エリアが空いていればtrueを返す(ビルドエリアがなくてもtrueを返す)
	*/
	bool AreaCheck(D3DXVECTOR3* _checkPos);	

	/**
	* 建物が建築されたことを伝える関数
	* @param[in] 建築された場所
	* @return 成功したらtrue
	*/
	bool SetBuilding(D3DXVECTOR3* _setPos);

	/**
	* ビルドエリアの存在と中心座標を取得する関数
	* @param[in] _checkPos チェックしたいエリアの座標
	* @param[out] _centerPos エリアの中心位置が入るポインタ
	* @return エリアが存在しなければfalseを返す
	*/
	bool GetAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle);


	void GetState();

	void SetState();

	void GetGameData();

	void SetGameData();

	void Load(FileSaveLoad* _pFileSaveLoad);

	void Save(FileSaveLoad* _pFileSaveLoad);


private:
	BuildAreaBuilder*				m_pBuildAreaBuilder;
	std::vector<BuildArea*>			m_pBuildArea;
	BUILDAREAMANAGER_ENUM::STATE	m_state;
	BUILD_STATE						m_buildState;
	StateManager*					m_pStateManager;
	GameData*						m_pGameData;
	InputDeviceFacade*				m_pInputDevice;
	bool							m_roadLinkStart_StartPos; //StartPosで繋げられた道が始点か？
	bool							m_roadLinkEnd_StartPos; //EndPosで繋げられた道が始点か？

	/**
	* 道を繋げるために使う敷かれている道をチェックして近くに道があれば、そこのstartposまたはendposとangleを渡す
	* @param[in] _checkPos チェックしたい座標
	* @param[out] _pStartOrEndPos startposまたはendpos
	* @param[out] _outputAngleDegree 見つけた道の角度
	* @param[in] _startPos 繋げられる道の始点か？
	* @return 周辺に道がなければfalseを返す
	*/
	bool BuildAreaCheck(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _pStartOrEndPos, float* _outputAngleDegree, bool* _startPos);

	/// @todo テスト用
	ClickPosConverter* m_pClickPosConverter;
};




#endif