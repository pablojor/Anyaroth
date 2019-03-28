#pragma once
#include "Canvas.h"
#include "ShopPanel.h"
#include "ButtonUI.h"
#include "DialoguePanel.h"
//#include "DepotPanel.h"

class ShopCanvas :	public Canvas
{
private:
	ButtonUI * _shopButton = nullptr;
	ButtonUI* _talkButton = nullptr;
	ButtonUI* _depotButton = nullptr;
	ButtonUI* _exitButton = nullptr;

	DialoguePanel* _dialoguePanel = nullptr;

	ShopPanel* _shopPanel = nullptr;
	//DepotPanel* _depotPanel = nullptr;

public:
	ShopCanvas(Game* game);
	~ShopCanvas();
};

