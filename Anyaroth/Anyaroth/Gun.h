#pragma once
#include "PoolWrapper.h"
#include "Game.h"
#include "GunType_def.h"
#include "EffectInterface.h"

class Gun
{
protected:
	int _maxMagazine = 0, _magazine = 0, _maxClip = 0, _clip = 0;
	double _maxCadence = 0, _cadence = 0;	//Tiempo entre bala y bala (se actualizara con el deltaTime)
	bool _isAutomatic = false;
	EffectInterface* _effect;
	BulletAnimType _bulletAnimType;

	double _damage = 0, _range = 0, _speed = 0;

	Vector2D _offset = { 0, 0 };

	Texture* _armTexture = nullptr, *_bulletTexture = nullptr, *_iconTexture = nullptr;

public:
	Gun(Texture* armTexture, Texture* bulletTexture, double speed, double damage, double range, int maxClip, int maxMagazine, double maxCadence, EffectInterface* effect, bool automatic = false, BulletAnimType bType = BulletAnimType::Default, Texture* iconTexture = nullptr);
	virtual ~Gun() {}

	virtual void shoot(PoolWrapper* bulletPool, const Vector2D& position, const double& angle, const string& tag);
	virtual void enemyShoot(PoolWrapper* bulletPool, const Vector2D& position, const double& angle, const string& tag);

	virtual void reload();

	inline bool canShoot() const { return _clip > 0 && _cadence <= 0; }
	inline bool canReload() const { return _magazine > 0 && _clip < _maxClip; }

	void addAmmo(int ammoAdded);
	void resetAmmo();

	inline int getMagazine() const { return _magazine; }
	inline int getClip() const { return _clip; }

	inline bool hasToBeReloaded() const { return _clip == 0 && _magazine > 0; }

	Vector2D prepareBulletPosition(const Vector2D& position, const double& angle);

	inline bool isAutomatic() const { return _isAutomatic; }

	inline void refreshGunCadence(const Uint32& deltaTime) { _cadence > 0 ? _cadence -= deltaTime : _cadence = 0; }

	inline void setBulletTexture(Texture* texture) { _bulletTexture = texture; }
	
	inline Texture* getBulletTexture() const { return _bulletTexture; }
	inline Texture* getArmTexture() const { return _armTexture; }
	inline Texture* getIconTexture() const { return _iconTexture; }

	//setters
	void setEffect(EffectInterface* effect) { _effect = effect; }
	inline void setMaxCadence(double value) { _maxCadence = value; _cadence = 0; }
	inline void setBulletSpeed(double value) { _speed = value; }
	inline void setDamage(double value) { _damage = value; }
	inline void setBulletAnimType(BulletAnimType bType) { _bulletAnimType = bType; }
	inline BulletAnimType getBulletAnimType() const { return _bulletAnimType; }

};