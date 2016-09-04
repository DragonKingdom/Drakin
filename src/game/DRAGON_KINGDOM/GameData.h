/**
 * @file  GameData.h
 * @author danjo
 */

#ifndef GAMEDATA_H
#define GAMEDATA_H

class FileSaveLoad;

/// @todo Time構造体の定義場所
struct Time
{
	int year;	// 年
	int month;	// 月
	int date;	// 日
	int hour;	// 時間
	int minute;	// 分
	int second;	// 秒
};

struct KingdomData
{
	int Money;			// お金
	int Population;		// 人口
	int Security;		// 治安
	int Satisfaction;	// 満足度
	int Popularity;		// 人気度
};

// 建物の数を格納する構造体
struct HouseNum
{
	int House;			// 建物の総数
	int PrivateHouse;	// 民家の総数
	int Blacksmith;		// 鍛冶屋の総数
};

/**
 * ゲームデータを管理するクラス
 */
class GameData
{
public:
	~GameData();

	/**
	* インスタンスの取得関数
	*/
	static GameData* getInstance()
	{
		if (m_pGameData == NULL)
		{
			m_pGameData = new GameData();
		}
		return m_pGameData;
	}

	/**
	* インスタンスの解放関数
	*/
	static void Release()
	{
		delete m_pGameData;
		m_pGameData = NULL;
	}


	/// @todo ファイル入出力はこいつがやる感じでいいのかな
	void Load(FileSaveLoad* _pFileSaveLoad);
	void Save(FileSaveLoad* _pFileSaveLoad);

	/**
	 * ゲーム内時間をセットする関数
	 * @param[in] _SetTimeData セットするデータが格納されたTime構造体
	 */
	void SetGameTime(Time _SetTimeData);

	/**
	 * ゲーム内時間を取得する関数
	 * @return ゲーム内時間が入ったTime構造体
	 */
	Time GetGameTime();

	/**
	 * 王国の情報をセットする関数
	 * @param[in] _SetKingdomData セットするデータが格納されたKingdomData構造体
	 */
	void SetKingdomData(KingdomData _setKingdomData);

	/**
	 * 王国の情報を取得する関数
	 * @return 王国の情報が入った構造体
	 */
	KingdomData GetKingdomData();

	/**
	 * 建物の数をセットする関数
	 * @param[in] _setHouseNum セットするデータが格納されたHouseNum構造体
	 */
	void SetHouseNum(HouseNum _setHouseNum);

	/**
	 * 建物の数を取得する関数
	 * @return 建物の数が入った構造体
	 */
	HouseNum GetHouseNum();

	/**
	 * お金の情報をセットする関数
	 * @param[in] _SetMoney セットするデータ
	 */
	void SetMoney(int _setMoney);

	/**
	 * お金の情報を取得する関数
	 * @return お金の情報が返ってくる
	 */
	int GetMoney();

	/**
	 * お金を増加する関数
	 * @param[in] _IncreaseValue お金の上昇値
	 */
	void IncreaseMoney(int _IncreaseValue);

	/**
	 * お金を減少する関数
	 * @param[in] _DecreaseValue お金の減少値
	 */
	void DecreaseMoney(int _DecreaseValue);

private:
	GameData();
	GameData(const GameData &other){}
	GameData &operator = (const GameData &other){}

	static GameData* m_pGameData;

	/// プレイ時間
	Time			m_gameTime;
	KingdomData		m_KingdomData;
	HouseNum		m_HouseNum;

};


#endif