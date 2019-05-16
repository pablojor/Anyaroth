#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "BulletEffect.h"
#include "GunType_def.h"

class Bullet : public GameObject
{
protected:
	int _range = 200; //rango del arma (en pixeles)
	int _aliveTime = 0; //tiempo que lleva vivo (usado en el rango)
	int _damage = 0;
	double _speed = 0;

	bool _collided = false;
	bool _isColliding = false;

	Vector2D _iniPos = { 0,0 };

	Texture* _texture = nullptr;
	TransformComponent* _transform = nullptr;
	BodyComponent* _body = nullptr;
	AnimatedSpriteComponent* _anim = nullptr;
	EffectInterface* _effect = nullptr;

	//Bounces
	int _numBounces = 0;

	//Gravity
	bool _absorbing = false;
	int _absorbingTime = 0;

	//Explosive
	bool _explode = false;
	double _explosionTime = 0;

public:
	Bullet(Game* game);
	virtual ~Bullet();

	inline void setSpeed(double speed) { _speed = speed; }
	inline double getSpeed() const { return _speed; }

	inline void setDamage(double damage) { _damage = damage; }
	inline int getDamage() const { return _damage; }

	inline BodyComponent* getBody() { return _body; }
	inline TransformComponent* getTransform() { return _transform; }

	inline Vector2D getIniPos() const { return _iniPos; }
	inline int getRange() const { return _range; }

	inline bool hasCollided() const { return _collided; }
	inline void setCollided(bool b) { _collided = b; }

	inline bool isColliding() const { return _isColliding; }
	inline void setIsColliding(bool b) { _isColliding = b; }

	inline int getAliveTime() const { return _aliveTime; }
	inline void setAliveTime(int time) { _aliveTime = time; }

	//Bounces
	inline int getNumBounces() const { return _numBounces; }
	inline void setNumBounces(int value) { _numBounces = value; }

	//Gravity
	inline int isAbsorbing() const { return _absorbing; }
	inline void setAbsorbing(bool value) { _absorbing = value; }

	inline int getAbsorbingTime() const { return _absorbingTime; }
	inline void setAbsorbingTime(int value) { _absorbingTime = value; }

	//Explosive
	inline bool isExploding() const { return _explode; }
	inline void setExploding(bool value) { _explode = value; }

	inline int getExplosionTime() const { return _explosionTime; }
	inline void setExplosionTime(int value) { _explosionTime = value; }

	virtual void init(Texture* texture, const Vector2D& position, double speed, double damage, double angle, double range, const string& tag, EffectInterface* effect, BulletAnimType type);
	virtual void update(double deltaTime);
	virtual void beginCollision(GameObject* other, b2Contact* contact);
	virtual void endCollision(GameObject * other, b2Contact* contact);

	void reset();

	void changeFilter();
	void setAnimations(BulletAnimType type);
};