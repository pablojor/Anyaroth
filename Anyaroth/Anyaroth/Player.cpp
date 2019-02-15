#include "Player.h"
#include "PlayerControllerComponent.h"
#include "TransformComponent.h"
#include "MovingComponent.h"
#include "BoxCollider.h"
#include "Game.h"
#include "FollowingComponent.h"

Player::Player(Texture* texture, Game* g) : GameComponent(g)
{
	//Siempre primero los componentes que tienen que estar SI o SI.
	addComponent<Texture>(texture);
	//Resto de componentes

	//addComponent<FollowingComponent>(this);

	auto transform = addComponent<TransformComponent>();		//Como en el metodo anterior se ha creado este componente, imprime por pantalla que ya existe uno.

	auto anim = addComponent<AnimatedSpriteComponent>();		//Como depende de Transform, en su constructura crea una si no ha encontrado Transform en el objeto.

	addComponent<MovingComponent>();
	addComponent<PlayerControllerComponent>();
	addComponent<BoxCollider>();

	anim->addAnim(AnimatedSpriteComponent::Idle, 16, true);
	anim->addAnim(AnimatedSpriteComponent::Walk, 10, true);
	anim->addAnim(AnimatedSpriteComponent::WalkBack, 10, true);


	transform->setScale(RESOLUTION); //el 3 sería el factor de resolución!!
	transform->setPosition(340, 400);
	transform->setAnchor(0, 0);
	//transform->setRotation(45);

	//Brazo con arma
	_weaponArm = new Arm(getGame()->getTexture("Arm"), this, getGame(), { 42,43 });
	addChild(_weaponArm);

	//Equipa el arma inicial
	equipGun(getGame()->BasicGun);

}

Player::~Player()
{
}

void Player::update()
{
	GameComponent::update();

	//transform->setRotation(transform->getRotation() + 0.2);
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