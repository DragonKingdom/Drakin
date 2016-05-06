#ifndef DEBUGMODE_H
#define DEBUGMODE_H

#include "Font.h"

#define DEBUGDATA_POS_X 0
#define DEBUGDATA_POS_Y 0


class ClickPosConverter;

class DebugMode
{
public:
	DebugMode(ClickPosConverter* pClickPosConverter);
	~DebugMode();
	void DebugDisplay();

private:
	ClickPosConverter*	m_pClickPosConverter;
	Font				m_Font;


};



#endif