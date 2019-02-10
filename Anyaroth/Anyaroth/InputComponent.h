#include "Component.h"
#include "SDL.h"

class GameComponent;

class InputComponent : public Component 
{
	public:
		InputComponent(GameComponent* obj);
		virtual ~InputComponent();
		virtual void handleInput(const SDL_Event& event) = 0;
};

