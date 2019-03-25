#pragma once

#include "Interactable.h"
#include "DialoguePanel.h"

class NPC : public Interactable
{
private:
	Dialogue _dialogue = {};

	DialoguePanel* _dialoguePanel = nullptr;

public:
	NPC(Game* g);
	virtual ~NPC();

	virtual void interact();
};

