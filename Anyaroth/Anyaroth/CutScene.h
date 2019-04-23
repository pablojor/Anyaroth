#pragma once

#include <queue>
#include "Event.h"
#include "Player.h"

#include "DialogueEvent.h"
#include "MoveEvent.h"
#include "waitEvent.h"
#include "ZoomInOutEvent.h"
#include "FadeInOutEvent.h"
#include "ShakeEvent.h"
#include "FlipEvent.h"
#include "ShopEvent.h"

using namespace std;

class CutScene
{
private:
	queue<Event*> _events;

	Player* _player;

	bool _isPlaying = false;
public:
	CutScene(Player* player);
	virtual ~CutScene();

	virtual void update(const double& deltaTime);

	void play();

	void addMoveEvent(BodyComponent* body, int dir, int speed, int xDestination);
	void addDialogueEvent(DialoguePanel* dialoguePanel, Dialogue dialogue);
	void addWaitEvent(int time);
	void addCameraEvent(Camera* cam, int time, CamEffect type);
	void addCameraShakeEvent(Camera* cam, int time, int intensity);
	void addFlipEvent();
	void addShopEvent(ShopMenu* shop);


	inline bool isPlaying() { return _isPlaying; }
};

