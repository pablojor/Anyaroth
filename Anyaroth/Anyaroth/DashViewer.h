#pragma once
#include "PanelUI.h"

class AnimationUI;
class ImageUI;

class DashViewer : public PanelUI
{
	private:
		double _cooldown;
		ImageUI* _icon;
		AnimationUI* _animation;

	public:
		DashViewer(Game* game, int xPos, int yPos);
		~DashViewer() {}

		virtual void update(double time) {}

		inline void setCooldown(double c);
};

//class DashViewer : public ImageUI
//{
//	private:
//		uint _dashNumber = 0;
//
//	public:
//		DashViewer(Game* game, int xPos, int yPos);
//		~DashViewer() {}
//
//		void render() const;
//
//		inline void setDashes(const uint& n) { _dashNumber = n; }
//		inline uint getDashesNumber() const { return _dashNumber; }
//};