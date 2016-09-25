#include "stdafx.h"
#include "CustomUserVertex.h"


CustomUserVertex::CustomUserVertex():
m_Type(USERVERTEX_1),
m_VertexSize(0),
m_pUserVertex(NULL),
m_pUserVertex2(NULL),
m_pUserVertex3(NULL)
{
}

CustomUserVertex::~CustomUserVertex()
{
}

void* CustomUserVertex::GetVertex()
{
	switch (m_Type)
	{
	case USERVERTEX_1:
		return m_pUserVertex;
		break;
	case USERVERTEX_2:
		return m_pUserVertex2;
		break;
	case USERVERTEX_3:
		return m_pUserVertex3;
		break;
	}
}

int CustomUserVertex::GetVertexSize()
{
	return m_VertexSize;
}

USERVERTEX_TYPE CustomUserVertex::GetUserVertexType()
{
	return m_Type;
}

