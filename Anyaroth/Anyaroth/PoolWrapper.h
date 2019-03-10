#pragma once
#include "GameComponent.h"

//		Usar esta clase para crear punteros a BulletPool
//		sin tener que rellenar el SIZE de la clase plantilla

class PoolWrapper : public GameComponent
{
public:
	PoolWrapper() {}
	virtual ~PoolWrapper() {}

	virtual void addBullet(Vector2D pos, Vector2D dir, double angle) {}
	virtual void changePoolTag(string tag) {}
};