#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
class Particle :
	public GameObject
{
private:
	Texture* _texture = nullptr;
	TransformComponent* _transform = nullptr;
	BodyComponent* _body = nullptr;
	AnimatedSpriteComponent* _anim = nullptr;

	int _maxAliveTime = 0; //tiempo de vida
	float _gravScale = 0;
	double _speed = 0;

	Vector2D _iniPos = { 0,0 };
public:
	Particle(Game* game);
	~Particle();

	virtual void init(Texture* texture, const Vector2D& position, double speed, double angle,double aliveTime);
	virtual void update(double deltaTime);
	inline void setGravScale(float grav) { _gravScale = grav; _body->getBody()->SetGravityScale(grav); }
	/*virtual void beginCollision(GameObject* other, b2Contact* contact);
	virtual void endCollision(GameObject * other, b2Contact* contact);
*/
	void reset();
};

