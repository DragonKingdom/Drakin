/**
 * @file  GameData.h
 * @author danjo
 */

#ifndef GAMEDATA_H
#define GAMEDATA_H


/// @todo Time�\���̂̒�`�ꏊ
struct Time
{
	int year;	// �N
	int month;	// ��
	int date;	// ��
	int hour;	// ����
	int minute;	// ��
	int second;	// �b
};

struct KingdomData
{
	int Money;			// ����
	int Population;		// �l��
	int Security;		// ����
	int Satisfaction;	// �����x
	int Popularity;		// �l�C�x
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

	/// @todo �t�@�C�����o�͂͂�������銴���ł����̂���
	void Load(int _dataID);
	void Save(int _dataID);

	/**
	 * �Q�[�������Ԃ��Z�b�g����֐�
	 * @param[in] _SetTimeData �Z�b�g����f�[�^���i�[���ꂽTime�\����
	 */
	void SetGameTime(Time _SetTimeData);

	/**
	 * �Q�[�������Ԃ��擾����֐�
	 * @return �Q�[�������Ԃ�������Time�\����
	 */
	Time GetGameTime();

	/**
	 * �����̏����Z�b�g����֐�
	 * @param[in] _SetKingdomData �Z�b�g����f�[�^���i�[���ꂽKingdomData�\����
	 */
	void SetKingdomData(KingdomData _setKingdomData);

	/**
	 * �����̏����擾����֐�
	 * @return �����̏�񂪓������\����
	 */
	KingdomData GetKingdomData();

	/**
	 * �����̏����Z�b�g����֐�
	 * @param[in] _SetMoney �Z�b�g����f�[�^
	 */
	void SetMoney(int _setMoney);

	/**
	 * �����̏����擾����֐�
	 * @return �����̏�񂪕Ԃ��Ă���
	 */
	int GetMoney();

	/**
	 * �����𑝉�����֐�
	 * @param[in] _IncreaseValue �����̏㏸�l
	 */
	void IncreaseMoney(int _IncreaseValue);

	/**
	 * ��������������֐�
	 * @param[in] _DecreaseValue �����̌����l
	 */
	void DecreaseMoney(int _DecreaseValue);

private:
	GameData();
	GameData(const GameData &other){}
	GameData &operator = (const GameData &other){}

	static GameData* m_pGameData;

	/// �v���C����
	Time			m_gameTime;
	KingdomData		m_KingdomData;


};


#endif