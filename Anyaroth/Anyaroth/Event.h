#pragma once

class Event
{
protected:
	bool _finished = false;

public:
	Event() {}
	virtual ~Event() {}

	virtual void play() = 0;
	virtual void update(double deltaTime) = 0;

	inline bool isFinished() { return _finished; }
};