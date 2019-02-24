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

	_trans = addComponent<TransformComponent>();
	_trans->setScale(0.25); //ESCALA

	auto body = addComponent<BodyComponent>();
	body->getBody()->SetType(b2_kinematicBody);
	body->getBody()->SetBullet(true);
	body->getBody()->SetFixedRotation(true);

	body->getBody()->SetActive(false);
	
	auto anim = addComponent<AnimatedSpriteComponent>();
	anim->addAnim(AnimatedSpriteComponent::Default, 1, false);
	anim->playAnim(AnimatedSpriteComponent::Default);
	anim->setTexture(texture);
	
	
	addComponent<MovingComponent>();//Tiene que ir aquí porque necesita la textura
	
}


void Bullet::update() 
{
	if (!isActive())
		return;

	if (_aliveTime < _range * 10)
	{
		//cout << "X: " << getComponent<TransformComponent>()->getPosition().getX() << "	Y: " << getComponent<TransformComponent>()->getPosition().getY() << endl << endl;
		
		GameComponent::update(); //<- DESCOMENTAR PARA PROBAR CON FÍSICAS


		// Actualiza la posición
		//_trans->setPosition(_trans->getPosition() + _velocity);  //<- DESCOMENTAR PARA PROBAR SIN FÍSICAS

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
}