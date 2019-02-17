#pragma once

class Storage
{
	private:
		int MAX_TOTAL = 10;
		int _total = 0;

	public:
		Storage() {}
		~Storage() {}

		void changeMaxTotal(int max) { MAX_TOTAL = max; }
		bool store(int s);
		bool spend(int n);
};