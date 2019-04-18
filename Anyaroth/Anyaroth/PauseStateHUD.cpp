#include "PauseStateHUD.h"


PauseStateHUD::PauseStateHUD(Game* g)
{
	_pausePanel = new PausePanel(g);

	addUIElement(_pausePanel);
}
