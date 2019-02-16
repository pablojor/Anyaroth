#include "Storage.h"

bool Storage::store(int s)
{
	if (_total != MAX_TOTAL)
	{
		int newTotal = _total + s;

		if (newTotal < MAX_TOTAL)
			_total = newTotal;
		else
			_total = MAX_TOTAL;

		return true;
	}
	else
		return false;
}

bool Storage::spend(int n)
{
	int newTotal = _total - n;

	if (newTotal < 0)
		return false;
	else
	{
		_total = newTotal;
		return true;
	}
}