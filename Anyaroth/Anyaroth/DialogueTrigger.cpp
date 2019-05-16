#include "DialogueTrigger.h"
#include "Game.h"


DialogueTrigger::DialogueTrigger(Game* game, string data, Player* player, int xPos, int yPos) : Trigger(game, xPos, yPos)
{
	if (data == "Close")
	{
		onTriggerEnter([this, game]() {
			getPlayHUD()->getDialoguePanel()->endDialogue();
			getPlayHUD()->getDialoguePanel()->stopAtLastLineShown(false);
			destroy();
		});
	}
	else
	{
		onTriggerEnter([this, game, data, player]() {
			getPlayHUD()->getDialoguePanel()->endDialogue();
			getPlayHUD()->getDialoguePanel()->stopAtLastLineShown(true);
			getPlayHUD()->getDialoguePanel()->startDialogue(_game->getDialogue(_game->usingJoystick() ? data + "PAD" : data));
			player->setInputFreezed(false);
			destroy();
		});
	}
}


DialogueTrigger::~DialogueTrigger()
{
}


PlayStateHUD* DialogueTrigger::getPlayHUD()
{
	return _game->getCurrentState()->getPlayHUD(); 
}