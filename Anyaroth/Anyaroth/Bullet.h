#pragma once
#include "GameComponent.h"
#include "Vector2D.h"
#include "TransformComponent.h"

/*********************************
	//RECORDATORIO: 
		Rango

/*********************************/

class Bullet : public GameComponent
{
private:
	int _range = 20; //rango del arma (en segundos, aproximadamente)
	int _aliveTime = 0; //Tiempo que lleva vivo (usado en el rango)
	double _speed = 0;
	int _damage = 0;

	//Texture* _texture = nullptr;
public:
	Bullet();
	virtual ~Bullet();

	void setSpeed(double speed) { _speed = speed; };
	void setDamage(double damage) { _damage = damage; };
	void init(Texture* texture, double speed, int damage, int range = 20);
	
	virtual void render() const
	{
		GameComponent::render();
		
	}

	virtual void update();

	void reset();
	
};