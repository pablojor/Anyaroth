
#include "Boss.h"
class Boss3 : public Boss
{
public:
	Boss3(Game* g, Player* player, Vector2D pos, BulletPool* pool);
	virtual ~Boss3();

	//virtual void movement(const double& deltaTime);
	//virtual void beginCollision(GameObject* other, b2Contact* contact);
	//virtual void endCollision(GameObject * other, b2Contact* contact);

	//virtual void fase1(const double& deltaTime);
	//virtual void fase2(const double& deltaTime);
	//virtual void fase3(const double& deltaTime);
	//virtual void beetwenFases(const double& deltaTime);
	//virtual void manageLife(Life& l, int damage);
};
