#include "CreditsPanel.h"
#include "Game.h"
#include "ImageUI.h"


CreditsPanel::CreditsPanel(Game* g, bool goodFinal) : PanelUI(g)
{
	ImageUI* bg = new ImageUI(g, g->getTexture("DemoCredits"));
	bg->setPosition(0, 0);

	string text = (goodFinal ? "Rebellion status report: " : "Rebellion status report: ");
	string text_2 = (goodFinal ? "After the victory of Avestas over the Queen, some of our comrades have" : "Fellow rebels, we have bad news for the rebellion. Avestas has been confirmed to");
	string text_3 = (goodFinal ? "shown their true intentions, which are far from being approved by the newly" : "be a traitor. He killed the Queen, but he is now sitting on her throne, controlling");
	string text_4 = (goodFinal ? "formed Rebellion Council. Those who question the decisions made by the" : "every anya that wears an unhacked helmet. He is perpetuating the tyranny of the");
	string text_5 = (goodFinal ? "Rebellion Council will be treated as traitors and prosecuted for their crimes." : "Queen, we must not accept him as a ruler. The rebellion must fight until the Core's");
	string text_6 = (goodFinal ? " " : "throne is destroyed. For freedom, for Anyaroth!");

	TextUI* _text = new TextUI(g, text, g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_text->setScale(0.6);
	_text->setPosition(CAMERA_RESOLUTION_X / 2 - bg->getW() / 4 - 15, CAMERA_RESOLUTION_Y / 2 - _text->getH() / 2 - 20 - 35);
	TextUI* text2 = new TextUI(g, text_2, g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	text2->setScale(0.6);
	text2->setPosition(CAMERA_RESOLUTION_X / 2 - bg->getW() / 4 - 15, CAMERA_RESOLUTION_Y / 2 - _text->getH() / 2 - 5 - 35);
	TextUI* text3 = new TextUI(g, text_3, g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	text3->setScale(0.6);
	text3->setPosition(CAMERA_RESOLUTION_X / 2 - bg->getW() / 4 - 15, CAMERA_RESOLUTION_Y / 2 - _text->getH() / 2 + 5 - 35);
	TextUI* text4 = new TextUI(g, text_4, g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	text4->setScale(0.6);
	text4->setPosition(CAMERA_RESOLUTION_X / 2 - bg->getW() / 4 - 15, CAMERA_RESOLUTION_Y / 2 - _text->getH() / 2 + 15 - 35);
	TextUI* text5 = new TextUI(g, text_5, g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	text5->setScale(0.6);
	text5->setPosition(CAMERA_RESOLUTION_X / 2 - bg->getW() / 4 - 15, CAMERA_RESOLUTION_Y / 2 - _text->getH() / 2 + 25 - 35);
	TextUI* text6 = new TextUI(g, text_6, g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	text6->setScale(0.6);
	text6->setPosition(CAMERA_RESOLUTION_X / 2 - bg->getW() / 4 - 15, CAMERA_RESOLUTION_Y / 2 - _text->getH() / 2 + 35 - 35);

	/*ImageUI* twitter = new ImageUI(g, g->getTexture("DemoTwitter"));
	twitter->setPosition(_text->getX() + 190, _text->getY() + 66);
	twitter->setSize(74, 13);*/

	_anyarothLogo = new ImageUI(g, g->getTexture("AnyarothLogo"));
	_anyarothLogo->setScale(0.15);
	_anyarothLogo->setPosition(CAMERA_RESOLUTION_X / 2 - _anyarothLogo->getW() / 2, CAMERA_RESOLUTION_Y / 2 - _anyarothLogo->getH() / 2);
	_anyarothLogo->setVisible(false);

	_creditsImage = new ImageUI(g, g->getTexture("Credits"));
	_creditsImage->setSize(CAMERA_RESOLUTION_X, CAMERA_RESOLUTION_Y);
	_creditsImage->setPosition(CAMERA_RESOLUTION_X / 2 - _creditsImage->getW() / 2, CAMERA_RESOLUTION_Y / 2 - _creditsImage->getH() / 2);
	_creditsImage->setVisible(false);

	_yggdraseedLogo = new ImageUI(g, g->getTexture("YggdraSeedLogo"));
	_yggdraseedLogo->setScale(0.25);
	_yggdraseedLogo->setPosition(CAMERA_RESOLUTION_X / 2 - _yggdraseedLogo->getW() / 2, CAMERA_RESOLUTION_Y / 2 - _yggdraseedLogo->getH() / 2);
	_yggdraseedLogo->setVisible(false);

	TextUI* pressAnyKey = new TextUI(g, "- Press any key to continue -", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	pressAnyKey->setPosition(CAMERA_RESOLUTION_X / 2 - pressAnyKey->getW() / 2, CAMERA_RESOLUTION_Y -  4 * pressAnyKey->getH());

	addChild(bg);
	//addChild(_buttonText);
	//addChild(twitter);
	addChild(_text);
	addChild(text2);
	addChild(text3);
	addChild(text4);
	addChild(text5);
	addChild(text6);
	addChild(_anyarothLogo);
	addChild(_creditsImage);
	addChild(_yggdraseedLogo);
	addChild(pressAnyKey);
}


CreditsPanel::~CreditsPanel()
{
}

void CreditsPanel::update(double deltaTime)
{
	PanelUI::update(deltaTime);

	if(_state != First)
		_timeBetweenStates -= deltaTime;
	if (_timeBetweenStates <= 0)
	{
		nextState();
		_timeBetweenStates = 7500;
	}
}

bool CreditsPanel::handleEvent(const SDL_Event& event)
{
	bool handled = false;
	if (_visible && _inputEnabled)
	{
		handled = PanelUI::handleEvent(event);

		if (!handled)
		{
			if ((event.type == SDL_KEYDOWN) || (event.type == SDL_CONTROLLERBUTTONDOWN))
			{
				nextState();
				handled = true;
			}
		}
	}
	return handled;
}

void CreditsPanel::goToMenu()
{
	Game* g = _game;
	g->popState();
	g->changeState(new MenuState(g));
}

void CreditsPanel::nextState()
{
	_inputEnabled = false;
	_game->getCurrentState()->getMainCamera()->fadeOut(1000);
	_game->getCurrentState()->getMainCamera()->onFadeComplete([this](Game* game)
	{
		_state = (State)(_state + 1);
		_game->getCurrentState()->getMainCamera()->fadeIn(1000);
		if (_state != ChangeToMenu)
		{
			_game->getCurrentState()->getMainCamera()->onFadeComplete([this](Game* game) 
			{
				_inputEnabled = true;		
			});
		}
		checkState();
		_timeBetweenStates = 7500;
	}
	);
}

void CreditsPanel::checkState()
{
	//Desactivamos todos los hijos y activamos solo los que deben de mostrarse
	for (auto c : _children)
		c->setVisible(false);

	switch (_state) {
	case Second:
		_anyarothLogo->setVisible(true);
		break;
	case Third:
		_creditsImage->setVisible(true);
		break;
	case Last:
		_yggdraseedLogo->setVisible(true);
		break;
	case ChangeToMenu:
		goToMenu();
		break;
	}
}
