#include "Particle.h"
#include "Game.h"



Particle::Particle(Game* game) : GameObject(game)
{
	_texture = game->getTexture("PistolBullet");
	addComponent<Texture>(_texture);

	_transform = addComponent<TransformComponent>();
	_transform->setAnchor(0.5);

	_anim = addComponent<AnimatedSpriteComponent>();

	_body = addComponent<BodyComponent>();
	_body->filterCollisions(PLAYER_BULLETS,FLOOR);
	_body->getBody()->SetType(b2_dynamicBody);
	_body->getBody()->SetFixedRotation(true);
	_body->getBody()->SetGravityScale(0);
	_body->getBody()->SetActive(false);

	setActive(false);
}


Particle::~Particle()
{
}

void Particle::init(Texture * texture, const Vector2D & position, double speed, double angle, double aliveTime)
{

	_iniPos = position;
	_transform->setPosition(position);
	_speed = speed;
	_maxAliveTime = aliveTime;


	_texture = texture;
	_transform->setRotation(angle);

	_body->setH(texture->getH()/2);
	_body->setW(texture->getW()/2);
	
	_body->moveShape(b2Vec2(0, 0));
	_body->filterCollisions(PLAYER_BULLETS, FLOOR);
	
	_body->getBody()->SetActive(true);
	_body->getBody()->SetTransform({ (float32)(position.getX() / M_TO_PIXEL), (float32)(position.getY() / M_TO_PIXEL) }, _body->getBody()->GetAngle());
	_body->getBody()->SetLinearVelocity(b2Vec2(_speed*cos(angle* M_PI / 180.0), -_speed*sin(angle* M_PI / 180.0)));




	_anim->setTexture(texture);

	setActive(true);
}

void Particle::update(double deltaTime)
{
	GameObject::update(deltaTime);
	if (isActive()) {
		if (_maxAliveTime > 0)
		{
			_maxAliveTime -= deltaTime;
			
		}
		else
		{
			reset();
		}
	}
}

void Particle::reset()
{
	_body->getBody()->SetGravityScale(0);
	_body->getBody()->SetActive(false);
	setActive(false);
	_maxAliveTime = 0;
}
