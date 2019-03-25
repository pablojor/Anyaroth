#include "Interactable.h"
#include "BodyComponent.h"
#include "Game.h"

Interactable::Interactable(Game* g, double w, double h) : GameComponent(g, "Interactable")
{

	auto _body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_staticBody);

	_body->setW(w);
	_body->setH(h);

	_body->filterCollisions(OBJECTS, PLAYER);
	_body->getBody()->SetFixedRotation(true);

	_body->getBody()->GetFixtureList()->SetSensor(true);

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
		_canInteract = true;
}

void Interactable::endCollision(GameComponent * other, b2Contact* contact)
{

	//Deteccion de player
	if (other->getTag() == "Player")
		_canInteract = false;
}