#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "ButtonUI.h"
#include "TextUI.h"

#include <queue>
#include <string>


class PopUpPanel :	public PanelUI
{
private:

	struct PUMessage {
		string _title;
		string _message;
	};

	ImageUI * _frame = nullptr;
	TextUI* _title = nullptr;
	std::vector<TextUI*> _textBlock;
	ButtonUI* _nextButton = nullptr;
	ButtonUI* _exitButton = nullptr;

	queue<PUMessage> _messages;

	void showMessage(PUMessage s);
	void chopText(string s, std::vector<string>& segments);

	void nextMessage(Game* game);
	void omitAllMessages(Game* game);

	void reorder();
	void reset();

public:
	PopUpPanel(Game* game);
	~PopUpPanel();

	void open();
	void close();

	inline void addMessage(PUMessage s) { _messages.push(s); }
};

