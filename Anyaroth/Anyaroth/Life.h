#pragma once

class Life
{
private:
	int _life, _maxLife;

public:
	Life() {}
	Life(int maxLife) : _maxLife(maxLife), _life(maxLife) {}

	void setLife(int amount);
	inline void setMaxLife(int amount) { _maxLife = amount; }
	inline void resetLife() { _life = _maxLife; }

	void addLife(int amount);
	void subLife(int amount);

	inline int getLife() const { return _life; }
	inline int getMaxLife() const { return _maxLife; }
};