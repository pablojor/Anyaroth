#pragma once

#include "Interactable.h"
#include "DialoguePanel.h"

class NPC : public Interactable
{
private:
	Dialogue _dialogue = {};

	DialoguePanel* _dialoguePanel = nullptr;

public:
	NPC(Game* g, Vector2D posIni, Dialogue dialogue);
	virtual ~NPC();

	virtual void update(const double& time);

	virtual void interact();

	void setDialoguePanel(DialoguePanel* dialoguePanel);
};

