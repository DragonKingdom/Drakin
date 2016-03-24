/**
 * @file  GameData.h
 * @author danjo
 */

#ifndef GAMEDATA_H
#define GAMEDATA_H


/// @todo Time�\���̂̒�`�ꏊ
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
 * �Q�[���f�[�^���Ǘ�����N���X
 */
class GameData
{
public:
	~GameData();

	/**
     * �C���X�^���X�̎擾
     */
	static GameData* getInstance()
	{
		if (m_pGameData == NULL)
		{
			m_pGameData = new GameData();
		}
		return m_pGameData;
	};

	// @todo �t�@�C�����o�͂͂�������銴���ł����̂���
	void Load(int _dataID);
	void Save(int _dataID);

	/**
	 * �Q�[�������Ԃ��Z�b�g����֐�
	 * @param[in] SetTimeData �Z�b�g����f�[�^���i�[���ꂽTime�\����
	 */
	void GameData::SetGameTime(Time _SetTimeData);

	/**
	 * �Q�[�������Ԃ��擾����֐�
	 * @return �Q�[�������Ԃ�������Time�\����
	 */
	Time GameData::GetGameTime();

	


private:
	GameData();
	GameData(const GameData &other){}
	GameData &operator = (const GameData &other){}

	static GameData* m_pGameData;

	/// �v���C����
	Time m_gameTime;
};


#endif