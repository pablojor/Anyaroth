#pragma once
#include "ImageUI.h"

class LifeBar :	public ImageUI
{
private:
	int* _life = nullptr;
	int* _maxLife = nullptr;

	void updateAspect();

public:
	LifeBar(Game* game, Texture* texture);
	~LifeBar() {};

	void render() const;
	void update();

	inline void setLifeAndMaxLife(int* life, int* maxLife) { _life = life; _maxLife = maxLife; }
};

