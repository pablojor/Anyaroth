#pragma once
#include "PanelUI.h"
#include "AnimatedImageUI.h"

class DashViewer : public AnimatedImageUI
{
	public:
		DashViewer(Game* game, int xPos, int yPos);
		~DashViewer() {}

		void createAnims(const uint& lapse);

		inline void reset() { playAnim(DashAnimations::Icon); }

		inline void startAnimCD() { reset();  playAnim(DashAnimations::Cooldown); }

		virtual void update(double deltaTime);
};