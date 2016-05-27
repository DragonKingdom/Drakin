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
	* ビルドエリアの存在と中心座標を取得する関数
	* @param[in] _checkPos チェックしたいエリアの座標
	* @param[out] _centerPos エリアの中心位置が入るポインタ
	* @return エリアが存在しなければfalseを返す
	*/
	bool GetAreaCenterPos(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _centerPos, float* _pAngle);

	/**
	* 道を繋げるために使う敷かれている道をチェックして近くに道があれば、そこのstartposまたはendposとangleを渡す
	* @param[in] _checkPos チェックしたい座標
	* @param[in] _pStartOrEndPos startposまたはendpos
	* @param[in] _outputAngleDegree 見つけた道の角度
	* @return 周辺に道がなければfalseを返す
	*/
	bool BuildAreaCheck(D3DXVECTOR3* _checkPos, D3DXVECTOR3* _pStartOrEndPos, float* _outputAngleDegree);

	void GetState();

	void SetState();

	void GetGameData();

	void SetGameData();

private:
	BuildAreaBuilder*				m_pBuildAreaBuilder;
	std::vector<BuildArea*>			m_pBuildArea;
	BUILDAREAMANAGER_ENUM::STATE	m_state;
	BUILD_STATE						m_buildState;
	StateManager*					m_pStateManager;
	GameData*						m_pGameData;
	InputDeviceFacade*				m_pInputDevice;

	/// @todo テスト用
	ClickPosConverter* m_pClickPosConverter;
};




#endif