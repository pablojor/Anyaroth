#include "Life.h"

void Life::setLife(int amount)
{
	if (amount > 0 && amount <= _maxLife)
		_life = amount;
}

void Life::addLife(int amount)
{
	if (_life + amount < _maxLife)
		_life += amount;
	else
		_life = _maxLife;
}

void Life::subLife(int amount)
{
	if (amount < _life)
		_life -= amount;
	else
		_life = 0;
}