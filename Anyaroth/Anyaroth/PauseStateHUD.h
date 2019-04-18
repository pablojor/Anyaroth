#pragma once
#include "Canvas.h"
#include "PausePanel.h"

class Game;

class PauseStateHUD : public Canvas
{
private:
	PausePanel* _pausePanel = nullptr;

public:
	PauseStateHUD() {};
	PauseStateHUD(Game* g);
	virtual ~PauseStateHUD() {};

	inline PausePanel* getMainMenuPanel() const { return _pausePanel; }
};

