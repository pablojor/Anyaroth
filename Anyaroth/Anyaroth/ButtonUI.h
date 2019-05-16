#pragma once
#include "FramedImageUI.h"
#include <functional>
#include <vector>


class ButtonUI : public FramedImageUI
{
	protected:
		typedef std::function<void(Game*)> Callback;
		struct Frames { uint onOut = 0; uint onOver = 0; uint onDown = 0; uint onUp = 0; uint onInactive = 0; };

		enum ButtonState { None, Over, Out, Down, Up };
		ButtonState _positionState = Out;	//Over o Out
		ButtonState _pressState = None;		//Up o Down

		Callback _onOutCallback = nullptr;
		Callback _onOverCallback = nullptr;
		Callback _onDownCallback = nullptr;
		Callback _onUpCallback = nullptr;

		uint _onOutFrame = 0;
		uint _onOverFrame = 0;
		uint _onDownFrame = 0;
		uint _onUpFrame = 0;
		uint _onInactiveFrame = 0;

		bool _inputEnable = true,
			 _selected = false;

		bool mouseIsOver();

		//0 left 1 up 2 right 3 down
		vector<ButtonUI*> _nextButtons = { nullptr, nullptr, nullptr, nullptr };

	public:
		ButtonUI(Game* game, Texture* image, const Callback& callback = NULL, Frames frames = { 0, 0, 0, 0 }, int arrayPos = 0);
		virtual ~ButtonUI() {};

		virtual void update(double deltaTime);
		virtual bool handleEvent(const SDL_Event& event);

		inline void onUp(const Callback& callback) { _onUpCallback = callback; }
		inline void onDown(const Callback& callback) { _onDownCallback = callback; }
		inline void onOver(const Callback& callback) { _onOverCallback = callback; }
		inline void onOut(const Callback& callback) { _onOutCallback = callback; }

		inline void callUp() { _onUpCallback(_game); }
		inline void callDown() { _onDownCallback(_game); }
		inline void callOver() { _onOverCallback(_game); }
		inline void callOut() { _onOutCallback(_game); }

		void setFrames(Frames frames);
		virtual void setVisible(bool a);

		virtual void setSelected(bool selected);
		inline bool isSelected() { return _selected; }

		void setNextButtons(vector<ButtonUI*> nextButtons) { _nextButtons = nextButtons; }
		inline  vector<ButtonUI*> const getNextButtons() { return _nextButtons; }
		inline ButtonUI* const getNextLeft() { return _nextButtons[0]; }
		inline ButtonUI* const getNextUp() { return _nextButtons[1]; }
		inline ButtonUI* const getNextRight() { return _nextButtons[2]; }
		inline ButtonUI* const getNextDown() { return _nextButtons[3]; }

		void setInputEnable(bool b);
};