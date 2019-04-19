#include "PauseStateHUD.h"


PauseStateHUD::PauseStateHUD(Game* g)
{
	_pausePanel = new PausePanel(g);
	_optionsPanel = new OptionsPanel(g, false);

	addUIElement(_pausePanel);
	addUIElement(_optionsPanel);
}
