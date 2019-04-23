#pragma once
#include "Canvas.h"
#include "PausePanel.h"
#include "OptionsPanel.h"

class Game;

class PauseStateHUD : public Canvas
{
private:
	PausePanel* _pausePanel = nullptr;
	OptionsPanel* _optionsPanel = nullptr;

public:
	PauseStateHUD() {};
	PauseStateHUD(Game* g);
	virtual ~PauseStateHUD() {};

	inline PausePanel* getPausePanel() const { return _pausePanel; }
	inline OptionsPanel* getOptionsPanel() const { return _optionsPanel; }
};

