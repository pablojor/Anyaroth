#pragma once

class Money
{
	private:
		int _bank = 0;
		int _wallet = 0;

	public:
		//Money() {}
		//virtual ~Money() {}

		void restartWallet() { _wallet = 0; }
		void storeWallet() { _bank += _wallet; }
		void store(int s) { _wallet += s; }

		bool spend(int n);

		int getWallet() const { return _wallet; }
};