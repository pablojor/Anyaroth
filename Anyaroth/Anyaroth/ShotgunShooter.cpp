#include "ShotgunShooter.h"
#include "TransformComponent.h"

void ShotgunShooter::shoot(Vector2D bulletPosition, Vector2D bulletDir, double angle)
{
	Vector2D auxBulletPos = bulletPosition;
	Vector2D auxBulletDir = bulletDir;
	double auxAngle = angle;

	for (int i = 0; i < _bulletAngles.size(); i++)
	{
		bulletPosition = auxBulletPos.rotateAroundPoint(_bulletAngles[i], { auxBulletPos.getX(), auxBulletPos.getY() });

		bulletDir = auxBulletDir.rotate(_bulletAngles[i]);
		bulletDir.normalize();

		angle = auxAngle + _bulletAngles[i];

		_bPool->addBullet(bulletPosition, bulletDir, angle);
	}
}