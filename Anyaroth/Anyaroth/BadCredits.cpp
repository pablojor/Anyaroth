#include "BadCredits.h"
#include "CreditsState.h"


BadCredits::BadCredits(Game* game, Vector2D posIni) : Interactable(game, posIni)
{
	Texture* _texture = game->getTexture("Mk");
	addComponent<Texture>(_texture);
	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_kinematicBody);
	_body->filterCollisions(OBJECTS, PLAYER);
	_body->getBody()->GetFixtureList()->SetSensor(true);

	Texture* _indicatorTexture = _interactIndicator->getComponent<Texture>();
	_interactIndicator->getComponent<TransformComponent>()->setPosition(posIni.getX() + (_texture->getW() / _texture->getNumCols()) / 2 - (_indicatorTexture->getW() / _indicatorTexture->getNumCols()) / 2, posIni.getY() - 30);
}


BadCredits::~BadCredits()
{
}

bool BadCredits::interact()
{
	Game* g = _game;
	g->popState();
	g->changeState(new CreditsState(g, false));
	return true;
}
