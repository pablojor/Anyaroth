#pragma once


class Event
{
protected:
	bool _finished = false;

public:
	Event();
	~Event();

	virtual void play() = 0;
	virtual void update(const double& deltaTime) = 0;


	inline bool isFinished() { return _finished; }
};

