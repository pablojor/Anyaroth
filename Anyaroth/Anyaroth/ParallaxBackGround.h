#pragma once
#include "Texture.h"
#include "Camera.h"

class ParallaxBackGround
{
	private:
		Texture* _texture = nullptr;

	public:
		ParallaxBackGround(Texture* texture);
		~ParallaxBackGround();

		void update();
		void render(Camera* c);
};

