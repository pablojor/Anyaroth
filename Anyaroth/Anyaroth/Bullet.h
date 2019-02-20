#pragma once
#include "GameComponent.h"
#include "Vector2D.h"

/*********************************
	//RECORDATORIO: 
		Rango

/*********************************/

class Bullet : public GameComponent
{
private:
	bool _active = false;
	double _speed = 0;
	int _damage = 0;
	//Texture* _texture = nullptr;
public:
	Bullet();
	virtual ~Bullet();

	void setSpeed(double speed) { _speed = speed; };
	void setDamage(double damage) { _damage = damage; };
	void setTexture(Texture* texture);
	void setActive(bool active) { _active = active; };

	bool isActive() { return _active; };
};