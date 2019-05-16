#pragma once

#include "FramedImageUI.h"
#include <vector>

struct AnimationState
{
	uint name;
	uint numFrames;
	bool loop;
	bool animationFinished;
	uint lapse;
};

class AnimatedImageUI : public FramedImageUI
{
	protected:
		vector<AnimationState> _animations = {};

		uint _currentAnim = 0;

		double _timer = 0;
    
		bool _animationFinished = false;
		//bool _active = true;

	public:
		enum DialogueBg { Default, Start, End };
		enum DialogueIndicator { Idle };
		enum DashAnimations { Icon, Cooldown };

		AnimatedImageUI(Game* game, Texture* image, int xPos = 0, int yPos = 0);
		~AnimatedImageUI();

		virtual void render() const;
		virtual void update(double deltaTime);

		void addAnim(uint name, uint numFrames, bool loop = false, uint lapse = 60);
		void playAnim(uint name);

		inline bool animationFinished() { return _animations[_currentAnim].animationFinished; }
		inline uint getCurrentAnim() const { return _currentAnim; }
};


