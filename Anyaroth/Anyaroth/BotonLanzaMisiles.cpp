#include "BotonLanzaMisiles.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Game.h"


BotonLanzaMisiles::BotonLanzaMisiles(Boss1* Boss, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : _boss(Boss), _play(play), GameComponent(g, tag)
{
	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(posIni.getX(), posIni.getY());

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_staticBody);

	_body->setW(20);
	_body->setH(20);
	_body->filterCollisions(MISILLAUNCHER, PLAYER );
	_body->getBody()->GetFixtureList()->SetSensor(true);
	_body->getBody()->SetFixedRotation(true);

	_anim = addComponent<AnimatedSpriteComponent>();
	
}


BotonLanzaMisiles::~BotonLanzaMisiles()
{
}

void BotonLanzaMisiles::beginCollision(GameComponent * other, b2Contact * contact)
{
	string otherTag = other->getTag();

	if (otherTag == "Player" )
	{
		if(_boss->isbeetweenFases())
		_ableToFire = true;
	}
}

void BotonLanzaMisiles::endCollision(GameComponent * other, b2Contact * contact)
{
	string otherTag = other->getTag();

	if (otherTag == "Player")
	{
		_ableToFire = false;
	}
}

void BotonLanzaMisiles::update(double time)
{
	GameComponent::update(time);
	if (_ableToFire && ready)
	{
		const Uint8* keyboard = SDL_GetKeyboardState(NULL);
		if (keyboard[SDL_SCANCODE_E])
		{
			ready = false;
			shoot();
		}
	}
}

void BotonLanzaMisiles::shoot()
{
	MisilBoss1 * misil = new MisilBoss1(_boss, _game, _play, _game->getTexture("PistolBullet"), _transform->getPosition(), "Misil");
	_play->addObject(misil);
}
