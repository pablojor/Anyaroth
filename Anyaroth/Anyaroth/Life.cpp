#include "Life.h"

Life::~Life()
{
}

void Life::setLife(int amount)
{
	if (amount > 0 && amount <= _maxLife)
		_life = amount;
}

void Life::addLife(int amount)
{
	if (_life + amount < _maxLife)
		_life += amount;
}

void Life::subLife(int amount)
{
	if (amount < _life)
		_life -= amount;
	else
	{
		_life = 0;
		_dead = true;
	}
}
