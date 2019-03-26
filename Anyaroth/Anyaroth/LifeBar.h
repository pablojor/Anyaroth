#pragma once
#include "ImageUI.h"

class LifeBar : public ImageUI
{
	private:
		bool inUse = true;

	public:
		LifeBar(Game* game, string textName, int xPos = 0, int yPos = 0);
		~LifeBar() {}

		void updateLifeBar(const int& life, const int& maxLife);

		void setInUse(bool b);
		inline bool getInUse() const { return inUse; }
};