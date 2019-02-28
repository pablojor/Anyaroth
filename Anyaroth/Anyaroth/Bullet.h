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
	int _range = 200; //rango del arma (en píxeles)
	int _aliveTime = 0; //Tiempo que lleva vivo (usado en el rango)
	double _speed = 0;
	int _damage = 0;
	double _angle = 0;

	bool _collided = false;

	Vector2D _velocity = { 0,0 };
	Vector2D _iniPos = { 0,0 };

	TransformComponent* _trans = nullptr;

	//Texture* _texture = nullptr;
public:
	Bullet(Texture* texture, Vector2D iniPos, Game* g, string tag);
	Bullet();
	virtual ~Bullet();

	void beginCollision(GameComponent* other);
	void setSpeed(double speed) { _speed = speed; };
	void setDamage(double damage) { _damage = damage; };
	int getDamage() { return _damage; };
	void setVelocity(Vector2D vel) { _velocity = vel; };
	void setRotation(double rot) { _angle = rot; };

	void init(Texture* texture, double speed, int damage, double angle, int range = 5);
	
	/*virtual void render() const
	{
		GameComponent::render();
		
	}*/

	virtual void update();

	void reset(Vector2D pos);
	
};