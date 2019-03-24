#pragma once
#include "PanelUI.h"
#include "AnimatedImageUI.h"

class DashViewer : public AnimatedImageUI
{
	public:
		DashViewer(Game* game, int xPos, int yPos);
		~DashViewer() {}

		void createAnims(const uint& lapse);

		void startAnimCD();

		virtual void render() const { AnimatedImageUI::render(); }
		virtual void update(double time);
};