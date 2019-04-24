#include "Interactable.h"
#include "BodyComponent.h"
#include "Game.h"

Interactable::Interactable(Game* g, Vector2D posIni) : GameObject(g, "Interactable")
{

	//addComponent<Texture>(g->getTexture("Mk"));

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(posIni.getX(), posIni.getY());

	_interactIndicator = new GameObject(g);
	_interactIndicator->addComponent<Texture>(g->getTexture("InteractIndicator"));

	_interactIndicator->addComponent<TransformComponent>();

	_interactIndicator->addComponent<AnimatedSpriteComponent>();
	_interactIndicator->getComponent<AnimatedSpriteComponent>()->addAnim(AnimatedSpriteComponent::Idle, 5, true);

	_interactIndicator->getComponent<AnimatedSpriteComponent>()->playAnim(AnimatedSpriteComponent::Idle);

	_interactIndicator->setActive(false);
	addChild(_interactIndicator);

	auto _indicatorTexture = _interactIndicator->getComponent<Texture>();
}


Interactable::~Interactable()
{
}

void Interactable::update(const double& time)
{
	GameObject::update(time);
}

bool Interactable::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && !event.key.repeat) // Captura solo el primer frame que se pulsa
	{
		if (event.key.keysym.sym == SDLK_e && _canInteract) { //TECLA PARA PASAR DE TEXTO EN EL DIALOGO
			interact();//realiza accion
		}
	}
	else if (event.type == SDL_CONTROLLERBUTTONDOWN)
	{
		if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B && _canInteract)
		{
			interact();//realiza accion
		}
	}

	return false;
}

void Interactable::beginCollision(GameObject * other, b2Contact* contact)
{
	//Deteccion de player
	if (other->getTag() == "Player")
	{
		_canInteract = true;
		_interactIndicator->setActive(true);
		_other = dynamic_cast<Player*>(other);
	}
}

void Interactable::endCollision(GameObject * other, b2Contact* contact)
{
	//Deteccion de player
	if (other->getTag() == "Player")
	{
		_canInteract = false;
		_interactIndicator->setActive(false);
		_other = nullptr;
	}
}