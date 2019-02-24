#include "Component.h"

class GameComponent;
class Camera;

class RenderComponent : public virtual Component 
{
	public:
		RenderComponent(GameComponent* obj);
		virtual ~RenderComponent();
		virtual void render(Camera* c) const = 0;
};