#include "Bullet.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "TransformComponent.h"
#include "MovingComponent.h"

Bullet::Bullet() 
{
	
}

Bullet::~Bullet() 
{
}


void Bullet::init(Texture* texture, double speed, int damage, int range)
{
	_speed = speed;
	_damage = damage;
	_range = range;

	addComponent<Texture>(texture);

	auto _trans = addComponent<TransformComponent>();
	_trans->setScale(0.15);

	auto body = addComponent<BodyComponent>();
	body->getBody()->SetType(b2_dynamicBody);
	body->getBody()->SetBullet(true);
	body->getBody()->SetFixedRotation(true);

	auto anim = addComponent<AnimatedSpriteComponent>();
	anim->addAnim(AnimatedSpriteComponent::Default, 1, false);
	anim->playAnim(AnimatedSpriteComponent::Default);

	
	
	//addComponent<BodyComponent>(); 
	addComponent<MovingComponent>();//Tiene que ir aquí porque necesita la textura
	
}


void Bullet::update() 
{
	if (_aliveTime < _range * 10)
	{

		cout << "X: " << getComponent<TransformComponent>()->getPosition().getX() << "	Y: " << getComponent<TransformComponent>()->getPosition().getY() << endl << endl;
		GameComponent::update();

		_aliveTime++;
	}
	else
		setActive(false);
}


void Bullet::reset()
{
	setActive(true);
	_aliveTime = 0;
}