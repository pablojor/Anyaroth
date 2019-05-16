#include "Player.h"
#include "Game.h"
#include "Coin.h"
#include "AmmoPackage.h"
#include "AidKit.h"
#include "Sword.h"
#include "GunType_def.h"
#include "WeaponManager.h"
#include "ParticleManager.h"
#include "GameManager.h"
#include "OrbShotgun.h"


Player::Player(Game* game) : GameObject(game, "Player")
{
	_isPlayer = true;
	_affectedByExternalForces = true;

	addComponent<Texture>(game->getTexture("Mk"));

	_transform = addComponent<TransformComponent>();

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_dynamicBody);
	_body->getBody()->SetBullet(true);

	_body->setW(12);
	_body->setH(26);

	_body->filterCollisions(PLAYER, OBJECTS | FLOOR | PLATFORMS | ENEMY_BULLETS | MELEE | LASER);
	_body->addCricleShape(b2Vec2(0, 1.1), 0.7, PLAYER, FLOOR | PLATFORMS);
	_body->getBody()->SetFixedRotation(true);

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
	_anim->addAnim(AnimatedSpriteComponent::MeleeSword, 5, false);
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
	
	_currentGun = WeaponManager::getInstance()->getWeapon(game, Pistol_Weapon);

	_playerArm->setTexture(_currentGun->getArmTexture());
	_playerArm->setAnimations(_currentGun->getAnimType());

	//Monedero
	_money = new Money();

	//Melee
	_melee = WeaponManager::getInstance()->getMelee(game, Knife_Weapon);
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

		BodyComponent* otherBody = other->getComponent<BodyComponent>();
		_contactPoint = otherBody->getBody()->GetPosition() + b2Vec2(otherBody->getW() / 2, otherBody->getH() / 2);
	}
	else if (other->getTag() == "Coin")
	{
		if (other->isActive())
		{
			auto value = other->getValue();

			_money->store(value);
			_playerPanel->updateCoinsCounter(_money->getWallet());
		}
		contact->SetEnabled(false);
	}
	else if (other->getTag() == "Ammo")
	{
		if (other->isActive())
		{
			auto value = other->getValue();

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
			auto value = other->getValue();

			_life.addLife(value);
			_playerPanel->updateLifeBar(_life.getLife(), _life.getMaxLife());
		}
		contact->SetEnabled(false);
	}
	else if (other->getTag() == "Door")
	{
		GameManager::getInstance()->setChangeLevel(true);
	}
	else if (other->getTag() == "Death")
	{
		die();
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
	_isShooting = false;
	_noDamage = true;

	setDead(true);
	_deathCD = 3000;
	_playerArm->setActive(false);
	_anim->playAnim(AnimatedSpriteComponent::PlayerDie);
	_body->getBody()->SetLinearVelocity(b2Vec2(0.0, 0.0));
	_body->getBody()->SetAngularVelocity(0);

	_money->restartWallet();
	_playerPanel->updateCoinsCounter(_money->getWallet());

	if (_game->random(0, 100) > 50)
		_game->getSoundManager()->playSFX("die1");
	else
		_game->getSoundManager()->playSFX("die2");
}

void Player::revive()
{
	_noDamage = false;

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
	if (!isDashing() && !_noDamage)
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
				_spawnParticles = true;
        
				int rand = _game->random(0, 100);
				if (rand > 80)
					_game->getSoundManager()->playSFX("pain1");
				else if (rand > 64)
					_game->getSoundManager()->playSFX("pain2");
				else if (rand > 48)
					_game->getSoundManager()->playSFX("pain3");
				else if (rand > 32)
					_game->getSoundManager()->playSFX("pain4");
				else if (rand > 16)
					_game->getSoundManager()->playSFX("pain5");
				else
					_game->getSoundManager()->playSFX("pain6");

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
		if ((event.type == SDL_KEYDOWN && !event.key.repeat)) // Captura solo el primer frame que se pulsa
		{
			if (event.key.keysym.sym == SDLK_q)
				swapGun();
			else if (event.key.keysym.sym == SDLK_r && !isReloading())
			{
				_hasToReload = true;
				_isShooting = false;
			}
			else if (event.key.keysym.sym == SDLK_LSHIFT && !isDashing() && !_onDash && _dashEnabled)
				_isDashing = true;
		}
		else if (event.type == SDL_KEYUP && !event.key.repeat)
		{
			if (isJumping() && event.key.keysym.sym == SDLK_SPACE)
				cancelJump();
		}
		else if ((event.type == SDL_MOUSEBUTTONDOWN && event.button.state == SDL_PRESSED))
		{
			if (event.button.button == SDL_BUTTON_LEFT )
				_isShooting = true;
			else if (event.button.button == SDL_BUTTON_RIGHT && !isMeleeing())
				_isMeleeing = true;
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
				_isShooting = false;
			else if (event.button.button == SDL_BUTTON_RIGHT)
				_isMeleeing = false;
		}

		if (event.type == SDL_CONTROLLERBUTTONDOWN)
		{
			switch (event.cbutton.button)
			{
			case SDL_CONTROLLER_BUTTON_A:
				_jJump = true;
				break;
			case SDL_CONTROLLER_BUTTON_X:
				_hasToReload = true;
				break;
			case SDL_CONTROLLER_BUTTON_Y:
				swapGun();
				break;
			case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
				if(!isMeleeing())
					_isMeleeing = true;
				break;
			default:
				break;
			}
		}
		if (event.type == SDL_CONTROLLERBUTTONUP)
		{
			switch (event.cbutton.button)
			{
			case SDL_CONTROLLER_BUTTON_A:
				_jJump = false;
				 if (isJumping())
					cancelJump();
				break;
			case SDL_CONTROLLER_BUTTON_X:
				_hasToReload = false;
				break;
			case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
				_isMeleeing = false;
				break;
			default:
				break;
			}
		}

		else if (event.type == SDL_CONTROLLERAXISMOTION)
		{
			//X axis motion
			if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
			{
				//Left of dead zone
				if (event.caxis.value < -JOYSTICK_DEADZONE)
					_jMoveRight = !(_jMoveLeft = true);
				//Right of dead zone
				else if (event.caxis.value > JOYSTICK_DEADZONE)
					_jMoveRight = !(_jMoveLeft = false);
				else
					_jMoveLeft = _jMoveRight = false;
			}
			//Y axis
			else if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY)
			{
				//Left of dead zone
				if (event.caxis.value > JOYSTICK_DEADZONE)
					_jMoveDown = true;
				else
					_jMoveDown = false;
			}

			//Right trigger
			else if (event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
			{
				if (event.caxis.value > JOYSTICK_DEADZONE)
				{
					if (!_jShoot)
						_isShooting = _jShoot = true;
				}
				else
					_isShooting = _jShoot = false;
			}
			//Left trigger
			else if (event.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT && !isDashing() && !_onDash && _dashEnabled)
			{
				if (event.caxis.value > JOYSTICK_DEADZONE)
				{
					_isDashing = true;
				}
			}
		}
	}

	return false;
}

void Player::update(double deltaTime)
{
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);

	if(isDead() && !GameManager::getInstance()->getChangeLevel() && _deathCD > 0)
	{
		_playerPanel->showDeathText(true);
		_deathCD -= deltaTime;

		if (_deathCD <= 0)
			GameManager::getInstance()->setChangeLevel(true);
	}

	if (_spawnParticles)
	{
		_spawnParticles = false;
		double center_x = _body->getBody()->GetPosition().x + _body->getW() / 2, center_y = _body->getBody()->GetPosition().y + _body->getH() / 2;

		Vector2D direction = Vector2D((_contactPoint.x - center_x), (center_y - _contactPoint.y));
		ParticleManager::GetParticleManager()->CreateSpray(_game->getTexture("Blood"), Vector2D(_contactPoint.x*M_TO_PIXEL, _contactPoint.y*M_TO_PIXEL), direction, 4, 10, 30, 700, 5, 2);
	}

	checkMelee();
	handleAnimations();

	GameObject::update(deltaTime);


	if (_hasToReload && _playerArm->isReloading())
		_hasToReload = false;

	checkMovement(keyboard);

	refreshCooldowns(deltaTime);
	dashTimer(deltaTime);

}

void Player::swapGun()
{
	if (_otherGun != nullptr && !isReloading() && !_isShooting)
	{
		Gun* auxGun = _currentGun;
		_currentGun = _otherGun;
		_otherGun = auxGun;

		_playerArm->setTexture(_currentGun->getArmTexture());
		_playerPanel->updateAmmoViewer(_currentGun->getClip(), _currentGun->getMagazine());
		_playerArm->setAnimations(_currentGun->getAnimType());

		if (_currentGun->getIconTexture() != nullptr) _playerPanel->updateWeaponryViewer(_currentGun->getIconTexture());
	}
}

void Player::changeCurrentGun(Gun * gun)
{
	if (gun != nullptr)
	{
		 if ( _currentGun != nullptr) 
			 delete _currentGun;
		_currentGun = gun;

		_playerArm->setTexture(_currentGun->getArmTexture());
		_playerPanel->updateAmmoViewer(_currentGun->getClip(), _currentGun->getMagazine());
		_playerPanel->updateWeaponryViewer(_currentGun->getIconTexture());

		_playerArm->setAnimations(_currentGun->getAnimType());
	}
}

void Player::changeOtherGun(Gun * gun)
{
	if (gun != nullptr)
	{
		if (_otherGun != nullptr) 
			delete _otherGun;
		_otherGun = gun;
	}
}

void Player::checkMovement(const Uint8* keyboard)
{
	if (!isDead() && !_inputFreezed)
	{
		if (keyboard[SDL_SCANCODE_A] && keyboard[SDL_SCANCODE_D] && !isMeleeing() && !isDashing() && !_stunned)
			move(Vector2D(0, 0), _speed);
		else if ((keyboard[SDL_SCANCODE_A] || _jMoveLeft) && !isMeleeing() && !isDashing() && !_stunned)
		{
			if (_isDashing && _dashEnabled && !isReloading())
				dash(Vector2D(-1, 0));
			else
			{
				move(Vector2D(-1, 0), _speed);
				_isDashing = false;
			}
		}
		else if ((keyboard[SDL_SCANCODE_D] || _jMoveRight) && !isMeleeing() && !isDashing() && !_stunned)
		{
			if (_isDashing && _dashEnabled && !isReloading())
				dash(Vector2D(1, 0));
			else
			{
				move(Vector2D(1, 0), _speed);
				_isDashing = false;
			}
		}
		else if ((keyboard[SDL_SCANCODE_S] || _jMoveDown) && _isDashing && !isDashing() && _dashEnabled && !isGrounded() && !isMeleeing() && !isReloading())
			dash(Vector2D(0, 1));
		else
		{
			move(Vector2D(0, 0), _speed);
			_isDashing = false;
		}

		if ((keyboard[SDL_SCANCODE_SPACE] || _jJump) && !isMeleeing() && !isJumping() && !isReloading() && !_stunned)
			if ((isGrounded() && !isFalling() && !isDashing()) || (!isGrounded() && isFalling() && _timeToJump > 0 && !isDashing()))
				jump();

		if (_game->usingJoystick())
		{
			_jPosX = (SDL_GameControllerGetAxis(_game->getJoystick(), SDL_CONTROLLER_AXIS_RIGHTX));
			_jPosY = (SDL_GameControllerGetAxis(_game->getJoystick(), SDL_CONTROLLER_AXIS_RIGHTY));

			if (_jReleased)
				_jReleased = (_prevAxisX < 0 && _prevAxisX < _jPosX || _prevAxisX > 0 && _prevAxisX > _jPosX) || (_prevAxisY < 0 && _prevAxisY < _jPosY || _prevAxisY > 0 && _prevAxisY > _jPosY);

			int winWidth = 0;	int winHeight = 0;
			SDL_GetWindowSize(_game->getWindow(), &winWidth, &winHeight);
			double radius = 250 * _game->getCurrentState()->getMainCamera()->getCameraSize().distance({}) / Vector2D(winWidth, winHeight).distance({});

			if (_jPosX < -JOYSTICK_DEADZONE * 2 || _jPosX > JOYSTICK_DEADZONE * 2 || _jPosY < -JOYSTICK_DEADZONE * 2 || _jPosY > JOYSTICK_DEADZONE * 2)
				_jAngle = atan2(_jPosY, _jPosX);

			double mouseX = (_body->getBody()->GetPosition().x + _body->getW() / 2) * M_TO_PIXEL + cos(_jAngle) * radius;
			double mouseY = (_body->getBody()->GetPosition().y + _body->getH() / 2) * M_TO_PIXEL + sin(_jAngle) * radius;

			if ((abs(_jPosX - _prevAxisX) < JOYSTICK_DEADZONE * 2 && abs(_jPosY - _prevAxisY) < JOYSTICK_DEADZONE * 2) && !_jReleased)
				_game->getCurrentState()->setMousePositionInWorld({ mouseX,mouseY });
			else
				_jReleased = true;

			_prevAxisX = _jPosX;
			_prevAxisY = _jPosY;
		}

		//Recarga
		if (canReload() && !isMeleeing() && !isDashing())
			reload();
		//Disparo
		if (_isShooting && !isMeleeing() && !isDashing() && !_hasToReload && !isReloading())
			shoot();
		//Melee
		if (_isMeleeing && !isMeleeing() && isGrounded() && !isDashing() && !_melee->isActive())
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
		if (isGrounded() && !isDashing() && !isMeleeing() && !_stunned)
		{
			//Idle
			if (abs(vel.x) <= 5.f /*&& vel.y == 0*/ && isGrounded())
				_anim->playAnim(AnimatedSpriteComponent::Idle);
			//Walking
			else if (abs(vel.x) > 5.f && isGrounded() && !isDashing())
			{
				if ((!_anim->isFlipped() && vel.x > 0) || (_anim->isFlipped() && vel.x < 0))
					_anim->playAnim(AnimatedSpriteComponent::Walk);
				else
					_anim->playAnim(AnimatedSpriteComponent::WalkBack);
			}
		}
		else if (!isGrounded() && !isDashing() && !isMeleeing() && !_stunned) //Jumping&Falling (Si no esta en el suelo esta Saltando/Cayendo)
		{
			if (vel.y > 2)
				_anim->playAnim(AnimatedSpriteComponent::Falling);
			else if (vel.y < 2 && vel.y > -2)
				_anim->playAnim(AnimatedSpriteComponent::StartFalling);
			else if (vel.y < -2)
				_anim->playAnim(AnimatedSpriteComponent::Jump);

			setGrounded(false);
		}

		if (isDashing() || isMeleeing())
			_playerArm->setActive(false);
		else if (!_playerArm->isActive() && !isDashing() && !isMeleeing())
		{
			_playerArm->setActive(true);
			_anim->playAnim(AnimatedSpriteComponent::Idle);
		}

		if ((isGrounded() || _body->getBody()->GetLinearVelocity().y == 0) && isDashing() && _dashDown)
		{
			_anim->playAnim(AnimatedSpriteComponent::Idle);
			_onDash = false;
			_dashDown = false;
			_isDashing = false;
			dashOff();
		}

		if (!isDashing())
			dashOff();
	}
}

void Player::refreshCooldowns(double deltaTime)
{
	refreshDashCoolDown(deltaTime);
	refreshGunCadence(deltaTime);
	refreshStunTime(deltaTime);

	if (!isGrounded() && _timeToJump > 0)
		_timeToJump -= deltaTime;
	_runningSpawnParticle -= deltaTime;
}

void Player::refreshDashCoolDown(double deltaTime)
{
	if (!_dashEnabled) 
	{
		_dashCD -= deltaTime;
		if (_dashCD <= 0)
		{
			_dashTime = 250;
			_dashCD = 1000 + _dashTime;
			_dashEnabled = true;
		}
	}
}

void Player::dashTimer(double deltaTime)
{
	if (_onDash)
	{
		if (!_dashDown)
			_dashTime -= deltaTime;

		_dashParticleTime -= deltaTime;
		if (_dashTime <= 0 && !_dashDown)
		{
			_dashParticleTime = 40;
			_dashTime = 250;
			_onDash = false;
			_isDashing = false;
		}
		if (_dashParticleTime <= 0)
		{
			if (_anim->getCurrentAnim() == AnimatedSpriteComponent::Dash)
			{
				if (!_anim->isFlipped())
					ParticleManager::GetParticleManager()->CreateSimpleParticle(_game->getTexture("DashTrail"), 1, Vector2D((_body->getBody()->GetPosition().x)*M_TO_PIXEL, (_body->getBody()->GetPosition().y)*M_TO_PIXEL), 0, 0, 120);
				else
					ParticleManager::GetParticleManager()->CreateSimpleParticle(_game->getTexture("DashTrailFlip"), 1, Vector2D((_body->getBody()->GetPosition().x)*M_TO_PIXEL, (_body->getBody()->GetPosition().y)*M_TO_PIXEL), 0, 0, 120);
			}
			else if (_anim->getCurrentAnim() == AnimatedSpriteComponent::DashBack)
			{
				if (!_anim->isFlipped())
					ParticleManager::GetParticleManager()->CreateSimpleParticle(_game->getTexture("DashBackTrail"), 1, Vector2D((_body->getBody()->GetPosition().x)*M_TO_PIXEL, (_body->getBody()->GetPosition().y)*M_TO_PIXEL), 0, 0, 120);
				else
					ParticleManager::GetParticleManager()->CreateSimpleParticle(_game->getTexture("DashBackTrailFlip"), 1, Vector2D((_body->getBody()->GetPosition().x)*M_TO_PIXEL, (_body->getBody()->GetPosition().y)*M_TO_PIXEL), 0, 0, 120);
			}
			else
			{
				if (!_anim->isFlipped())
					ParticleManager::GetParticleManager()->CreateSimpleParticle(_game->getTexture("DashDownTrail"), 1, Vector2D((_body->getBody()->GetPosition().x)*M_TO_PIXEL, (_body->getBody()->GetPosition().y)*M_TO_PIXEL), 0, 0, 120);
				else
					ParticleManager::GetParticleManager()->CreateSimpleParticle(_game->getTexture("DashDownTrailFlip"), 1, Vector2D((_body->getBody()->GetPosition().x)*M_TO_PIXEL, (_body->getBody()->GetPosition().y)*M_TO_PIXEL), 0, 0, 120);
			}
			_dashParticleTime = 40;
		}
	}
}

void Player::refreshGunCadence(double deltaTime)
{
	_currentGun->refreshGunCadence(deltaTime);

	if (_otherGun != nullptr)
		_otherGun->refreshGunCadence(deltaTime);
}

void Player::refreshStunTime(double deltaTime)
{
	if (_stunned)
	{
		_stunTime -= deltaTime;

		if (_stunTime <= 0)
		{
			_stunTime = 1000;
			_stunned = false;
			_playerArm->getComponent<CustomAnimatedSpriteComponent>()->setVisible(true);
		}
	}
}

void Player::move(const Vector2D& dir, double speed)
{
	if (abs(_body->getBody()->GetLinearVelocity().x) < speed || dir.getX() == 0)
		_body->getBody()->ApplyLinearImpulseToCenter(b2Vec2(dir.getX() * speed, 0), true);
	else
		_body->getBody()->SetLinearVelocity(b2Vec2(dir.getX() * speed, _body->getBody()->GetLinearVelocity().y));

	if (_floorCount > 0 && dir.getX()!=0 && _runningSpawnParticle<=0)
	{
		_runningSpawnParticle = 40;
		ParticleManager::GetParticleManager()->CreateFountain(_game->getTexture(_dustParticle), Vector2D((_body->getBody()->GetPosition().x+_body->getW() *-dir.getX())*M_TO_PIXEL, (_body->getBody()->GetPosition().y+_body->getH()*1.2)*M_TO_PIXEL),Vector2D(-dir.getX(),1),0,10/*spped*/,15,100,10, 100,3);
	}
}

void Player::reload()
{
	_playerArm->reload();
	_currentGun->reload();
	_game->getSoundManager()->playSFX("reload");
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

void Player::resetDustParticle()
{
	int level = GameManager::getInstance()->getCurrentLevel();

	if (level <= 6)
	{
		_dustParticle = "Dust1";
	}
	else if (level <= 12)
	{
		_dustParticle = "Dust2";
	}
	else
	{
		_dustParticle = "Dust3";
	}
}


void Player::stopPlayer()
{
	_body->getBody()->SetLinearVelocity(b2Vec2(0.0, 0.0));
	_body->getBody()->SetAngularVelocity(0);

	_hasToReload = false,
	_isShooting = false,
	_isMeleeing = false,
	_isDashing = false,
	_onDash = false,
	_dashDown = false,
	_jJump = false,
	_jShoot = false,
	_jMoveLeft = false,
	_jMoveDown = false,
	_jMoveRight = false,
	_jReleased = false;
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

	_game->getSoundManager()->playSFX("dash");
	_playerPanel->startAnimDashCD();
}

void Player::dashOff()
{
	_body->getBody()->SetLinearDamping(_damping);
	_body->getBody()->SetGravityScale(_gravScale);
}

void Player::jump()
{
	_body->getBody()->SetLinearVelocity(b2Vec2(_body->getBody()->GetLinearVelocity().x, 0));
	_body->getBody()->ApplyLinearImpulse(b2Vec2(0, -_jumpForce), _body->getBody()->GetWorldCenter(), true);

	setGrounded(false);
	_timeToJump = 0.f;

	_anim->playAnim(AnimatedSpriteComponent::BeforeJump); 
	ParticleManager::GetParticleManager()->CreateSpray(_game->getTexture(_dustParticle), Vector2D((_body->getBody()->GetPosition().x+_body->getW()/2)*M_TO_PIXEL, (_body->getBody()->GetPosition().y + _body->getH())*M_TO_PIXEL), Vector2D(-1, 1), 10, 20, 20, 400, 10, 3);
	ParticleManager::GetParticleManager()->CreateSpray(_game->getTexture(_dustParticle), Vector2D((_body->getBody()->GetPosition().x - _body->getW() / 2)*M_TO_PIXEL, (_body->getBody()->GetPosition().y + _body->getH())*M_TO_PIXEL), Vector2D(1, 1), 10, 20, 20, 400, 10, 3);
  
	_game->getSoundManager()->playSFX("jump");
}

void Player::cancelJump()
{
	float penalization = 0.4f;
	_body->getBody()->SetLinearVelocity(b2Vec2(_body->getBody()->GetLinearVelocity().x, _body->getBody()->GetLinearVelocity().y * (1 - penalization)));
}

void Player::stunPlayer()
{
	if (isGrounded())
	{
		_stunned = true;
		_anim->playAnim(AnimatedSpriteComponent::Hurt);
		_playerArm->getComponent<CustomAnimatedSpriteComponent>()->setVisible(false);
	}
}

void Player::melee()
{
	if(_melee->isActive())
		_melee->endMelee();

	_anim->playAnim(_meleeAnim);

	_melee->meleeAttack(_body->getBody()->GetPosition().x* M_TO_PIXEL, _body->getBody()->GetPosition().y*M_TO_PIXEL, (_anim->isFlipped()) ? -1 : 1);
	_isMeleeing = false;

	_game->getSoundManager()->playSFX("melee");
}

void Player::shoot()
{
	if (!_stunned)
	{
		if (_currentGun->canShoot() && !isReloading())
		{
			_playerArm->shoot();
			_currentGun->shoot(_playerBulletPool, _playerArm->getPosition(), !_anim->isFlipped() ? _playerArm->getAngle() : _playerArm->getAngle() + 180, "Bullet");
			_playerPanel->updateAmmoViewer(_currentGun->getClip(), _currentGun->getMagazine());

			if (!_currentGun->isAutomatic())
				_isShooting = false;
		}
		else if (_currentGun->hasBullets())
		{
			_playerArm->shoot();
			_game->getSoundManager()->playSFX("emptyGun");
			_isShooting = false;
		}
		else if (!_currentGun->canShoot() && !_currentGun->isAutomatic())
		{
			_playerArm->shoot();
			_isShooting = false;
		}


		if (_currentGun->hasToBeReloaded())
			_hasToReload = true;
	}
}

bool Player::canReload()
{
	if (_hasToReload && _currentGun->canReload())
		return true;

	_hasToReload = false;
	return false;
}

void Player::checkMelee()
{
	if (!isMeleeing() && _melee != nullptr && _melee->isActive())
		_melee->endMelee();
}

void Player::changeMelee(Melee* newMelee, int anim)
{
	if (_melee != nullptr)
		_melee->destroy();
	_melee = newMelee;
	addChild(_melee);
	_meleeAnim = anim;
}

void Player::clearAmmo() 
{ 
	_currentGun->clearAmmo(); 
	_playerPanel->updateAmmoViewer(_currentGun->getClip(), _currentGun->getMagazine());
}