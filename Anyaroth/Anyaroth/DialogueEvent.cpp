#include "DialogueEvent.h"


DialogueEvent::DialogueEvent(DialoguePanel* dialoguePanel, Dialogue dialogue) : _dialoguePanel(dialoguePanel), _dialogue(dialogue)
{
}


void DialogueEvent::update(const double& time)
{
	if (_dialoguePanel->conversationRealEnd())
	{
		_finished = true;
	}
}

void DialogueEvent::play()
{
	_dialoguePanel->startDialogue(_dialogue);
}

void DialogueEvent::setDialoguePanel(DialoguePanel* dialoguePanel)
{
	_dialoguePanel = dialoguePanel;
}