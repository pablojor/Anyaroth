#include "NPC.h"
#include "Game.h"


NPC::NPC(Game* g, double xPos, double yPos, Dialogue dialogue) : Interactable(g, xPos, yPos)
{
	_dialogue = dialogue;

	addComponent<Texture>(g->getTexture("Coin"));

	auto _texture = getComponent<Texture>();
	auto _indicatorTexture = _interactIndicator->getComponent<Texture>();

	/*_body->setW(40);
	_body->setH(20);*/


	_anim = addComponent<AnimatedSpriteComponent>();
	_anim->addAnim(AnimatedSpriteComponent::Main, 6, true);

	_anim->playAnim(AnimatedSpriteComponent::Main);

	_interactIndicator->getComponent<TransformComponent>()->setPosition(xPos + (_texture->getW() / _texture->getNumCols()) / 2 - (_indicatorTexture->getW() / _indicatorTexture->getNumCols()) / 2 /*50*/, yPos - 30 /*180*/);
}


NPC::~NPC()
{

}


void NPC::update(double deltaTime)
{
	GameComponent::update(deltaTime);

	if (_canInteract)
	{
		if (_dialoguePanel->isConversating())
			_interactIndicator->setActive(false);
		else
			_interactIndicator->setActive(true);
	}
}

void NPC::interact()
{
	_dialoguePanel->startDialogue(_dialogue);
}

void NPC::setDialoguePanel(DialoguePanel* dialoguePanel)
{
	_dialoguePanel = dialoguePanel;
}
