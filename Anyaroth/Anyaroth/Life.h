#pragma once
class Life
{
	private:
		int _life;
		int _maxLife;
		bool _dead = false;
	public:
		Life() {};
		Life(int maxLife) : _maxLife(maxLife), _life(maxLife) {};
		virtual ~Life();
		void setLife(int amount);
		void resetLife() { _life = _maxLife; }
		void addLife(int amount);
		void subLife(int amount);
		bool dead() { return _dead; }
		inline int getLife() const { return _life; };
		inline int getMaxLife() const { return _maxLife; }

};

