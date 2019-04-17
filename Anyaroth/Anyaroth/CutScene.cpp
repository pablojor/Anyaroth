#include "CutScene.h"
#include "checkML.h"


CutScene::CutScene(Player* player) : _player(player)
{
}

CutScene::~CutScene()
{
	while (!_events.empty())
	{
		delete _events.front();
		_events.pop();
	}
}

void CutScene::update(const double& deltaTime)
{
	if (_isPlaying && !_events.empty())
	{
		if (!_events.front()->isFinished())
			_events.front()->update(deltaTime);
		else
		{
			delete _events.front();
			_events.pop();

			if (!_events.empty())
				_events.front()->play();
			else
			{
				_isPlaying = false;
				_player->setInputFreezed(false);
			}
		}
	}
}

void CutScene::play()
{
	if (!_events.empty())
	{
		_player->setInputFreezed(true);
		_isPlaying = true;
		_events.front()->play();
	}

}

void CutScene::addMoveEvent()
{

}

void CutScene::addDialogueEvent(DialoguePanel* dialoguePanel, Dialogue dialogue)
{
	_events.push(new DialogueEvent(dialoguePanel, dialogue));
}

void CutScene::addCameraEvent()
{
}
