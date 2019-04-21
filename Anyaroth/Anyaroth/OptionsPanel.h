#pragma once
#include "PanelUI.h"
#include "ButtonUI.h"
#include "TextUI.h"

class OptionsPanel : public PanelUI
{
private:
	ButtonUI *_moreVolume, *_lessVolume;
	ButtonUI *_moreSFXVolume, *_lessSFXVolume;
	ButtonUI *_moreBright, *_lessBright;
	ButtonUI* _screenButton;

	TextUI* _volumeSFXText;
	TextUI* _volumeText;
	TextUI* _nameVolumeSFXText;
	TextUI* _nameVolumeText;
	TextUI* _nameBrightText;

	ButtonUI* _backButton;

	bool _menu, _fullScreen;
	int buttonW, buttonH;

public:
	OptionsPanel(Game* g, bool mainMenu);
	~OptionsPanel();

	virtual bool handleEvent(const SDL_Event& event);

	void moreVolume(Game * g);
	void lessVolume(Game * g);
	void moreSFXVolume(Game * g);
	void lessSFXVolume(Game * g);
	void moreBright(Game * g);
	void lessBright(Game * g);
	void fullScreen(Game* g);

	int valueToWrite(float val);

	void back(Game * g);
};
