#include "Collision.h"

bool Collision::PointToSquare(D3DXVECTOR2 _point,Vertex::FRECT _rect)
{
	if( _point.x >= _rect.left && _point.x <= _rect.right )
	{
		if( _point.y >= _rect.top && _point.y <= _rect.bottom)
		{
			return true;
		}
	}
	return false;
}
bool tdCollision::PointToSquare(const D3DXVECTOR2& _point, const Vertex::FRECT& _rect){
	if (_point.x >= _rect.left && _point.x <= _rect.right)
	{
		if (_point.y >= _rect.top && _point.y <= _rect.bottom)
		{
			return true;
		}
	}
	return false;
}
