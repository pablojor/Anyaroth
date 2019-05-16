#pragma once
#include "ImageUI.h"


class Cursor : public ImageUI
{

public:
	Cursor(Game* game);
	~Cursor() {}

	void update(double deltaTime);
};