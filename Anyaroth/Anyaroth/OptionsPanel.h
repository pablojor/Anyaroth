#pragma once
#include "PanelUI.h"
#include "ButtonUI.h"

class OptionsPanel : public PanelUI
{
private:
	ButtonUI *_moreVolume, *_lessVolume;
	ButtonUI *_moreSFXVolume, *_lessSFXVolume;


	ButtonUI* _backButton;

	bool _menu;
	float _volume, _sfxVolume;
public:
	OptionsPanel(Game* g, bool mainMenu);
	~OptionsPanel();

	void moreVolume(Game * g);
	void lessVolume(Game * g);
	void moreSFXVolume(Game * g);
	void lessSFXVolume(Game * g);

	void back(Game * g);
};
