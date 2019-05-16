#include "NPC.h"
#include "Game.h"

NPC::NPC(Game* g, Texture* texture, Vector2D pos, Dialogue dialogue) : Interactable(g, pos)
{
	_dialogue = dialogue;

	addComponent<Texture>(texture);

	auto _texture = getComponent<Texture>();
	auto _indicatorTexture = _interactIndicator->getComponent<Texture>();

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_kinematicBody);
	_body->setW(40);
	_body->setH(20);
	_body->getBody()->GetFixtureList()->SetSensor(true);
	_body->filterCollisions(OBJECTS, PLAYER);

	_anim = addComponent<AnimatedSpriteComponent>();
	_anim->addAnim(AnimatedSpriteComponent::Main, _anim->getTexture()->getNumCols(), true);

	_anim->playAnim(AnimatedSpriteComponent::Main);

	_interactIndicator->getComponent<TransformComponent>()->setPosition(pos.getX() + (_texture->getW() / _texture->getNumCols()) / 2 - (_indicatorTexture->getW() / _indicatorTexture->getNumCols()) / 2, pos.getY() - 30);
}

NPC::~NPC()
{
}

void NPC::update(double time)
{
	Interactable::update(time);

	if (_canInteract)
	{
		if (_dialoguePanel->isOpened())
		{
			_interactIndicator->setActive(false);
			if (_other != nullptr)
			{
				_other->setInputFreezed(true);

				if (_other->getComponent<TransformComponent>()->getPosition().getX() > _transform->getPosition().getX())
				{
					_anim->flip();
					_other->getComponent<CustomAnimatedSpriteComponent>()->flip();
				}
				else
				{
					_anim->unFlip();
					_other->getComponent<CustomAnimatedSpriteComponent>()->unFlip();
				}
			}
		}
		else
		{
			_interactIndicator->setActive(true);
			if (_other != nullptr)
				_other->setInputFreezed(false);
		}
	}
}

bool NPC::interact()
{
	if(!_dialoguePanel->isOpened())
	{
		_dialoguePanel->startDialogue(_dialogue);
		_other->setInputFreezed(true);
	}
	return false;
}

void NPC::setDialoguePanel(DialoguePanel* dialoguePanel)
{
	_dialoguePanel = dialoguePanel;
}