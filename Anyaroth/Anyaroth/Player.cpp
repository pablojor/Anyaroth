#include "Player.h"
#include "TransformComponent.h"
#include "MovingComponent.h"
#include "Game.h"
#include "FollowingComponent.h"
#include "AnimatedSpriteComponent.h"
#include "PoolWrapper.h"
#include "Coin.h"
//#include "HurtRenderComponent.h"

Player::Player(Game* g, int xPos, int yPos) :  GameComponent(g, "Player")
{
	addComponent<Texture>(g->getTexture("Mk"));

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(xPos/*50*/,yPos /*180*/);


	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_dynamicBody);
	_body->getBody()->SetBullet(true);

	_body->setW(12);
	_body->setH(26);

	_body->filterCollisions(PLAYER, OBJECTS | FLOOR /*| ENEMY_BULLETS*/);
	_body->addCricleShape(b2Vec2(0, 1.1), 0.7, PLAYER, FLOOR);
	_body->getBody()->SetFixedRotation(true);
	double _gravScale = 3.5, _damping = 3.0;
	_body->getBody()->SetLinearDamping(_damping);
	_body->getBody()->SetGravityScale(_gravScale);

	//Sensor del suelo
	b2PolygonShape shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 2 / M_TO_PIXEL, b2Vec2(0, 2), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = PLAYER;
	fDef.filter.maskBits = FLOOR;
	fDef.isSensor = true;
	_body->addFixture(&fDef, this);


	_anim = addComponent<AnimatedSpriteComponent>();
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

	//_hurt = addComponent<HurtRenderComponent>();

	//Inicialización del vector de texturas del brazo
	_armTextures =
	{
		getGame()->getTexture("ArmPistol"),
		getGame()->getTexture("ArmShotgun")
	};

	_playerArm = new PlayerArm(g, this, { 28, 18 });
	addChild(_playerArm);

	//Inventario inicial
	_gunInventory.push_back(BasicGun);
	_gunInventory.push_back(BasicShotgun); //para probar
	//Equipa el arma inicial
	//equipGun(_gunInventory[1]);

	//Monedero
	_money = new Money();
}

Player::~Player()
{
	delete _money;
}

void Player::beginCollision(GameComponent * other, b2Contact* contact)
{
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();
	//Deteccion del suelo
	if ((fA->IsSensor() || fB->IsSensor()) && other->getTag() == "Suelo")
		_floorCount++;

	/*else if (other->getTag() == "EnemyBullet")
	{
		double damage = 0;
		damage = dynamic_cast<Bullet*>(other)->getDamage();
		subLife(damage);
	}*/
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
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();
	//Deteccion del suelo
	if ((fA->IsSensor() || fB->IsSensor()) && other->getTag() == "Suelo")
		_floorCount > 0 ? _floorCount-- : _floorCount = 0;
}

void Player::subLife(int damage)
{
	_life.subLife(damage);
	if (!_dead)
	{
		if (_life.dead())
		{
			die();
			//_hurt->die();
			//_hurtArm->die();
			_dead = true;
		}
		else
		{
			//_hurt->hurt();
			//_hurtArm->hurt();
		}
	}
	_playerPanel->updateLifeBar(_life.getLife(), _life.getMaxLife());
}

void Player::die()
{
	cout << "Has Muerto" << endl;
	//getGame()->changeState(Play);
}

bool Player::handleInput(const SDL_Event& event)
{
	GameComponent::handleInput(event);

	if (event.type == SDL_KEYDOWN && !event.key.repeat) // Captura solo el primer frame que se pulsa
	{
		if (event.key.keysym.sym == SDLK_q)
			swapGun();
		if (event.key.keysym.sym == SDLK_r)
			reload();
		if (event.key.keysym.sym == SDLK_LSHIFT)
			_isDashing = true;
	}
	else if (event.type == SDL_KEYUP && !event.key.repeat)
	{
		if (event.key.keysym.sym == SDLK_LSHIFT)
			_isDashing = false;
	}
	return false;
}

void Player::update()
{
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	GameComponent::update();

	checkMovement(keyboard);
	refreshCooldowns(16.6);
	handleAnimations();
}

//Equipa un arma utilizando el array de atributos gameGuns de Game.h
/*void Player::equipGun(int gunIndex)
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
	//_hurtArm = _weaponArm->addComponent<HurtRenderComponent>();
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
}*/

void Player::swapGun()
{
	cout << "Arma cambiada" << endl;
	//equipGun((_equippedGun + 1) % _maxInventoryGuns); //equipa el arma del siguiente slot
	_playerPanel->updateWeaponryViewer();
}

void Player::checkMovement(const Uint8* keyboard)
{
	double _speed = 15;

	if (keyboard[SDL_SCANCODE_A] && keyboard[SDL_SCANCODE_D] /*&& !_isAttacking && !_dashing && !_isReloading*/)
	{
		move(Vector2D(0, 0), _speed);
	}
	else if (keyboard[SDL_SCANCODE_A] /*&& !_isAttacking && !_dashing && !_isReloading*/)
	{
		if (dashIsAble())
			dash(Vector2D(-1, 0));
		else
			move(Vector2D(-1, 0), _speed);
	}
	else if (keyboard[SDL_SCANCODE_D] /*&& !_isAttacking && !_dashing && !_isReloading*/)
	{
		if (dashIsAble())
			dash(Vector2D(1, 0));
		else
			move(Vector2D(1, 0), _speed);
	}
	else if (keyboard[SDL_SCANCODE_S] && dashIsAble() && !isGrounded() /*&& !_isAttacking && _jumping && !_dashing && _amountOfDash > 0 && !_isReloading*/)
	{
		dash(Vector2D(0, 1));
	}
	else
		move(Vector2D(0, 0), _speed);

	if (keyboard[SDL_SCANCODE_SPACE] && isGrounded()/* && !_isAttacking && !_jumping && !_dashing && !_isReloading*/)
		jump();

	//Recarga
	if (keyboard[SDL_SCANCODE_R] && isGrounded())
		reload();

	//Cambio de arma
	//Creo que esta bien en el handleInput
}

void Player::handleAnimations()
{	//La animacion del Dash se activa en la funcion del Dash, 
	//ya que se trata de una habilidad y no del movimiento "normal" del personaje
	auto vel = _body->getBody()->GetLinearVelocity();
	bool isDashing = ((_anim->getCurrentAnim() == AnimatedSpriteComponent::Dash || _anim->getCurrentAnim() == AnimatedSpriteComponent::DashBack) && !_anim->animationFinished());

	//Idle&Walking
	if (isGrounded() && !isDashing)
	{
		//Idle
		if (vel.x == 0 && vel.y == 0 && isGrounded())
			_anim->playAnim(AnimatedSpriteComponent::Idle);
		//Walking
		else if (abs(vel.x) > 0 && isGrounded() && !isDashing)
		{
			//Esto hay que cambiarlo
			if (!_anim->isFlipped())
				_anim->playAnim(AnimatedSpriteComponent::Walk);
			else
				_anim->playAnim(AnimatedSpriteComponent::WalkBack);
		}
	}
	//Jumping&Falling (Si no esta en el suelo esta Saltando/Cayendo)
	else if (!isGrounded() && !isDashing)
	{
		if (!isDashing)
		{
			if (vel.y > 2)
			{
				_anim->playAnim(AnimatedSpriteComponent::Falling);
			}
			else if (vel.y < 2 && vel.y > -2)
			{
				_anim->playAnim(AnimatedSpriteComponent::StartFalling);
			}
			else if (vel.y < -2)
			{
				_anim->playAnim(AnimatedSpriteComponent::Jump);
			}
			setGrounded(false);
		}
	}
}

void Player::refreshCooldowns(const Uint32 & deltaTime)
{
	refreshDashCoolDown(deltaTime);
	refreshGunCadence(deltaTime);
}

void Player::refreshDashCoolDown(const Uint32& deltaTime)
{
	if (_numDash < _maxDash) {
		_dashCD -= deltaTime;
		if (_dashCD <= 0)
		{
			_numDash++;
			_playerPanel->updateDashViewer(_numDash);
			_dashCD = 3000; //Se restablecen los 3 segundos
		}
	}
}

void Player::refreshGunCadence(const Uint32 & deltaTime)
{
}

void Player::move(const Vector2D& dir, const double& speed)
{
	if (abs(_body->getBody()->GetLinearVelocity().x) < speed)
		_body->getBody()->SetLinearVelocity(b2Vec2(dir.getX() * speed, _body->getBody()->GetLinearVelocity().y));
}

void Player::reload()
{
	cout << "Arma recargada" << endl;
	_playerPanel->updateAmmoViewer(_playerArm->getCurrentGun()->getClip(), _playerArm->getCurrentGun()->getAmmo());
}

void Player::dash(const Vector2D& dir)
{
	double force = 3250;
	move(Vector2D(0, 0), 0);
	_body->getBody()->ApplyLinearImpulse(b2Vec2(dir.getX() * force, dir.getY() * force * 1.5), _body->getBody()->GetWorldCenter(), true);
	_numDash--;
	_isDashing = false;

	if ((!_anim->isFlipped() && dir.getX() > 0) || (_anim->isFlipped() && dir.getX() < 0))
		_anim->playAnim(AnimatedSpriteComponent::Dash);
	else
		_anim->playAnim(AnimatedSpriteComponent::DashBack);

	_playerPanel->updateDashViewer(_numDash);
}


void Player::jump()
{
	double _jumpForce = 1000;
	_body->getBody()->ApplyLinearImpulse(b2Vec2(0, -_jumpForce), _body->getBody()->GetWorldCenter(), true);
	setGrounded(false);
	_anim->playAnim(AnimatedSpriteComponent::BeforeJump);
}

void Player::melee()
{
	cout << "Melee realizado" << endl;
	_anim->playAnim(AnimatedSpriteComponent::MeleeKnife);
}

void Player::shoot()
{
	cout << "Disparo" << endl;
	_playerPanel->updateAmmoViewer(_playerArm->getCurrentGun()->getClip(), _playerArm->getCurrentGun()->getAmmo());
}