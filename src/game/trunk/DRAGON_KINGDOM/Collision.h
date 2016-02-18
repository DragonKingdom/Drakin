/**
 * @file Collision.h
 * @author danjo
 */

#ifndef COLLISION_H
#define COLLISION_H

#include <vertex.h>
/**
 * 衝突判定を行うクラス
 */
class Collision
{
public:

private:

public:
	Collision();
	~Collision();

	bool PointToSquare(D3DXVECTOR2 _point,Vertex::FRECT _rect);
private:
	
};
#endif