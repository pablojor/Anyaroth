#include "Component.h"

class GameComponent;

class RenderComponent : public Component {

public:
	RenderComponent(GameComponent* obj);
	virtual ~RenderComponent();
	virtual void render(/*GameObject* o, Uint32 time*/) const = 0;
};