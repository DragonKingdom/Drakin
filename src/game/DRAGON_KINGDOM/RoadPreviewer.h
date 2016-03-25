#ifndef ROADPREVIEWER_H
#define ROADPREVIEWER_H


class RoadPreviewer
{
public:
	RoadPreviewer();
	~RoadPreviewer();
	void Draw();
	void StartPosSet(D3DXVECTOR3 _startPos);
	void EndPosSet(D3DXVECTOR3 _endPos);

private:
	D3DXVECTOR3 m_StartPos;
	D3DXVECTOR3 m_EndPos;

};


#endif