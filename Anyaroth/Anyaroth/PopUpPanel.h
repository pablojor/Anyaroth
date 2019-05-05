#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "ButtonUI.h"
#include "TextUI.h"

#include <queue>
#include <string>

using namespace std;

class PopUpPanel :	public PanelUI
{
private:
	struct PUMessage
	{
		string _title;
		string _message;
	};

	ImageUI * _frame = nullptr;
	TextUI* _title = nullptr;

	vector<TextUI*> _textBlock;

	ButtonUI* _nextButton = nullptr;
	TextUI* _nextButtonText = nullptr;

	queue<PUMessage> _messages;

	bool _isFinished = false;

	void showMessage(PUMessage s);
	void chopText(string s, vector<string>& segments);

	void nextMessage(Game* game);
	void omitAllMessages(Game* game);

	void reorder();
	void reset();

public:
	PopUpPanel(Game* game);
	~PopUpPanel() {}

	void open();
	void close();

	inline void addMessage(PUMessage s) { _messages.push(s); }
	inline bool isFinished() const { return _isFinished; }
};