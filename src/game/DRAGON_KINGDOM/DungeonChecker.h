#ifndef DUNGEONCHECKER_H


class DungeonChecker
{
public:
	DungeonChecker();
	~DungeonChecker();

	/**
	 * ランダムなダンジョンの座標を取得する
	 * @return ダンジョンの座標
	 */
	D3DXVECTOR3 GetRandomDungeonPos();

private: 

};


#endif