#include "NPC.h"



NPC::NPC(Game* g) : Interactable(g, 50, 50)
{

}


NPC::~NPC()
{
}


void NPC::interact()
{
	_dialoguePanel->startDialogue(_dialogue);
}
