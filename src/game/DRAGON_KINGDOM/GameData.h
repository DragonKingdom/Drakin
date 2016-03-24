/**
 * @file  GameData.h
 * @author danjo
 */

#ifndef GAMEDATA_H
#define GAMEDATA_H


/// @todo Time構造体の定義場所
struct Time
{
	int year;
	int month;
	int date;
	int hour;
	int minute;
	int second;
};

/**
 * ゲームデータを管理するクラス
 */
class GameData
{
public:
	~GameData();

	/**
     * インスタンスの取得
     */
	static GameData* getInstance()
	{
		if (m_pGameData == NULL)
		{
			m_pGameData = new GameData();
		}
		return m_pGameData;
	};

	// @todo ファイル入出力はこいつがやる感じでいいのかな
	void Load(int _dataID);
	void Save(int _dataID);

	/**
	 * ゲーム内時間をセットする関数
	 * @param[in] SetTimeData セットするデータが格納されたTime構造体
	 */
	void GameData::SetGameTime(Time _SetTimeData);

	/**
	 * ゲーム内時間を取得する関数
	 * @return ゲーム内時間が入ったTime構造体
	 */
	Time GameData::GetGameTime();

	


private:
	GameData();
	GameData(const GameData &other){}
	GameData &operator = (const GameData &other){}

	static GameData* m_pGameData;

	/// プレイ時間
	Time m_gameTime;
};


#endif