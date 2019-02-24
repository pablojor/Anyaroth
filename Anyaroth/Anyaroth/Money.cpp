#include "Money.h"

bool Money::spend(int n)
{
	int newTotal = _bank - n;

	if (newTotal < 0)
		return false;
	else
	{
		_bank = newTotal;
		return true;
	}
}