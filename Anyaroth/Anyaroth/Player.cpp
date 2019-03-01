#include "Player.h"
#include "PlayerControllerComponent.h"
#include "TransformComponent.h"
#include "MovingComponent.h"
#include "Game.h"
#include "FollowingComponent.h"
#include "AnimatedSpriteComponent.h"
#include "PoolWrapper.h"
#include "Coin.h"

Player::Player(Texture* texture, Game* g, PlayState* play, string tag) : _play(play), GameComponent(g, tag)
{
	//Siempre primero los componentes que tienen que estar SI o SI.
	addComponent<Texture>(texture);

	//Resto de componentes
	_transform = addComponent<TransformComponent>();		//Como en el metodo anterior se ha creado este componente, imprime por pantalla que ya existe uno.
	_transform->setPosition(50, 50);

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_dynamicBody);
	_body->getBody()->SetBullet(true);
	
	_body->setW(12);
	_body->setH(26);
	
	_body->filterCollisions(PLAYER, OBJECTS | FLOOR /*| ENEMY_BULLETS*/);
	_body->addCricleShape(b2Vec2(0, 1.1), 0.7, PLAYER, OBJECTS | FLOOR);
	_body->getBody()->SetFixedRotation(true);

	_anim = addComponent<AnimatedSpriteComponent>();		//Como depende de Transform, en su constructura crea una si no ha encontrado Transform en el objeto.
	_anim->addAnim(AnimatedSpriteComponent::Idle, 16, true);
	_anim->addAnim(AnimatedSpriteComponent::Walk, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::WalkBack, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::MeleeKnife, 6, false);
	_anim->addAnim(AnimatedSpriteComponent::ReloadPistol, 13, false);
	_anim->addAnim(AnimatedSpriteComponent::BeforeJump, 1, false);
	_anim->addAnim(AnimatedSpriteComponent::Jump, 4, true);
	_anim->addAnim(AnimatedSpriteComponent::StartFalling, 2, false);
	_anim->addAnim(AnimatedSpriteComponent::Falling, 2, true);
	_anim->addAnim(AnimatedSpriteComponent::Hurt, 2, true);
	_anim->addAnim(AnimatedSpriteComponent::Dash, 6, false);
	_anim->addAnim(AnimatedSpriteComponent::DashDown, 3, true);
	_anim->addAnim(AnimatedSpriteComponent::DashBack, 6, false);
	_anim->addAnim(AnimatedSpriteComponent::ReloadShotgun, 5, false);

	addComponent<MovingComponent>();
	_controller = addComponent<PlayerControllerComponent>();

	/*//brazo de atr�s
	auto armBack = new Arm(g->getTexture("Armback"), this, getGame(), { 11,5 });
	addChild(armBack);*/

	//Brazo con arma
	//_weaponArm = new Arm(getGame()->getTexture("ArmPistol"), this, getGame(), { 10,12 }); 

	//_weaponArm = new Arm(getGame()->getTexture("ArmPistol"), this, getGame(), { 26,5 }); //Parámetros para la pistola

	_weaponArm = new Arm(getGame()->getTexture("ArmPistol"), this, getGame(), { 28,14 }); //Parámetros para la pistola
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

		if (_transform->getPosition().getY() + (myH+ 0.3) * (M_TO_PIXEL * 2) < otherTransform->getPosition().getY())
		{
			_controller->ableJump();
		

		}
		else if (_transform->getPosition().getY() + (myH + 0.3) * (M_TO_PIXEL * 2) > otherTransform->getPosition().getY())
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
	else if (other->getTag() == "Moneda")
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

		if (_transform->getPosition().getY() + (myH + 0.3) * (M_TO_PIXEL * 2) < otherTransform->getPosition().getY())
		{


			if ((_body->getBody()->GetLinearVelocity().y < -2))
			{
				if(_controller->IsSpaceDown())
				_currentState = Player::Jumping;
				_controller->changeJump();
			}
			
		}
		if (_transform->getPosition().getY() + (myH + 0.3) * (M_TO_PIXEL * 2) > otherTransform->getPosition().getY() ||
			(_transform->getPosition().getY() + (myH + 0.3) * (M_TO_PIXEL * 2) < otherTransform->getPosition().getY()) && (AmountOfCollision == 0))
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

	if (_anim->animationFinished() && _currentState != Player::Falling && _currentState != Player::Jumping)
	{
		_anim->playAnim(AnimatedSpriteComponent::Idle);
		_controller->setIsAttacking(false);
		_controller->setIsReloading(false);

		_currentState = Idle;
	}

	if (AmountOfCollision <= 0|| _body->getBody()->GetLinearVelocity().y > 2)
	{
		if (_currentState != Player::Falling && _currentState != Player::Dashing && _body->getBody()->GetLinearVelocity().y > 2)
		{
			_anim->playAnim(AnimatedSpriteComponent::StartFalling);
			_currentState = Player::Falling;

		}
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
void Player::equipGun(int gunIndex, int bulletPoolIndex)
{
	Shooter* sh = &getGame()->gameGuns[gunIndex].shooter;
	string name = getGame()->gameGuns[gunIndex].name;
	int mA = getGame()->gameGuns[gunIndex].maxAmmo;
	int mC = getGame()->gameGuns[gunIndex].maxClip;

	// TEMPORAL
	PoolWrapper* bp = _play->getBulletPool();
	//

	_weaponArm->setGun(new Gun(_weaponArm, sh, bp, name, mA, mC));
	//cout << "Gun equipada" << endl << endl << endl << endl << endl << endl;
}

void Player::reload()
{
	_controller->reload();
}