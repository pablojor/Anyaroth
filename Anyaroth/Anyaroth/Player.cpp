#include "Player.h"
#include "PlayerControllerComponent.h"
#include "TransformComponent.h"
#include "MovingComponent.h"
#include "Game.h"
#include "FollowingComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Coin.h"

Player::Player(Texture* texture, Game* g, string tag) : GameComponent(g, tag)
{
	//Siempre primero los componentes que tienen que estar SI o SI.
	addComponent<Texture>(texture);

	//Resto de componentes
	//addComponent<FollowingComponent>(this);


	 _transform = addComponent<TransformComponent>();		//Como en el metodo anterior se ha creado este componente, imprime por pantalla que ya existe uno.
	 _transform->setPosition(50, 50);

	 _body = addComponent<BodyComponent>();
	 _body->getBody()->SetType(b2_dynamicBody);
	 _body->getBody()->SetBullet(true);
	 _body->getBody()->SetFixedRotation(true);
	 _body->setW(20);
	 _body->filterCollisions(PLAYER, OBJECTS | FLOOR /*| ENEMY_BULLETS*/);

	_anim = addComponent<AnimatedSpriteComponent>();		//Como depende de Transform, en su constructura crea una si no ha encontrado Transform en el objeto.
	_anim->addAnim(AnimatedSpriteComponent::Idle, 16, true);
	_anim->addAnim(AnimatedSpriteComponent::Walk, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::WalkBack, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::MeleeKnife, 6, false);
	_anim->addAnim(AnimatedSpriteComponent::ReloadPistol, 13, false);

	addComponent<MovingComponent>();
	_controller = addComponent<PlayerControllerComponent>();

	/*//brazo de atr�s
	auto armBack = new Arm(g->getTexture("Armback"), this, getGame(), { 11,5 });
	addChild(armBack);*/

	//Brazo con arma
	//_weaponArm = new Arm(getGame()->getTexture("ArmPistol"), this, getGame(), { 10,12 }); 

	_weaponArm = new Arm(getGame()->getTexture("ArmPistol"), this, getGame(), { 11,5 }); //Parámetros para la pistola
	addChild(_weaponArm);

	//Equipa el arma inicial
	equipGun(getGame()->BasicGun);

	AmountOfCollision = 0;
	//Monedore
	_money = new Money();

}

Player::~Player()
{
	delete _money;
}

void Player::beginCollision(GameComponent * other)
{
	
	auto otherTransform = other->getComponent<TransformComponent>();
	auto otherBody = other->getComponent<BodyComponent>();

	double myH = _body->getH(), myW = _body->getW();
	double otherH = otherBody->getH(), otherW = otherBody->getW();
	string otherTag = other->getTag();
	if (otherTag == "Suelo")
	{
		AmountOfCollision += 1;
		
		if (_transform->getPosition().getY() + myH * (M_TO_PIXEL * 2) < otherTransform->getPosition().getY())
		{
			_controller->ableJump();

		}
		else if (_transform->getPosition().getY() + myH * (M_TO_PIXEL * 2) > otherTransform->getPosition().getY())
		{
			
			if (_transform->getPosition().getY() <= otherTransform->getPosition().getY() + otherH * (M_TO_PIXEL * 2))
			{
				if (_transform->getPosition().getX() + myW * (M_TO_PIXEL) < otherTransform->getPosition().getX() - otherW * (M_TO_PIXEL * 2))
				{
					_controller->wallOnRight(true);
				}
				else
					_controller->wallOnLeft(true);
			}
		}
	}
	else if (otherTag == "Bullet")
	{
		double damage = 0;
		//damage=dynamic_cast<Bullet*>(other).getDamage();
		subLife(damage);
	}
  else if(other->getTag() == "Moneda")
	{
		auto coin = dynamic_cast<Coin*>(other);
		auto cant = coin->getValue();
		_money->store(cant);
		coin->destroy();
		cout << "Moneda cogida" << endl;
		cout << "Cantidad monedero: " << _money->getWallet() << endl;
	}
}

void Player::endCollision(GameComponent * other)
{
	
	

	auto otherTransform = other->getComponent<TransformComponent>();
	auto otherBody = other->getComponent<BodyComponent>();

	double myH = _body->getH(), myW = _body->getW();
	double otherH = otherBody->getH(), otherW = otherBody->getW();

	string otherTag = other->getTag();
	if (otherTag == "Suelo")
	{
		AmountOfCollision -= 1;

		if (_transform->getPosition().getY() + myH * (M_TO_PIXEL * 2) < otherTransform->getPosition().getY())
		{


			if ((_body->getBody()->GetLinearVelocity().y < -0.5))
			{
				_controller->changeJump();
			}
		}
		if (_transform->getPosition().getY() + myH * (M_TO_PIXEL * 2) > otherTransform->getPosition().getY() ||
			(_transform->getPosition().getY() + myH * (M_TO_PIXEL * 2) < otherTransform->getPosition().getY()) && (AmountOfCollision == 0))
		{

			if (_transform->getPosition().getX() + myW * (M_TO_PIXEL) < otherTransform->getPosition().getX() - otherW * (M_TO_PIXEL * 2))
			{
				_controller->wallOnRight(false);
			}
			else
				_controller->wallOnLeft(false);
		}
	}
}

void Player::setLife(double amount)
{
	_life = amount;
}


void Player::addLife(double amount)
{
	_life += amount;
}

void Player::subLife(double amount)
{
	if (_life > amount)
		_life -= amount;
	else
		die();
}

void Player::die()
{
}

void Player::update()
{
	
	GameComponent::update();

	if (_anim->animationFinished())
	{
		_anim->playAnim(AnimatedSpriteComponent::Idle);
		_controller->setIsAttacking(false);
		_controller->setIsReloading(false);

		_currentState = Idle;
	}
	
	if (AmountOfCollision<=0)
	{
		_controller->changeJump();
	}
	
	if (_controller->amountDash() < _MaxDash)
	{
		if (SDL_GetTicks() > _timer + _dashCD)
		{
			
			_controller->newDash();
			_timer = SDL_GetTicks();
		}
	}
	else
		_timer = SDL_GetTicks();
}

//Equipa un arma utilizando el array de atributos gameGuns de Game.h
void Player::equipGun(int gunIndex)
{
	Shooter* sh = &getGame()->gameGuns[gunIndex].shooter;
	string name = getGame()->gameGuns[gunIndex].name;
	int mA = getGame()->gameGuns[gunIndex].maxAmmo;
	int mC= getGame()->gameGuns[gunIndex].maxClip;

	_weaponArm->setGun(new Gun(this, sh, name, mA, mC));
	//cout << "Gun equipada" << endl << endl << endl << endl << endl << endl;
}

void Player::reload()
{
	_controller->reload();
}