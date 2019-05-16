#pragma once
#include <queue>
#include "Event.h"
#include "Game.h"
#include "Player.h"

#include "DialogueEvent.h"
#include "PopUpEvent.h"
#include "ShopEvent.h"
#include "MoveEvent.h"
#include "WaitingEvent.h"
#include "ZoomInOutEvent.h"
#include "FadeInOutEvent.h"
#include "ShakeEvent.h"
#include "FlipEvent.h"
#include "ChangeLevelEvent.h"
#include "BlackScreenEvent.h"
#include "FitCameraEvent.h"
#include "PlaySoundEvent.h"
#include "PlayMusicEvent.h"

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

	virtual void update(double deltaTime);

	void play();

	void addMoveEvent(BodyComponent* body, int dir, int speed, int xDestination);
	void addWaitEvent(int time);

	void addDialogueEvent(DialoguePanel* dialoguePanel, Dialogue dialogue);
	void addPopUpEvent(PopUpPanel* popUpPanel);
	void addShopEvent(ShopMenu* shop);

	void addCameraEvent(Camera* cam, int time, CamEffect type);
	void addCameraShakeEvent(Camera* cam, int time, int intensity);
	void addCameraBlackScreenEvent(Camera* cam);
	void addFitCameraEvent(Camera* cam, double x, double y);

	void addFlipEvent();
	void addChangeLevelEvent();

	void addPlaySoundEvent(Game* game, string sound);
	void addPlayMusicEvent(Game* game, string music);

	inline bool isPlaying() { return _isPlaying; }
};