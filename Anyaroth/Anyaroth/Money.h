#pragma once

class Money
{
private:
	int _bank = 0, _wallet = 0;

public:
	inline void restartWallet() { _wallet = 0; }
	inline void storeWallet() { _bank += _wallet; restartWallet(); }
	inline void store(int s) { _wallet += s; }
	inline void setBank(int amount) { _bank = amount; }

	bool spend(int n);
	inline int getWallet() const { return _wallet; }
	inline int getBank() const { return _bank; }
};