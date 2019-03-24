#include "Player.h"
#include "Game.h"
#include "Coin.h"
#include "BasicPistol.h"
#include "BasicShotgun.h"
#include "Axe.h"


Player::Player(Game* game, int xPos, int yPos) :  GameComponent(game, "Player")
{
	_game = game;

	addComponent<Texture>(game->getTexture("Mk"));

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(xPos, yPos);

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_dynamicBody);
	_body->getBody()->SetBullet(true);

	_body->setW(12);
	_body->setH(26);
	
	_body->filterCollisions(PLAYER, OBJECTS | FLOOR  | ENEMY_BULLETS);
	_body->addCricleShape(b2Vec2(0, 1.1), 0.7, PLAYER, FLOOR);
	_body->getBody()->SetFixedRotation(true);

	double _gravScale = 3.5, _damping = 3.0;
	_body->getBody()->SetLinearDamping(_damping);
	_body->getBody()->SetGravityScale(_gravScale);

	//Sensor del suelo
	b2PolygonShape shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 3 / M_TO_PIXEL, b2Vec2(0, 3), 0);
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

	_hurt = addComponent<HurtRenderComponent>();
	
	//Brazo
	_playerArm = new PlayerArm(game, this, { 28, 18 });
	addChild(_playerArm);

	//Armas (de momento esas dos)
	_currentGun = new BasicPistol(game);
	_otherGun = new BasicShotgun(game);
	_playerArm->setTexture(_currentGun->getArmTexture());

	//Monedero
	_money = new Money();

	//Melee
	_melee = new Melee(game);
	addChild(_melee);
}

Player::~Player()
{
	delete _money;
	delete _currentGun;
	delete _otherGun;
}

void Player::beginCollision(GameComponent * other, b2Contact* contact)
{
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();

	//Deteccion del suelo
	if ((fA->IsSensor() || fB->IsSensor()) && other->getTag() == "Ground")
	{
		_floorCount++;
		setGrounded(true);
	}
	else if (other->getTag() == "EnemyBullet")
	{
		double damage = 0;
		damage = dynamic_cast<Bullet*>(other)->getDamage();
		subLife(damage);
	}
	else if (other->getTag() == "Coin")
	{
		if (other->isActive())
		{
			auto coin = dynamic_cast<Coin*>(other);
			auto cant = coin->getValue();
			_money->store(cant);
			coin->collect();
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
	if ((fA->IsSensor() || fB->IsSensor()) && other->getTag() == "Ground")
		_floorCount > 0 ? _floorCount-- : _floorCount = 0;
}

void Player::die()
{
	_dead = true;
	_body->getBody()->SetLinearVelocity(b2Vec2(0.0, 0.0));
	_body->getBody()->SetAngularVelocity(0);
}

void Player::revive()
{
	_dead = false;

	_life.resetLife();
	_playerPanel->updateLifeBar(_life.getLife(), _life.getMaxLife());

	_money->restartWallet();
	_playerPanel->updateCoinsCounter(_money->getWallet());

	_currentGun->resetAmmo();
	_otherGun->resetAmmo();
	_playerPanel->updateAmmoViewer(_currentGun->getClip(), _currentGun->getMagazine());
}

void Player::subLife(int damage)
{
	if (!isDashing())
	{
		_life.subLife(damage);
		if (!_dead)
		{
			if (_life.dead())
			{
				die();
				//_hurt->die();
			}
			else
				_hurt->hurt();
		}
		_playerPanel->updateLifeBar(_life.getLife(), _life.getMaxLife());
	}
}

bool Player::handleInput(const SDL_Event& event)
{
	GameComponent::handleInput(event);

	if (event.type == SDL_KEYDOWN && !event.key.repeat) // Captura solo el primer frame que se pulsa
	{
		if (event.key.keysym.sym == SDLK_q)
			swapGun();
		else if (event.key.keysym.sym == SDLK_r)
			_isReloading = true;
		else if (event.key.keysym.sym == SDLK_LSHIFT)
			_isDashing = true;
	}
	else if (event.type == SDL_KEYUP && !event.key.repeat)
	{
		if (event.key.keysym.sym == SDLK_r)
			_isReloading = false;
		else if (event.key.keysym.sym == SDLK_LSHIFT)
			_isDashing = false;
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.state == SDL_PRESSED)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
			_isShooting = true;
		else if (event.button.button == SDL_BUTTON_RIGHT)
			_isMeleeing = true;
	}
	else if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
			_isShooting = false;
		else if (event.button.button == SDL_BUTTON_RIGHT)
			_isMeleeing = false;
	}
	return false;
}

void Player::update(double time)
{
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	GameComponent::update(time);

	checkMovement(keyboard);
	checkMelee();
	refreshCooldowns(time);
	handleAnimations();
}

void Player::swapGun()
{
	Gun* auxGun = _currentGun;
	_currentGun = _otherGun;
	_otherGun = auxGun;
	_playerArm->setTexture(_currentGun->getArmTexture());
	_playerPanel->updateAmmoViewer(_currentGun->getClip(), _currentGun->getMagazine());
	_playerPanel->updateWeaponryViewer();
}


void Player::checkMovement(const Uint8* keyboard)
{
	double _speed = 15;

	if (keyboard[SDL_SCANCODE_A] && keyboard[SDL_SCANCODE_D] && !isMeleeing() && !isDashing())
		move(Vector2D(0, 0), _speed);	
	else if (keyboard[SDL_SCANCODE_A] && !isMeleeing() && !isDashing())
	{
		if (dashIsAble())
			dash(Vector2D(-1, 0));
		else
			move(Vector2D(-1, 0), _speed);
	}
	else if (keyboard[SDL_SCANCODE_D] && !isMeleeing() && !isDashing())
	{
		if (dashIsAble())
			dash(Vector2D(1, 0));
		else
			move(Vector2D(1, 0), _speed);
	}
	else if (keyboard[SDL_SCANCODE_S] && dashIsAble() && !isGrounded() && !isMeleeing()/*&& !isReloading()*/)
		dash(Vector2D(0, 1));
	else
		move(Vector2D(0, 0), _speed);

	if (keyboard[SDL_SCANCODE_SPACE] && !isMeleeing() && !isJumping()/*&& !isReloading()*/)
		if((isGrounded() && !isFalling()) || (!isGrounded() && isFalling() && _timeToJump > 0))
			jump();

	//Recarga
	if (canReload() && !isMeleeing())
		reload();
	//Disparo
	if (_isShooting && !isMeleeing())
		shoot();
	//Melee
	if (_isMeleeing && !isMeleeing() && isGrounded())
		melee();
}

void Player::handleAnimations()
{	
	//La animacion del Dash se activa en la funcion del Dash, 
	//ya que se trata de una habilidad y no del movimiento "normal" del personaje
	auto vel = _body->getBody()->GetLinearVelocity();

	//Idle&Walking
	if (isGrounded() && !isDashing() && !isMeleeing())
	{
		//Idle
		if (vel.x == 0 && vel.y == 0 && isGrounded())
			_anim->playAnim(AnimatedSpriteComponent::Idle);
		//Walking
		else if (abs(vel.x) > 0 && isGrounded() && !isDashing())
		{
			if ((!_anim->isFlipped() && vel.x > 0) || (_anim->isFlipped() && vel.x < 0))
				_anim->playAnim(AnimatedSpriteComponent::Walk);
			else
				_anim->playAnim(AnimatedSpriteComponent::WalkBack);
		}
	}
	else if (!isGrounded() && !isDashing() && !isMeleeing()) //Jumping&Falling (Si no esta en el suelo esta Saltando/Cayendo)
	{
		if (vel.y > 2)
			_anim->playAnim(AnimatedSpriteComponent::Falling);
		else if (vel.y < 2 && vel.y > -2)
			_anim->playAnim(AnimatedSpriteComponent::StartFalling);
		else if (vel.y < -2)
			_anim->playAnim(AnimatedSpriteComponent::Jump);

		setGrounded(false);		
	}

	if ((isGrounded() || _body->getBody()->GetLinearVelocity().y == 0) && isDashing() && dashDown)
	{
		_anim->playAnim(AnimatedSpriteComponent::Idle);
		_onDash = false;
		dashDown = false;
		dashOff();		
	}

	if (!isDashing())
		dashOff();
}

void Player::refreshCooldowns(const double& deltaTime)
{
	dashTimer(deltaTime);
	refreshDashCoolDown(deltaTime);
	refreshGunCadence(deltaTime);

	if (!isGrounded() && _timeToJump > 0)
		_timeToJump -= deltaTime;
}

void Player::refreshDashCoolDown(const double& deltaTime)
{
	if (_numDash < _maxDash)
	{
		_dashCD -= deltaTime;
		if (_dashCD <= 0)
		{
			_numDash++;
			_playerPanel->updateDashViewer(_numDash);
			_dashCD = 3000; //Se restablecen los 3 segundos
		}
	}
}

void Player::dashTimer(const double & deltaTime)
{
	if (_onDash&&!dashDown)
	{
		dashDur -= deltaTime;
		if (dashDur <= 0)
		{
			dashDur = 250;
			_onDash = false;
		}
	}
}

void Player::refreshGunCadence(const double& deltaTime)
{
	_currentGun->refreshGunCadence(deltaTime);
	_otherGun->refreshGunCadence(deltaTime);
}

void Player::move(const Vector2D& dir, const double& speed)
{
	if (abs(_body->getBody()->GetLinearVelocity().x) < speed ||dir.getX()==0)
		_body->getBody()->ApplyLinearImpulseToCenter(b2Vec2(dir.getX() * speed, 0),true);
	else
		_body->getBody()->SetLinearVelocity(b2Vec2(dir.getX() * speed, _body->getBody()->GetLinearVelocity().y));
}

void Player::reload()
{
	_playerArm->reload();
	_currentGun->reload();
	_playerPanel->updateAmmoViewer(_currentGun->getClip(), _currentGun->getMagazine());
}

void Player::setPlayerPanel(PlayerPanel * p)
{
	_playerPanel = p;

	//Actualizamos de primeras el aspecto del Panel del Jugador
	_playerPanel->updateAmmoViewer(_currentGun->getClip(), _currentGun->getMagazine());
	_playerPanel->updateDashViewer(_dashCD);
	_playerPanel->updateCoinsCounter(_money->getWallet());
	_playerPanel->updateLifeBar(_life.getLife(), _life.getMaxLife());
}

bool Player::isDashing() const
{
	return _onDash;
}

bool Player::isMeleeing() const
{
	return ((_anim->getCurrentAnim() == AnimatedSpriteComponent::MeleeKnife || _anim->getCurrentAnim() == AnimatedSpriteComponent::MeleeKnife) && !_anim->animationFinished());
}

bool Player::isReloading() const
{
	return false;
}

bool Player::isJumping() const
{
	return (_anim->getCurrentAnim() == AnimatedSpriteComponent::BeforeJump || _anim->getCurrentAnim() == AnimatedSpriteComponent::Jump) && !_anim->animationFinished();
}

bool Player::isFalling() const
{
	return (_anim->getCurrentAnim() == AnimatedSpriteComponent::Falling || _anim->getCurrentAnim() == AnimatedSpriteComponent::StartFalling) && !_anim->animationFinished();
}

void Player::dash(const Vector2D& dir)
{
	double force = 40;
	_body->getBody()->SetLinearVelocity(b2Vec2(dir.getX() * force, dir.getY() * force * 1.5));
	_numDash--;
	_isDashing = false;
	_onDash = true;
	_body->getBody()->SetLinearDamping(0);
	_body->getBody()->SetGravityScale(0);

	if (dir.getY() == 0) 
	{
		if ((!_anim->isFlipped() && dir.getX() > 0) || (_anim->isFlipped() && dir.getX() < 0))
			_anim->playAnim(AnimatedSpriteComponent::Dash);
		else
			_anim->playAnim(AnimatedSpriteComponent::DashBack);
	}
	else
	{
		_anim->playAnim(AnimatedSpriteComponent::DashDown);
		dashDown = true;
	}

	_playerPanel->updateDashViewer(_numDash);
}

void Player::dashOff()
{
	double _gravScale = 4, _damping = 3.0;
	_body->getBody()->SetLinearDamping(_damping);
	_body->getBody()->SetGravityScale(_gravScale);
}

void Player::jump()
{
	double _jumpForce = 360;
	_body->getBody()->SetLinearVelocity(b2Vec2(_body->getBody()->GetLinearVelocity().x, 0));
	_body->getBody()->ApplyLinearImpulse(b2Vec2(0, -_jumpForce), _body->getBody()->GetWorldCenter(), true);
	setGrounded(false);
	_timeToJump = 0.f;
	_anim->playAnim(AnimatedSpriteComponent::BeforeJump);
}

void Player::melee()
{
	if (_melee->isActive())
		_melee->endMelee();

	_anim->playAnim(AnimatedSpriteComponent::MeleeKnife);
	_melee->meleeAttack(_body->getBody()->GetPosition().x* M_TO_PIXEL, _body->getBody()->GetPosition().y*M_TO_PIXEL, (_anim->isFlipped()) ? -1 : 1);
	_isMeleeing = false;
}

void Player::shoot()
{
	if (_currentGun->canShoot()/*&& isReloading()*/)
	{
		_playerArm->shoot();
		_currentGun->shoot(_playerBulletPool, _playerArm->getPosition(), !_anim->isFlipped() ? _playerArm->getAngle() : _playerArm->getAngle() + 180, "Bullet");
		_playerPanel->updateAmmoViewer(_currentGun->getClip(), _currentGun->getMagazine());
		
		if (!_currentGun->isAutomatic())
			_isShooting = false;
	}

	if (_currentGun->hasToBeReloaded())
		reload();
}

bool Player::canReload()
{
	if (_isReloading && isGrounded())
		return _currentGun->canReload();

	_isReloading = false;
	return false;
}

void Player::checkMelee()
{
	if (!isMeleeing() && _melee != nullptr && _melee->isActive())
		_melee->endMelee();
}

void Player::changeMelee(Melee* newMelee)
{
	_melee = newMelee;
}