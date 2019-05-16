#pragma once
#include "Arm.h"

class Player;

class PlayerArm : public Arm
{
private:
	Player* _player = nullptr;
	void handleFlipState(const Vector2D& target);
public:
	PlayerArm(Game* game, Player* player, Vector2D offset = { 0, 0 });

	void update(double deltaTime);

	void shoot();
	void reload();

	inline double getAngle() const { return _transform->getRotation(); }
	inline Vector2D getPosition() const { return _transform->getPosition(); }
	inline bool isReloading() const { return _anim->getCurrentAnim() == AnimatedSpriteComponent::Reload && !_anim->animationFinished(); }
	inline bool reloadFinished() { return (_anim->getCurrentAnim() == AnimatedSpriteComponent::Reload && _anim->animationFinished()); }
};