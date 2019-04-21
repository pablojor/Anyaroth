#include "Player.h"
#include "Game.h"
#include "Coin.h"
#include "AmmoPackage.h"
#include "AidKit.h"
#include "Axe.h"
#include "GunType_def.h"
#include "WeaponManager.h"


Player::Player(Game* game, int xPos, int yPos) : GameObject(game, "Player")
{
	addComponent<Texture>(game->getTexture("Mk"));

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(xPos, yPos);

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_dynamicBody);
	_body->getBody()->SetBullet(true);

	_body->setW(12);
	_body->setH(26);

	_body->filterCollisions(PLAYER, OBJECTS | FLOOR | PLATFORMS | ENEMY_BULLETS | MELEE);
	_body->addCricleShape(b2Vec2(0, 1.1), 0.7, PLAYER, FLOOR | PLATFORMS);
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
	fDef.filter.maskBits = FLOOR | PLATFORMS;
	fDef.isSensor = true;
	_body->addFixture(&fDef, this);

	_anim = addComponent<CustomAnimatedSpriteComponent>();
	_anim->addAnim(AnimatedSpriteComponent::Idle, 16, true);
	_anim->addAnim(AnimatedSpriteComponent::Walk, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::WalkBack, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::MeleeKnife, 6, false);
	_anim->addAnim(AnimatedSpriteComponent::MeleeSword, 13, false);
	_anim->addAnim(AnimatedSpriteComponent::BeforeJump, 1, false);
	_anim->addAnim(AnimatedSpriteComponent::Jump, 4, true);
	_anim->addAnim(AnimatedSpriteComponent::StartFalling, 2, false);
	_anim->addAnim(AnimatedSpriteComponent::Falling, 2, true);
	_anim->addAnim(AnimatedSpriteComponent::Hurt, 2, true);
	_anim->addAnim(AnimatedSpriteComponent::Dash, 5, false);
	_anim->addAnim(AnimatedSpriteComponent::DashDown, 3, true);
	_anim->addAnim(AnimatedSpriteComponent::DashBack, 5, false);
	_anim->addAnim(AnimatedSpriteComponent::MeleeHalberd, 5, false);
	_anim->addAnim(AnimatedSpriteComponent::PlayerDie, 35, false);

	//Brazo
	_playerArm = new PlayerArm(game, this, { 28, 15 });
	addChild(_playerArm);
	
	_currentGun = WeaponManager::getWeapon(game, ImprovedShotgun_Weapon);
	_otherGun = WeaponManager::getWeapon(game, BasicShotgun_Weapon);

	_playerArm->setTexture(_currentGun->getArmTexture());
	_playerArm->setAnimations(PlayerArmType);

	//Monedero
	_money = new Money();

	//Melee
	_melee = new Melee(game, { 15, 0 }, ENEMIES);
	addChild(_melee);
}

Player::~Player()
{
	delete _money;
	if (_currentGun != nullptr) delete _currentGun;
	if (_otherGun != nullptr) delete _otherGun;
}

void Player::beginCollision(GameObject * other, b2Contact* contact)
{
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();

	//Deteccion del suelo
	if ((fA->IsSensor() || fB->IsSensor()) && (other->getTag() == "Ground" || other->getTag() == "Platform"))
	{
		_floorCount++;
		setGrounded(true);
	}
	else if (other->getTag() == "EnemyBullet" || (other->getTag() == "Melee" && other != _melee))
	{
		int damage = other->getDamage();
		subLife(damage);
	}
	else if (other->getTag() == "Coin")
	{
		if (other->isActive())
		{
			auto coin = dynamic_cast<Coin*>(other);
			auto value = coin->getValue();

			coin->collect();

			_money->store(value);
			_playerPanel->updateCoinsCounter(_money->getWallet());
		}
		contact->SetEnabled(false);
	}
	else if (other->getTag() == "Ammo")
	{
		if (other->isActive())
		{
			auto ammo = dynamic_cast<AmmoPackage*>(other);
			auto value = ammo->getValue();

			ammo->collect();

			_currentGun->addAmmo(_currentGun->getMaxClip()*value);
			_playerPanel->updateAmmoViewer(_currentGun->getClip(), _currentGun->getMagazine());

			if (_otherGun != nullptr) _otherGun->addAmmo(_otherGun->getMaxClip()*value);
		}
		contact->SetEnabled(false);
	}
	else if (other->getTag() == "AidKit")
	{
		if (other->isActive())
		{
			auto aidKit = dynamic_cast<AidKit*>(other);
			auto value = aidKit->getValue();

			aidKit->collect();

			_life.addLife(value);
			_playerPanel->updateLifeBar(_life.getLife(), _life.getMaxLife());
		}
		contact->SetEnabled(false);
	}
	else if (other->getTag() == "Door")
	{
		_changeLevel = true;
	}
}

void Player::endCollision(GameObject * other, b2Contact* contact)
{
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();

	//Deteccion del suelo
	if ((fA->IsSensor() || fB->IsSensor()) && (other->getTag() == "Ground" || other->getTag() == "Platform"))
		_floorCount > 0 ? _floorCount-- : _floorCount = 0;
}

void Player::die()
{
	setDead(true);
	_deathCD = 3000;
	_playerArm->setActive(false);
	_anim->playAnim(AnimatedSpriteComponent::PlayerDie);
	_body->getBody()->SetLinearVelocity(b2Vec2(0.0, 0.0));
	_body->getBody()->SetAngularVelocity(0);

	_money->restartWallet();
	_playerPanel->updateCoinsCounter(_money->getWallet());
}

void Player::revive()
{
	setDead(false);
	_playerPanel->showDeathText(false);
	_playerArm->setActive(true);

	_life.resetLife();
	_playerPanel->updateLifeBar(_life.getLife(), _life.getMaxLife());

	_currentGun->resetAmmo();
	_playerPanel->updateAmmoViewer(_currentGun->getClip(), _currentGun->getMagazine());

	if (_otherGun != nullptr) _otherGun->resetAmmo();

	_playerPanel->resetDashViewer();
}

void Player::subLife(int damage)
{
	if (!isDashing())
	{
		_life.subLife(damage);

		if (!isDead())
		{
			if (_life.getLife() == 0)
			{
				die();
			}
			else
			{
				_anim->hurt();
				_playerArm->hurt();
			}
		}
		_playerPanel->updateLifeBar(_life.getLife(), _life.getMaxLife());
	}
}

bool Player::handleEvent(const SDL_Event& event)
{
	GameObject::handleEvent(event);

	if (!isDead() && !_inputFreezed)
	{
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
			else if (isJumping())
				cancelJump();
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
	}

	return false;
}

void Player::update(const double& deltaTime)
{
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);

	if (!isDead())
	{
		if (isDashing() || isMeleeing() || isReloading())
			_playerArm->setActive(false);
		else
			_playerArm->setActive(true);

		if (isDashing() || isMeleeing() || isReloading())
			_playerArm->setActive(false);
		else if (!_playerArm->isActive())
			_playerArm->setActive(true);
	}
	else
	{
		_playerPanel->showDeathText(true);
		_deathCD -= deltaTime;

		if (_deathCD <= 0)
			_changeLevel = true;
	}

	GameObject::update(deltaTime);

	refreshCooldowns(deltaTime);
	dashTimer(deltaTime);

	checkMovement(keyboard);
	checkMelee();

	handleAnimations();
}

void Player::swapGun()
{
	if (_otherGun != nullptr)
	{
		Gun* auxGun = _currentGun;
		_currentGun = _otherGun;
		_otherGun = auxGun;
		_playerArm->setTexture(_currentGun->getArmTexture());
		_playerPanel->updateAmmoViewer(_currentGun->getClip(), _currentGun->getMagazine());
		
		if (_currentGun->getIconTexture() != nullptr) _playerPanel->updateWeaponryViewer(_currentGun->getIconTexture());
	}
}

void Player::changeCurrentGun(Gun * gun)
{
	if (gun != nullptr) 
	{
		delete _currentGun;
		_currentGun = gun;
		_playerArm->setTexture(_currentGun->getArmTexture());
		_playerPanel->updateAmmoViewer(_currentGun->getClip(), _currentGun->getMagazine());
		_playerPanel->updateWeaponryViewer(_currentGun->getIconTexture());
	}
}

void Player::changeOtherGun(Gun * gun)
{
	if (gun != nullptr)
	{
		delete _otherGun;
		_otherGun = gun;
	}
}


void Player::checkMovement(const Uint8* keyboard)
{
	double _speed = 15;

	if (!isDead() && !_inputFreezed)
	{
		if (keyboard[SDL_SCANCODE_A] && keyboard[SDL_SCANCODE_D] && !isMeleeing() && !isDashing())
			move(Vector2D(0, 0), _speed);
		else if (keyboard[SDL_SCANCODE_A] && !isMeleeing() && !isDashing())
		{
			if (_isDashing && _dashEnabled)
				dash(Vector2D(-1, 0));
			else
				move(Vector2D(-1, 0), _speed);
		}
		else if (keyboard[SDL_SCANCODE_D] && !isMeleeing() && !isDashing())
		{
			if (_isDashing && _dashEnabled)
				dash(Vector2D(1, 0));
			else
				move(Vector2D(1, 0), _speed);
		}
		else if (keyboard[SDL_SCANCODE_S] && _isDashing && _dashEnabled && !isGrounded() && !isMeleeing()/*&& !isReloading()*/)
			dash(Vector2D(0, 1));
		else
			move(Vector2D(0, 0), _speed);

		if (keyboard[SDL_SCANCODE_SPACE] && !isMeleeing() && !isJumping()/*&& !isReloading()*/)
			if ((isGrounded() && !isFalling() && !isDashing()) || (!isGrounded() && isFalling() && _timeToJump > 0 && !isDashing()))
				jump();

		//Recarga
		if (canReload() && !isMeleeing() && !isDashing())
			reload();
		//Disparo
		if (_isShooting && !isMeleeing() && !isDashing())
			shoot();
		//Melee
		if (_isMeleeing && !isMeleeing() && isGrounded() && !isDashing())
			melee();
	}
}

void Player::handleAnimations()
{
	//La animacion del Dash se activa en la funcion del Dash, 
	//ya que se trata de una habilidad y no del movimiento "normal" del personaje
	auto vel = _body->getBody()->GetLinearVelocity();

	if (!isDead())
	{
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

		if ((isGrounded() || _body->getBody()->GetLinearVelocity().y == 0) && isDashing() && _dashDown)
		{
			_anim->playAnim(AnimatedSpriteComponent::Idle);
			_onDash = false;
			_dashDown = false;
			dashOff();
		}

		if (!isDashing())
			dashOff();
	}
}

void Player::refreshCooldowns(const double& deltaTime)
{
	refreshDashCoolDown(deltaTime);
	refreshGunCadence(deltaTime);

	if (!isGrounded() && _timeToJump > 0)
		_timeToJump -= deltaTime;
}

void Player::refreshDashCoolDown(const double& deltaTime)
{
	_dashCD -= deltaTime;
	if (_dashCD <= 0)
	{
		_dashCD = 1000 + _dashTime;
		_dashEnabled = true;
	}
}

void Player::dashTimer(const double & deltaTime)
{
	if (_onDash && !_dashDown)
	{
		_dashTime -= deltaTime;
		if (_dashTime <= 0)
		{
			_dashTime = 250;
			_onDash = false;
		}
	}
}

void Player::refreshGunCadence(const double& deltaTime)
{
	_currentGun->refreshGunCadence(deltaTime);
	if (_otherGun != nullptr)
		_otherGun->refreshGunCadence(deltaTime);
}

void Player::move(const Vector2D& dir, const double& speed)
{
	if (abs(_body->getBody()->GetLinearVelocity().x) < speed || dir.getX() == 0)
		_body->getBody()->ApplyLinearImpulseToCenter(b2Vec2(dir.getX() * speed, 0), true);
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
	if (_currentGun->getIconTexture() != nullptr) _playerPanel->updateWeaponryViewer(_currentGun->getIconTexture());
}

void Player::dash(const Vector2D& dir)
{
	double force = 40;
	_body->getBody()->SetLinearVelocity(b2Vec2(dir.getX() * force, dir.getY() * force * 1.5));

	_isDashing = false;
	_onDash = true;
	_dashEnabled = false;

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
		_dashDown = true;
	}

	_playerPanel->startAnimDashCD();
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

void Player::cancelJump()
{
	float penalization = 0.3f;
	_body->getBody()->SetLinearVelocity(b2Vec2(_body->getBody()->GetLinearVelocity().x, _body->getBody()->GetLinearVelocity().y * (1 - penalization)));
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