#include "Interactable.h"
#include "BodyComponent.h"
#include "Game.h"

Interactable::Interactable(Game* g, double xPos, double yPos) : GameComponent(g, "Interactable")
{

	addComponent<Texture>(g->getTexture("Mk"));

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(xPos/*50*/, yPos /*180*/);


	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_staticBody);

	/*_body->setW(w);
	_body->setH(h);*/

	_body->filterCollisions(OBJECTS, PLAYER);
	_body->getBody()->SetFixedRotation(true);

	_body->getBody()->GetFixtureList()->SetSensor(true);


	/*_anim = addComponent<AnimatedSpriteComponent>();
	_anim->addAnim(AnimatedSpriteComponent::IdleNoInteractable, 16, true);
	_anim->addAnim(AnimatedSpriteComponent::IdleInteractable, 10, true);
	_anim->addAnim(AnimatedSpriteComponent::IdleNoInteractable, 16, true);
	_anim->addAnim(AnimatedSpriteComponent::IdleInteractable, 10, true);*/

	_interactIndicator = new GameComponent(g);
	_interactIndicator->addComponent<Texture>(g->getTexture("InteractIndicator"));
	addChild(_interactIndicator);
}


Interactable::~Interactable()
{
}


bool Interactable::handleInput(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && !event.key.repeat) // Captura solo el primer frame que se pulsa
	{
		if (event.key.keysym.sym == SDLK_e && _canInteract) { //TECLA PARA PASAR DE TEXTO EN EL DIALOGO
			interact();//realiza accion
		}
	}

	return false;
}

void Interactable::beginCollision(GameComponent * other, b2Contact* contact)
{
	//Deteccion de player
	if (other->getTag() == "Player")
	{
		_canInteract = true;
		_interactIndicator->setActive(true);
	}
}

void Interactable::endCollision(GameComponent * other, b2Contact* contact)
{
	//Deteccion de player
	if (other->getTag() == "Player")
	{
		_canInteract = false;
		_interactIndicator->setActive(false);
	}
}