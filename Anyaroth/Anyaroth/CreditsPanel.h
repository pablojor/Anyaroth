#pragma once
#include "PanelUI.h"
#include "TextUI.h"
#include "ButtonUI.h"
#include "ImageUI.h"


class CreditsPanel : public PanelUI
{
private:
	enum State {First, Second, Third, Last, ChangeToMenu};

	ImageUI* _anyarothLogo = nullptr;
	ImageUI* _creditsImage = nullptr;
	ImageUI* _yggdraseedLogo = nullptr;

	State _state = First;
	int _timeBetweenStates = 7500;

	void goToMenu();
	void nextState();
	void checkState();
public:
	CreditsPanel(Game* g, bool goodFinal);
	virtual ~CreditsPanel();

	virtual void update(double deltaTime);
	virtual bool handleEvent(const SDL_Event& event);
};

