#include "Component.h"

class GameComponent;

class PhysicsComponent : public Component {
public:
	PhysicsComponent(GameComponent* obj);
	virtual ~PhysicsComponent();
	virtual void update(GameObject* o, Uint32 time) = 0;
};
