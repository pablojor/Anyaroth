#pragma once
#include "Event.h"
#include "PopUpPanel.h"

class PopUpEvent : public Event
{
private:
	PopUpPanel* _popUpPanel;

public:
	PopUpEvent(PopUpPanel* popUpPanel) : _popUpPanel(popUpPanel) {}
	virtual ~PopUpEvent() {};

	virtual void update(double time);
	virtual void play();
};