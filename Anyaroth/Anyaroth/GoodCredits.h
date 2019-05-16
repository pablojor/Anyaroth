#pragma once
#include "Interactable.h"


class GoodCredits : public Interactable
{
public:
	GoodCredits(Game* game, Vector2D posIni);
	~GoodCredits();

	virtual bool interact();
};

