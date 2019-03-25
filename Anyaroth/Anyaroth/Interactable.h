#pragma once

#include "GameComponent.h"

class Interactable : public GameComponent
{
protected:
	bool _canInteract = false;


public:
	Interactable(Game* g, double w, double h);
	virtual ~Interactable();

	virtual bool handleInput(const SDL_Event& event);

	virtual void interact() {};

	void beginCollision(GameComponent * other, b2Contact* contact);
	void endCollision(GameComponent * other, b2Contact* contact);
};

