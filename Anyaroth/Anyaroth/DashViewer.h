#pragma once
#include "ImageUI.h"

class DashViewer : public ImageUI
{
	private:
		uint _dashNumber = 0;

	public:
		DashViewer(Game* game, int xPos, int yPos);
		~DashViewer() {}

		void render() const;

		inline void setDashes(const uint& n) { _dashNumber = n; }
		inline uint getDashesNumber() const { return _dashNumber; }
};