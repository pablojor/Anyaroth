#pragma once

class Life
{
private:
	int _life, _maxLife;
	bool _dead = false;

public:
	Life() {}
	Life(int maxLife) : _maxLife(maxLife), _life(maxLife) {}
	virtual ~Life() {}

	void setLife(int amount);
	inline void resetLife() { _life = _maxLife; _dead = false; }

	void addLife(int amount);
	void subLife(int amount);

	inline bool dead() const { return _dead; }
	inline int getLife() const { return _life; }
	inline int getMaxLife() const { return _maxLife; }
};