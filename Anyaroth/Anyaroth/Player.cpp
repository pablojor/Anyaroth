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

	auto transform = addComponent<TransformComponent>();		//Como en el metodo anterior se ha creado este componente, imprime por pantalla que ya existe uno.
	transform->setPosition(50, 50);

	auto body = addComponent<BodyComponent>();
	body->getBody()->SetType(b2_dynamicBody);
	body->getBody()->SetBullet(true);
	body->getBody()->SetFixedRotation(true);
	body->setW(20);
	body->filterCollisions(PLAYER, OBJECTS | FLOOR);
	
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

	//Monedore
	_money = new Money();
}

Player::~Player()
{
	delete _money;
}

void Player::beginCollision(GameComponent * other)
{
	auto myTransform = this->getComponent<TransformComponent>();
	auto myControler = this->getComponent<PlayerControllerComponent>();

	auto otherTransform = other->getComponent<TransformComponent>();

	if (myTransform->getPosition().getY() < otherTransform->getPosition().getY())
		myControler->ableJump();

	if(other->getTag() == "Moneda")
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
	auto myTransform = this->getComponent<TransformComponent>();
	auto myControler = this->getComponent<PlayerControllerComponent>();

	auto otherTransform = other->getComponent<TransformComponent>();

	if (myTransform->getPosition().getY() < otherTransform->getPosition().getY())
		myControler->changeJump();
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