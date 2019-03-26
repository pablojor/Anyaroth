#include "BotonLanzaMisiles.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Game.h"


BotonLanzaMisiles::BotonLanzaMisiles(Boss1* Boss, Game* g, PlayState* play, Texture* texture, Vector2D posIni) : _boss(Boss), _play(play), Interactable(g, posIni)
{
	addComponent<Texture>(texture);


	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_kinematicBody);
	_body->filterCollisions(OBJECTS, PLAYER);
	_body->getBody()->GetFixtureList()->SetSensor(true);
	_body->setW(20);
	_body->getBody()->GetFixtureList()->SetSensor(true);
	_body->getBody()->SetFixedRotation(true);

	_anim = addComponent<AnimatedSpriteComponent>();
	
}

void BotonLanzaMisiles::update(const double & deltaTime)
{
	Interactable::update(deltaTime);
	if(usable && ! ready)
		ready = _boss->isbeetweenFases();
}


BotonLanzaMisiles::~BotonLanzaMisiles()
{
}

void BotonLanzaMisiles::interact()
{
	if (ready)
	{
		MisilBoss1 * misil = new MisilBoss1(_boss, _game, _play, _game->getTexture("PistolBullet"), _transform->getPosition(), "Misil");
		_play->addObject(misil);
		ready = false;
		usable = false;
	}
}
