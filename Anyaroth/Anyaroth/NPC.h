#pragma once

#include "Interactable.h"
#include "DialoguePanel.h"

class NPC : public Interactable
{
private:
	Dialogue _dialogue = {};

public:
	NPC(Game* g, double w, double h);
	virtual ~NPC();

	virtual void interact();
};

