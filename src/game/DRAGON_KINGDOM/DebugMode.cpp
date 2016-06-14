#include "DebugMode.h"
#include "ClickPosConverter.h"
#include "InputDeviceFacade.h"
#include <string>


DebugMode::DebugMode(ClickPosConverter* pClickPosConverter):
m_pClickPosConverter(pClickPosConverter)
{
}

DebugMode::~DebugMode()
{
}

void DebugMode::DebugDisplay()
{
#ifdef _DEBUG
	D3DXVECTOR3 ConvertPos;
	D3DXVECTOR2 MousePos = InputDeviceFacade::GetInstance()->GetMousePos();
	m_pClickPosConverter->ConvertForLoad(&ConvertPos, int(MousePos.x), int(MousePos.y));

	std::string DebugStr =
		"x座標：" + std::to_string(ConvertPos.x) + "\n" +
		"y座標：" + std::to_string(ConvertPos.y) + "\n" +
		"z座標：" + std::to_string(ConvertPos.z) + "\n";



	m_Font.Draw(DebugStr.c_str(), D3DXVECTOR2(DEBUGDATA_POS_X, DEBUGDATA_POS_Y));

#endif
}


