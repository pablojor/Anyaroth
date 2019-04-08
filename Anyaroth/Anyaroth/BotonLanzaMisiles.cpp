#include "BotonLanzaMisiles.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Game.h"

BotonLanzaMisiles::BotonLanzaMisiles(Game* g, Boss1* boss, Texture* texture, Vector2D pos) : _boss(boss), Interactable(g, pos)
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
	_anim->addAnim(AnimatedSpriteComponent::Deactivated, 1, false);
	_anim->addAnim(AnimatedSpriteComponent::Activating, 12, false);
	_anim->addAnim(AnimatedSpriteComponent::Active, 4, true);
	_anim->addAnim(AnimatedSpriteComponent::Used, 11, false);

	_anim->playAnim(AnimatedSpriteComponent::Deactivated);

	_interactIndicator->getComponent<TransformComponent>()->setPosition(pos.getX() + (texture->getW() / texture->getNumCols()) / 2 - (_indicatorTexture->getW() / _indicatorTexture->getNumCols()) / 2 /*50*/, pos.getY() - 30 /*180*/);
}

BotonLanzaMisiles::~BotonLanzaMisiles()
{
}

void BotonLanzaMisiles::update(const double & deltaTime)
{
	Interactable::update(deltaTime);

	if (_canInteract)
	{
		if (usable && ready)
		{
			if (!_interactIndicator->isActive())
				_interactIndicator->setActive(true);
		}
		else
			_interactIndicator->setActive(false);
	}
	else if (usable)
	{
		ready = _boss->isbeetweenFases();
		if (ready)
		{
			if(_anim->getCurrentAnim() != AnimatedSpriteComponent::Activating 
				&& _anim->getCurrentAnim() != AnimatedSpriteComponent::Active)
			_anim->playAnim(AnimatedSpriteComponent::Activating);
			else if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::Activating)
				_anim->playAnim(AnimatedSpriteComponent::Active);
		}
	}
}

void BotonLanzaMisiles::interact()
{
	if (usable &&ready)
	{
		_anim->playAnim(AnimatedSpriteComponent::Used);
		MisilBoss1 * misil = new MisilBoss1(_boss, _game, _play, _game->getTexture("SpentaMisil"), _transform->getPosition(), "Misil");
		addChild(misil);
		ready = false;
		usable = false;
	}
}