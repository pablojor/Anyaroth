#include "DialogueEvent.h"

void DialogueEvent::update(double time)
{
	if (_dialoguePanel->conversationRealEnd())
		_finished = true;
}

void DialogueEvent::play()
{
	_dialoguePanel->startDialogue(_dialogue);
}