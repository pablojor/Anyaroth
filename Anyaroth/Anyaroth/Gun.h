#pragma once
#include "PoolWrapper.h"
#include "Game.h"
#include "GunType_def.h"
#include "EffectInterface.h"
#include "BulletPool.h"

class Gun
{
private:
	GunType _id;

protected:
	Game* _game = nullptr;

	int _maxMagazine = 0, _magazine = 0, _maxClip = 0, _clip = 0;
	double _damage = 0, _range = 0, _speed = 0;
	double _maxCadence = 0, _cadence = 0;	//Tiempo entre bala y bala (se actualizara con el deltaTime)
	bool _isAutomatic = false, createParticles = true;

	EffectInterface* _effect;
	BulletAnimType _bulletAnimType;
	ArmAnimType _animType;

	Vector2D _offset = { 0, 0 };
	Texture* _armTexture = nullptr, *_bulletTexture = nullptr, *_iconTexture = nullptr;
	string _shotSoundTag = "";

public:
	Gun(Game* game, Texture* armTexture, Texture* bulletTexture, string shotSoundTag, double speed, double damage, double range, int maxClip, int maxMagazine, int maxCadence, EffectInterface* effect, GunType id, Texture* iconTexture, bool automatic = false, BulletAnimType bType = BulletAnimType::Default);
	virtual ~Gun() {}

	virtual void shoot(BulletPool* bulletPool, const Vector2D& position, double angle, const string& tag);
	virtual void enemyShoot(BulletPool* bulletPool, const Vector2D& position, double angle, const string& tag);

	virtual void reload();

	inline bool canShoot() const { return _clip > 0 && _cadence <= 0; }
	inline bool hasBullets() const { return _clip == 0 && _magazine == 0; }
	inline bool canReload() const { return _magazine > 0 && _clip < _maxClip; }

	void addAmmo(int ammoAdded);
	void resetAmmo();
	void clearAmmo();

	inline int getMagazine() const { return _magazine; }
	inline int getClip() const { return _clip; }
	inline int getMaxClip() const { return _maxClip; }

	inline const GunType& getGunID() const { return _id; }
	inline const ArmAnimType& getAnimType() const { return _animType; }
	inline BulletAnimType getBulletAnimType() const { return _bulletAnimType; }

	inline bool hasToBeReloaded() const { return _clip == 0 && _magazine > 0; }
	inline bool isAutomatic() const { return _isAutomatic; }

	Vector2D prepareBulletPosition(const Vector2D& position, double angle);

	inline void refreshGunCadence(const Uint32& deltaTime) { _cadence > 0 ? _cadence -= deltaTime : _cadence = 0; }

	inline Texture* getBulletTexture() const { return _bulletTexture; }
	inline Texture* getArmTexture() const { return _armTexture; }
	inline Texture* getIconTexture() const { return _iconTexture; }

	//setters
	void setEffect(EffectInterface* effect) { _effect = effect; }
	inline void setMaxCadence(double value) { _maxCadence = value; _cadence = 0; }
	inline void setBulletSpeed(double value) { _speed = value; }
	inline void setDamage(double value) { _damage = value; }
	inline void setBulletTexture(Texture* texture) { _bulletTexture = texture; }
	inline void setBulletAnimType(BulletAnimType bType) { _bulletAnimType = bType; }
	inline void setShotSound(string soundTag) { _shotSoundTag = soundTag; }
	inline void setArmTexture(Texture* t) { _armTexture = t; }
};