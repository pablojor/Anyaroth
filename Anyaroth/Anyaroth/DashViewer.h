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

		inline void startAnimCD() { playAnim(DashAnimations::Cooldown); }

		virtual void update(const double& deltaTime);
};