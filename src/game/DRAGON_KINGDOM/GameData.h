/**
 * @file  GameData.h
 * @author danjo
 */

#ifndef GAMEDATA_H
#define GAMEDATA_H

/**
 * ゲームデータを管理するクラス
 */
class GameData
{
private:
	GameData();
	GameData(const GameData &other){}
	GameData &operator = (const GameData &other){}
public:
	~GameData();

	/**
     * インスタンスの取得
     */
	static GameData& getInstance()
	{
		static GameData gameData;
		return gameData;
	};

	/// ゲーム時間
	struct Time
	{
		int year;
		int month;
		int date;
		int hour;
		int minute;
		int second;
	};
	/// プレイ時間
	Time m_time;

	void Load(int _dataID);
	void Save(int _dataID);
};
#endif