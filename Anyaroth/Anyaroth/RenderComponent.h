#include "Component.h"

class GameComponent;

class RenderComponent : public Component {

public:
	RenderComponent(GameComponent* obj);
	virtual ~RenderComponent();
	virtual void render() const = 0;
};