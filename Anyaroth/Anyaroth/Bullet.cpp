#include "Bullet.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "TransformComponent.h"
#include "MovingComponent.h"

Bullet::Bullet(Texture* texture, Vector2D iniPos, Game* g, string tag) : GameComponent(g, tag) 
{
	
}
Bullet::Bullet() 
{
	
}

Bullet::~Bullet() 
{
}
void Bullet::beginCollision(GameComponent * other)
{
	if(other->getTag() != "Player" && other->getTag() != "")
		_collided = true;
}

void Bullet::init(Texture* texture, double speed, int damage, double angle, int range)
{
	_speed = speed;
	_damage = damage;
	_range = range;
	_angle = angle;

	addComponent<Texture>(texture);

	_trans = addComponent<TransformComponent>();
	_trans->setAnchor(0.5); 
	_trans->setRotation(angle);

	auto body = addComponent<BodyComponent>();
	body->getBody()->SetType(b2_dynamicBody);
	body->getBody()->SetBullet(true);
	body->getBody()->SetFixedRotation(true);
	body->getBody()->SetGravityScale(0);

	body->getBody()->SetActive(false);
	
	auto anim = addComponent<AnimatedSpriteComponent>();
	anim->addAnim(AnimatedSpriteComponent::Default, 4, false);

	
	anim->setTexture(texture);
	
}


void Bullet::update() 
{
	if (!isActive())
		return;

	if (_aliveTime < _range * 10 && !_collided)
	{
		//cout << "X: " << getComponent<TransformComponent>()->getPosition().getX() << "	Y: " << getComponent<TransformComponent>()->getPosition().getY() << endl << endl;
		
		GameComponent::update(); //<- DESCOMENTAR PARA PROBAR CON F�SICAS


		// Actualiza la posici�n
		//_trans->setPosition(_trans->getPosition() + _velocity);  //<- DESCOMENTAR PARA PROBAR SIN F�SICAS

		// Desactiva la bala al salir de la pantalla (por hacer)
		/*
		if (position_.getX() + width_ <= 0
			|| position_.getX() >= getGame()->getWindowWidth()
			|| position_.getY() + height_ <= 0
			|| position_.getY() >= getGame()->getWindowHeight()) {
			toggleActive();
		}
		*/

		_aliveTime++;
	}
	else
	{
		setActive(false);
		this->getComponent<BodyComponent>()->getBody()->SetActive(false);
	}
}


void Bullet::reset()
{
	setActive(true);
	_aliveTime = 0;
	_collided = false;
}