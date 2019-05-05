#pragma once
#include "ImageUI.h"

class LifeBar : public ImageUI
{
	private:
		bool inUse = false;
		int _life, _maxLife;
	public:
		LifeBar(Game* game, string textName, int xPos = 0, int yPos = 0);
		~LifeBar() {}

		virtual void updateLifeBar(const int& life, const int& maxLife);
		virtual void render() const;
		virtual void setInUse(bool b);
		inline bool getInUse() const { return inUse; }
};