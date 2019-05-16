#pragma once
#include "Interactable.h"
#include "DialoguePanel.h"

class NPC : public Interactable
{
private:
	Dialogue _dialogue = {};
	DialoguePanel* _dialoguePanel = nullptr;

public:
	NPC(Game* g, Texture* texture, Vector2D pos, Dialogue dialogue);
	virtual ~NPC();

	virtual void update(double time);
	virtual bool interact();

	void setDialoguePanel(DialoguePanel* dialoguePanel);
};