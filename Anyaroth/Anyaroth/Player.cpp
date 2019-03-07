#include "Player.h"
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
	double _gravScale = 3.5, _damping = 3.0;
	_body->getBody()->SetLinearDamping(_damping);
	_body->getBody()->SetGravityScale(_gravScale);


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
	//_movement = addComponent<MovingComponent>();


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
	//equipGun(_gunInventory[1]);

	//AmountOfCollision = 0;
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
		//AmountOfCollision += 1;


		if (_transform->getPosition().getY() + (myH+ 0.4) * (M_TO_PIXEL * 2) < otherTransform->getPosition().getY())
		{
			//_isGrounded = true;
 			//_controller->ableJump();
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
		//AmountOfCollision -= 1;

		//ESTO HACE QUE FALLE LA ANIMACION DE ANDAR, TENGO QUE INVESTIGARLO
		if (_transform->getPosition().getY() + (myH + 0.4) * (M_TO_PIXEL * 2) < otherTransform->getPosition().getY())
		{
			//_isGrounded = false;			
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
	return false;
}

void Player::update()
{
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	Uint32 mouse = SDL_GetMouseState(NULL, NULL);

	GameComponent::update();

	checkMovement(keyboard);

	if (mouse && SDL_BUTTON(SDL_BUTTON_RIGHT)/* && !_dashing*/) //&& !_isAttacking)
	{
		move(Vector2D(0, 0), 0);
		setCurrentState(Player::Attacking);
		_anim->playAnim(AnimatedSpriteComponent::MeleeKnife);//llamo animacion del melee dependiendo del arma cuerpo a cuerpo
	}

	
	//if (keyboard[SDL_SCANCODE_R] /*&& !_dashing*/) //&& !isReloading)
	//	reload();
	//if (keyboard[SDL_SCANCODE_Q]/*&& !_isSwapping && !_dashing*/)
	//{
	//	//_isSwapping = true;
	//	swapGun();  //llamo a función de recargar
	//	//_qPul = false;
	//}

	handleAnimations();











	/*if (_controller->amountDash() < _MaxDash)
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
	_playerPanel->updateAmmoViewer(_weaponArm->getCurrentGun()->getClip(), _weaponArm->getCurrentGun()->getAmmo());*/

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
	else if (keyboard[SDL_SCANCODE_S] && dashIsAble() && !_isGrounded /*&& !_isAttacking && _jumping && !_dashing && _amountOfDash > 0 && !_isReloading*/)
	{
		dash(Vector2D(0, 1));
	}
	else
		move(Vector2D(0, 0), _speed);

	if (keyboard[SDL_SCANCODE_SPACE] && _isGrounded/* && !_isAttacking && !_jumping && !_dashing && !_isReloading*/)
		jump();	

	_isGrounded = (abs(_body->getBody()->GetLinearVelocity().y) < 0.1/* && _isGrounded*/);
}

void Player::handleAnimations()
{
	auto vel = _body->getBody()->GetLinearVelocity();

	//Idle
	if (vel.x == 0 && vel.y == 0 && _isGrounded)
		_anim->playAnim(Idle);
	//Walking
	else if (abs(vel.x) > 0 && _isGrounded && !_anim->getCurrentAnim() != AnimatedSpriteComponent::Dash)
	{
		//Esto hay que cambiarlo
		if (!_anim->isFlipped())
			_anim->playAnim(AnimatedSpriteComponent::Walk);
		else
			_anim->playAnim(AnimatedSpriteComponent::WalkBack);
	}
	//Jumping&Falling
	if (vel.y != 0 && !_isGrounded)
	{
		if ((_anim->getCurrentAnim() != AnimatedSpriteComponent::Dash && _anim->getCurrentAnim() != AnimatedSpriteComponent::DashBack) ||
			((_anim->getCurrentAnim() == AnimatedSpriteComponent::Dash || _anim->getCurrentAnim() == AnimatedSpriteComponent::DashBack) && _anim->animationFinished()))
		{
			if (vel.y > 0.1 && !_isGrounded)
			{
				_anim->playAnim(AnimatedSpriteComponent::Falling);
				_isGrounded = false;
			}
			else if (vel.y < 0.1 && vel.y > -0.1 && !_isGrounded)
			{
				_anim->playAnim(AnimatedSpriteComponent::StartFalling);
				_isGrounded = false;
			}
			else if (vel.y < -0.1 && !_isGrounded)
			{
				_anim->playAnim(AnimatedSpriteComponent::Jump);
				_isGrounded = false;
			}
		}
	}
	



	/*if (_anim->animationFinished() && _currentState != Player::Falling && _currentState != Player::Jumping)
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

	}*/
}

void Player::move(const Vector2D& dir, const double& speed)
{
	if (abs(_body->getBody()->GetLinearVelocity().x) < speed) 
	{	
		_body->getBody()->SetLinearVelocity(b2Vec2(dir.getX() * speed, _body->getBody()->GetLinearVelocity().y));
		/*if (_isGrounded)
		{
			if (!_anim->isFlipped())
				_anim->playAnim(AnimatedSpriteComponent::Walk);
			else
				_anim->playAnim(AnimatedSpriteComponent::WalkBack);
		}*/
	}
}

void Player::reload()
{
	//_controller->reload();
}

void Player::dash(const Vector2D& dir)
{
	double force = 3250;
	move(Vector2D(0, 0), 0);
	_body->getBody()->ApplyLinearImpulse(b2Vec2(dir.getX() * force, dir.getY() * force * 1.5), _body->getBody()->GetWorldCenter(), true);
	_numDash--;
	_isDashing = false;

	if (!_anim->isFlipped())
		_anim->playAnim(AnimatedSpriteComponent::Dash);
	else
		_anim->playAnim(AnimatedSpriteComponent::DashBack);

	/*setCurrentState(Player::Dashing);*/
}


void Player::jump()
{
	//cout << "Salto" << endl;
	double _jumpForce = 1000;
	_body->getBody()->ApplyLinearImpulse(b2Vec2(0, -_jumpForce), _body->getBody()->GetWorldCenter(), true);
	_isGrounded = false;
	_anim->playAnim(AnimatedSpriteComponent::BeforeJump);
}

void Player::melee()
{
}

void Player::shoot()
{
	cout << "Disparo" << endl;
}
