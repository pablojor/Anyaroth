#include "Player.h"
#include "PlayerControllerComponent.h"
#include "TransformComponent.h"
#include "MovingComponent.h"
#include "Game.h"
#include "FollowingComponent.h"
#include "AnimatedSpriteComponent.h"
#include "PoolWrapper.h"
#include "Coin.h"
#include "HurtRenderComponent.h"

Player::Player(Texture* texture, Game* g, PlayState* play, string tag) : _play(play), GameComponent(g, tag)
{
	//Siempre primero los componentes que tienen que estar SI o SI.
	addComponent<Texture>(texture);

	//Resto de componentes
	_transform = addComponent<TransformComponent>();		//Como en el metodo anterior se ha creado este componente, imprime por pantalla que ya existe uno.
	_transform->setPosition(50, 180);


	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_dynamicBody);
	_body->getBody()->SetBullet(true);
	
	_body->setW(12);
	_body->setH(26);
	
	_body->filterCollisions(PLAYER, OBJECTS | FLOOR /*| ENEMY_BULLETS*/);
	_body->addCricleShape(b2Vec2(0, 1.1), 0.7, PLAYER, FLOOR);
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

	_hurt = addComponent<HurtRenderComponent>();

	addComponent<MovingComponent>();
	_controller = addComponent<PlayerControllerComponent>();

	/*//brazo de atr�s
	auto armBack = new Arm(g->getTexture("Armback"), this, getGame(), { 11,5 });
	addChild(armBack);*/

	//Brazo con arma
	//_weaponArm = new Arm(getGame()->getTexture("ArmPistol"), this, getGame(), { 10,12 }); 

	//_weaponArm = new Arm(getGame()->getTexture("ArmPistol"), this, getGame(), { 26,5 }); //Parámetros para la pistola

	///_weaponArm = new Arm(getGame()->getTexture("ArmPistol"), this, getGame(), { 28,14 }); //Parámetros para la pistola
	///addChild(_weaponArm);

	//Inicialización del vector de texturas del brazo
	_armTextures =
	{
		getGame()->getTexture("ArmPistol"),
		getGame()->getTexture("ArmShotgun")
	};

	

	//Inventario inicial
	_gunInventory.push_back(BasicGun);
	_gunInventory.push_back(BasicShotgun); //para probar
	//Equipa el arma inicial
	equipGun(_gunInventory[1]);

	AmountOfCollision = 0;
	//Monedore
	_money = new Money();

}

Player::~Player()
{
	delete _money;
}

void Player::beginCollision(GameComponent * other, b2Contact* contact)
{

	auto otherTransform = other->getComponent<TransformComponent>();
	auto otherBody = other->getComponent<BodyComponent>();

	double myH = _body->getH(), myW = _body->getW();
	double otherH = otherBody->getH(), otherW = otherBody->getW();
	string otherTag = other->getTag();
	if (otherTag == "Suelo")
	{
		AmountOfCollision += 1;


		if (_transform->getPosition().getY() + (myH+ 0.4) * (M_TO_PIXEL * 2) < otherTransform->getPosition().getY())
		{
			OnGround = true;
 			_controller->ableJump();
		

		}
	}
	else if (otherTag == "EnemyBullet")
	{
		double damage = 0;
		damage = dynamic_cast<Bullet*>(other)->getDamage();
		subLife(damage);
	}
	else if (other->getTag() == "Moneda")
	{
		if (other->isActive())
		{
			auto coin = dynamic_cast<Coin*>(other);
			auto cant = coin->getValue();
			_money->store(cant);
			coin->destroy();
			cout << "Moneda cogida" << endl;
			cout << "Cantidad monedero: " << _money->getWallet() << endl;
			
			_playerPanel->updateCoinsCounter(_money->getWallet());
		}
		contact->SetEnabled(false);
	}
}

void Player::endCollision(GameComponent * other, b2Contact* contact)
{



	auto otherTransform = other->getComponent<TransformComponent>();
	auto otherBody = other->getComponent<BodyComponent>();

	double myH = _body->getH(), myW = _body->getW();
	double otherH = otherBody->getH(), otherW = otherBody->getW();

	string otherTag = other->getTag();
	if (otherTag == "Suelo")
	{
		AmountOfCollision -= 1;

		if (_transform->getPosition().getY() + (myH + 0.4) * (M_TO_PIXEL * 2) < otherTransform->getPosition().getY())
		{
			OnGround = false;

			if ((_body->getBody()->GetLinearVelocity().y < -2))
			{
				if(_controller->IsSpaceDown())
				_currentState = Player::Jumping;
				_controller->changeJump();
			}
			
		}
		
	}
}

void Player::subLife(int damage)
{
	_life.subLife(damage);
	if (!_dead)
	{
		if (_life.dead())
		{
			die();
			_hurt->die();
			_hurtArm->die();
			_dead = true;
		}
		else
		{
			_hurt->hurt();
			_hurtArm->hurt();
		}
	}
	_playerPanel->updateLifeBar(_life.getLife(), _life.getMaxLife());
}

void Player::die()
{
	cout << "Has Muerto" << endl;
	//getGame()->changeState(Play);
}

void Player::update()
{

	GameComponent::update();

	if (_anim->animationFinished() && _currentState != Player::Falling && _currentState != Player::Jumping)
	{
		if (_controller->currXDir() == 0)
		{
			_anim->playAnim(AnimatedSpriteComponent::Idle);
			_controller->setIsAttacking(false);
			_controller->setIsReloading(false);

			_currentState = Idle;
		}
		else
		{
			if (!_anim->isFlipped())
				_anim->playAnim(AnimatedSpriteComponent::Walk);
			else
				_anim->playAnim(AnimatedSpriteComponent::WalkBack);
			_controller->setIsAttacking(false);
			_controller->setIsReloading(false);

			_currentState = Walking;
		}
	}

	if (AmountOfCollision <= 0|| _body->getBody()->GetLinearVelocity().y > 2 && !OnGround)
	{
		if ( _currentState != Player::Falling && _currentState != Player::Dashing && _body->getBody()->GetLinearVelocity().y > 2)
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
			_playerPanel->updateDashViewer(_controller->amountDash());
		}
	}
	else
		_timer = SDL_GetTicks();

	//De momento todo el rato porque hay que cambiar cosas del player, porque esto es un caos
	_playerPanel->updateDashViewer(_controller->amountDash());
	_playerPanel->updateAmmoViewer(_weaponArm->getCurrentGun()->getClip(), _weaponArm->getCurrentGun()->getAmmo());

}

//Equipa un arma utilizando el array de atributos gameGuns de Game.h
void Player::equipGun(int gunIndex)
{
	if (_weaponArm == nullptr) //Si todavía no se ha inicializado _weaponArm, lo creo
	{
		_weaponArm = new PlayerArm(_armTextures[gunIndex], this, getGame(), _play, { 28,14 }); //Parámetros para la pistola
		addChild(_weaponArm);

		_hurtArm = _weaponArm->addComponent<HurtRenderComponent>();
	}
	else //Si no, simplemente cambio la textura
	{
		_weaponArm->setArmSprite(_armTextures[gunIndex]);
	}

	ShooterInterface* sh = getGame()->gameGuns[gunIndex].shooter;
	GunType type = GunType(getGame()->gameGuns[gunIndex].type);
	int mA = getGame()->gameGuns[gunIndex].maxAmmo;
	int mC = getGame()->gameGuns[gunIndex].maxClip;

	// TEMPORAL
	PoolWrapper* bp = _play->getBulletPool(type);
	//

	

	_weaponArm->setGun(new Gun(_weaponArm, sh, bp, type, mA, mC));
	//cout << "Gun equipada" << endl << endl << endl << endl << endl << endl;
	_equippedGun = type;
}

void Player::swapGun()
{
	equipGun((_equippedGun + 1) % _maxInventoryGuns); //equipa el arma del siguiente slot
	_playerPanel->updateWeaponryViewer();
}

void Player::reload()
{
	_controller->reload();
}