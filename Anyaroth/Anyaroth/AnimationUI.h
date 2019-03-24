#pragma once
#include "UIElement.h"
#include "Texture.h"

class AnimationUI : public UIElement
{
	private:
		Texture* _image = nullptr;
		SDL_Rect _destRect;

		uint _numFrames = 1;
		uint _initFrameX = 0;
		uint _frameX = 0;
		uint _frameY = 0;

		double _timer;
		double _lapse;
		bool _loop;

	public:
		AnimationUI(Game* game, Texture* image, bool loop, uint numFrames = 1, int xPos = 0, int yPos = 0, int initFrameX = 0, int initFrameY = 0, uint lapse = 60);
		~AnimationUI() {}

		virtual void render() const;
		virtual void update(double time);
		virtual void handleEvent(const SDL_Event& event) {}

		void playAnim();
		inline void setLapse(double l) { _lapse = l; }
};

