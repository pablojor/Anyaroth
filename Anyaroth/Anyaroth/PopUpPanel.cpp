#include "PopUpPanel.h"
#include "Game.h"
#include "Camera.h"

#include <iterator>
#include <sstream>

PopUpPanel::PopUpPanel(Game* game) : PanelUI(game)
{
	_frame = new ImageUI(game, game->getTexture("DepotPanel"));
	_title = new TextUI(game, "Title", game->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255});
	_title->setScale(1.5f);

	_nextButton = new ButtonUI(game, game->getTexture("MenuButtons"), [this](Game* game) { nextMessage(game); }, { 0, 1, 2, 1 });
	_exitButton = new ButtonUI(game, game->getTexture("MenuButtons"), [this](Game* game) { omitAllMessages(game); }, { 0, 1, 2, 1 });

	addChild(_frame);
	addChild(_title);
	addChild(_nextButton);
	addChild(_exitButton);

	_textBlock = std::vector<TextUI*>(6);
	for (int i = 0; i < _textBlock.size(); i++)
	{
		_textBlock[i] = new TextUI(game, "Line", game->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
		addChild(_textBlock[i]);
	}

	reorder();
}


PopUpPanel::~PopUpPanel()
{
	/*delete _frame; _frame = nullptr;
	delete _title; __title = nullptr;
	delete _nextButton; _nextButton = nullptr;
	delete _exitButton; _exitButton = nullptr;

	for (auto t : _textBlock)
	{
		delete t; t = nullptr;
	}*/
}


void PopUpPanel::showMessage(PUMessage s)
{
	//Reseteamos
	reset();
	//Ponemos el titulo
	_title->setText(_messages.front()._title);

	//Ponemos el mensaje
	std::vector<string> segments;
	chopText(_messages.front()._message, segments);
	for (int i = 0; i < segments.size(); i++)
	{
		if (i >= _textBlock.size())
			addChild(new TextUI(_game, segments[i], _game->getFont("ARIAL12"), 12, 0, 0, { 255,255,255,255 }));
		else
			_textBlock[i]->setText(segments[i]);
	}
}

void PopUpPanel::chopText(string s, std::vector<string>& segments)
{
	string temp = s.c_str();
	int width = 0, maxWidth = 120;
	TTF_SizeText(_game->getFont("ARIAL12")->getTTFFont(), s.c_str(), &width, nullptr);

	if (width > maxWidth)
	{
		int i = 0;
		bool finish = false;
		while (i < _textBlock.size() && !finish)
		{
			istringstream iss(temp);
			vector<string> results(istream_iterator<string>{iss},
				istream_iterator<string>());

			string aux = "";
			int j = 0;
			TTF_SizeText(_game->getFont("ARIAL12")->getTTFFont(), aux.c_str(), &width, nullptr);
			while (j < results.size() && width < maxWidth)
			{
				aux += results[j];
				aux += " ";
				TTF_SizeText(_game->getFont("ARIAL12")->getTTFFont(), aux.c_str(), &width, nullptr);
				j++;
			}

			segments[i] = aux;

			if (j < results.size())
			{
				temp = temp.substr(aux.size());
				TTF_SizeText(_game->getFont("ARIAL12")->getTTFFont(), temp.c_str(), &width, nullptr);
			}
			else
				finish = true;
			i++;
		}
	}
	else
		segments[0] = s;
}

void PopUpPanel::nextMessage(Game* game)
{
	if (_messages.size() > 0)
	{
		_messages.pop();
		if (_messages.size() > 0)
		{
			showMessage(_messages.front());
			reorder();
		}
		else
		{
			close();
		}
	}
	else
		close();
}

void PopUpPanel::omitAllMessages(Game * game)
{
	while(_messages.size() != 0)
		_messages.pop();
	close();
}


void PopUpPanel::reorder()
{
	_frame->setPosition(CAMERA_RESOLUTION_X / 2 - _frame->getW() / 2, CAMERA_RESOLUTION_Y / 2 - _frame->getH() / 2);
	_title->setPosition(CAMERA_RESOLUTION_X / 2 - _title->getW() / 2, _frame->getY() + 2);

	for (int i = 0; i < _textBlock.size(); i++)
	{
		if(i - 1 < 0)
			_textBlock[i]->setPosition(_frame->getX() + 2, _title->getY() +  _textBlock[i]->getH() + 5);
		else
			_textBlock[i]->setPosition(_frame->getX() + 2, _textBlock[i - 1]->getY() + _textBlock[i]->getH());
	}

	_nextButton->setPosition(_frame->getX() - 2, _frame->getY() + _frame->getH());
	_exitButton->setPosition(_frame->getX() + _frame->getW() / 2 + 2, _frame->getY() + _frame->getH());
}


void PopUpPanel::reset()
{
	for (auto a : _textBlock)
		a->setText(" ");
	_title->setText(" ");
}


void PopUpPanel::open()
{
	for (auto c : _children)
		c->setVisible(true);
}


void PopUpPanel::close()
{
	for (auto c : _children)
		c->setVisible(false);
}
