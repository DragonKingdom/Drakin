/**
* @file   TeamLogo.h
* @brief  ロゴシーンのチームロゴクラスのh
*
* @author morimoto
*/
#ifndef TEAMLOGO_H
#define TEAMLOGO_H

#include "FadeInOut.h"


class TeamLogo
{
public:
	TeamLogo();
	~TeamLogo();
	SceneID Control();
	void Draw();
	
	inline bool FadeInCompleted() { return m_fadeIn.FadeInCompleted(); }


private:
	FadeInOut	m_fadeIn;
	bool		m_IsFadeIn;

	DISALLOW_COPY_AND_ASSIGN(TeamLogo);


};




#endif