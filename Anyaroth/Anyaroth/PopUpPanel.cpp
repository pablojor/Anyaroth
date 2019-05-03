#include "PopUpPanel.h"
#include "Game.h"
#include "Camera.h"

#include <iterator>
#include <sstream>

PopUpPanel::PopUpPanel(Game* game) : PanelUI(game)
{
	_frame = new ImageUI(game, game->getTexture("DepotPanel"));
	_title = new TextUI(game, "Title", game->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255});
	_title->setScale(1.2);

	_nextButton = new ButtonUI(game, game->getTexture("MenuButtons"), [this](Game* game) { nextMessage(game); }, { 0, 1, 2, 1 });
	_nextButtonText = new TextUI(game, "Next", game->getFont("ARIAL12"), 12, 0, 0, { 0, 0, 0, 255 });

	addChild(_frame);
	addChild(_title);
	addChild(_nextButton);
	addChild(_nextButtonText);

	_textBlock = std::vector<TextUI*>(6);
	for (int i = 0; i < _textBlock.size(); i++)
	{
		_textBlock[i] = new TextUI(game, "Line", game->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
		_textBlock[i]->setScale(0.8);
		addChild(_textBlock[i]);
	}

	reorder();

	//Para las pruebas
	addMessage({ "AAAAAAAAA", "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled" });
	addMessage({ "BBBBBBBBB", "bbbbbbbb bbb bbbbbbbbbbb bbbb bbbb bbbbbbbb bbbbbbbbbbbb bbbb bbbb bbbbbbbbbbbbb b bbb bbbbbbbbb bbbbbbb bbbbbbb bbbbbb bbbbbb bb bbbbbb" });
	addMessage({ "CCCCCCCCC", "cccccccc ccc ccccccccccc cccc cccc cccccccc cccccccccccc cccc cccc ccccccccccccc c ccc ccccccccc ccccccc ccccccc cccccc cccccc cc cccccc" });
	addMessage({ "DDDDDDDDD", "dddddddd ddd ddddddddddd dddd dddd dddddddd dddddddddddd dddd dddd ddddddddddddd d ddd ddddddddd ddddddd ddddddd dddddd dddddd dd dddddd" });

	open();
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
	_title->setText(s._title);
	_title->setScale(1.2);

	//Ponemos el mensaje
	std::vector<string> segments;
	chopText(s._message, segments);
	for (int i = 0; i < segments.size(); i++)
	{
		if (i >= _textBlock.size())
		{
			_textBlock.push_back(new TextUI(_game, segments[i], _game->getFont("ARIAL12"), 12, 0, 0, { 255,255,255,255 }));
			addChild(_textBlock[i]);
		}
		else
			_textBlock[i]->setText(segments[i]);

		_textBlock[i]->setScale(0.8);
	}

	if (_messages.size() < 2)
		_nextButtonText->setText("Close");
	else
		_nextButtonText->setText("Next");


	reorder();
}

void PopUpPanel::chopText(string s, std::vector<string>& segments)
{
	string temp = s.c_str();
	int width = 0, maxWidth = 175;
	TTF_SizeText(_game->getFont("ARIAL12")->getTTFFont(), s.c_str(), &width, nullptr);

	if (width > maxWidth)
	{
		int i = 0;
		bool finish = false;
		while ((i < _textBlock.size() && !finish) || !finish)
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

			segments.push_back(aux);

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
		segments.push_back(s);
}

void PopUpPanel::nextMessage(Game* game)
{
	if (_messages.size() > 0)
	{
		_messages.pop();
		if (_messages.size() > 0)
			showMessage(_messages.front());
		else
			close();
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
			_textBlock[i]->setPosition(_frame->getX() + 5, _title->getY() + _title->getH() /*+  _textBlock[i]->getH()*/ + 2);
		else
			_textBlock[i]->setPosition(_frame->getX() + 5, _textBlock[i - 1]->getY() + _textBlock[i]->getH());
	}

	_nextButton->setPosition(CAMERA_RESOLUTION_X / 2 - _nextButton->getW() / 2, _frame->getY() + _frame->getH() - _nextButton->getH() - 5);
	_nextButtonText->setPosition(_nextButton->getX() + _nextButton->getW() / 2 - _nextButtonText->getW() / 2, _nextButton->getY() + _nextButton->getH() / 2 - _nextButtonText->getH() / 2);
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

	if (_messages.size() > 0)
		showMessage(_messages.front());
}


void PopUpPanel::close()
{
	for (auto c : _children)
		c->setVisible(false);
}
