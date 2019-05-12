#pragma once
#include "Interactable.h"


class BadCredits :	public Interactable
{
public:
	BadCredits(Game* game, Vector2D posIni);
	~BadCredits();

	virtual bool interact();
};

