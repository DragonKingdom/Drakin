/**
 * @file  GameData.h
 * @author danjo
 */

#ifndef GAMEDATA_H
#define GAMEDATA_H

/**
 * �Q�[���f�[�^���Ǘ�����N���X
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
     * �C���X�^���X�̎擾
     */
	static GameData& getInstance()
	{
		static GameData gameData;
		return gameData;
	};

	/// �Q�[������
	struct Time
	{
		int year;
		int month;
		int date;
		int hour;
		int minute;
		int second;
	};
	/// �v���C����
	Time m_time;

	void Load(int _dataID);
	void Save(int _dataID);
};
#endif