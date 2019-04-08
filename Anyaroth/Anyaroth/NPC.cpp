#include "NPC.h"
#include "Game.h"


NPC::NPC(Game* g, Vector2D posIni, Dialogue dialogue) : Interactable(g, posIni)
{
	_dialogue = dialogue;

	addComponent<Texture>(g->getTexture("Npc"));

	auto _texture = getComponent<Texture>();
	auto _indicatorTexture = _interactIndicator->getComponent<Texture>();


	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_kinematicBody);
	_body->filterCollisions(OBJECTS, PLAYER);
	_body->setW(40);
	_body->setH(20);
	_body->getBody()->GetFixtureList()->SetSensor(true);



	_anim = addComponent<AnimatedSpriteComponent>();
	_anim->addAnim(AnimatedSpriteComponent::Main, 8, true);

	_anim->playAnim(AnimatedSpriteComponent::Main);

	_interactIndicator->getComponent<TransformComponent>()->setPosition(posIni.getX() + (_texture->getW() / _texture->getNumCols()) / 2 - (_indicatorTexture->getW() / _indicatorTexture->getNumCols()) / 2 /*50*/, posIni.getY() - 30 /*180*/);
}


NPC::~NPC()
{

}


void NPC::update(const double& time)
{
	GameObject::update(time);

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
