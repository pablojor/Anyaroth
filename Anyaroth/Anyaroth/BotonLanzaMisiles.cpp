#include "BotonLanzaMisiles.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Game.h"


BotonLanzaMisiles::BotonLanzaMisiles(Boss1* Boss, Game* g, PlayState* play, Texture* texture, Vector2D posIni) : _boss(Boss), _play(play), Interactable(g, posIni)
{
	addComponent<Texture>(texture);

	auto _indicatorTexture = _interactIndicator->getComponent<Texture>();

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_kinematicBody);
	_body->filterCollisions(OBJECTS, PLAYER);
	_body->setW(20);
	_body->getBody()->GetFixtureList()->SetSensor(true);
	_body->getBody()->SetFixedRotation(true);

	_anim = addComponent<AnimatedSpriteComponent>();
	
	_interactIndicator->getComponent<TransformComponent>()->setPosition(posIni.getX() + (texture->getW() / texture->getNumCols()) / 2 - (_indicatorTexture->getW() / _indicatorTexture->getNumCols()) / 2 /*50*/, posIni.getY() - 30 /*180*/);
}

void BotonLanzaMisiles::update(const double & deltaTime)
{
	Interactable::update(deltaTime);

	if (usable )
		ready = _boss->isbeetweenFases();
	if (_canInteract)
	{
		if(usable && ready)
			_interactIndicator->setActive(true);
		else
			_interactIndicator->setActive(false);
	}
}


BotonLanzaMisiles::~BotonLanzaMisiles()
{
}

void BotonLanzaMisiles::interact()
{
	if (usable &&ready)
	{
		MisilBoss1 * misil = new MisilBoss1(_boss, _game, _play, _game->getTexture("PistolBullet"), _transform->getPosition(), "Misil");
		_play->addObject(misil);
		ready = false;
		usable = false;
	}
}
