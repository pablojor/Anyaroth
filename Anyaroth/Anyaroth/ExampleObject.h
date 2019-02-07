#pragma once
#include "GameComponent.h"
#include "BoxCollider.h"

class ExampleObject : public GameComponent 
{
	private:
		string _tag;
	public:
		ExampleObject(string tag, Texture* texture);
		~ExampleObject() {}

		void update();
};

