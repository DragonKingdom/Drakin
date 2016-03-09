/**
 * @file Collision.h
 * @author danjo
 */

#ifndef COLLISION_H
#define COLLISION_H

#include <vertex.h>
/**
 * �Փ˔�����s���N���X
 */
class Collision
{
public:
	Collision(){};
	~Collision(){};

	bool PointToSquare(D3DXVECTOR2 _point,Vertex::FRECT _rect);
private:
	
};
namespace tdCollision{
	bool PointToSquare(const D3DXVECTOR2& _point, const Vertex::FRECT& _rect);

}
#endif