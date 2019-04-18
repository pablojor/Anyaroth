#pragma once

class GameManager
{

private:
	static GameManager _instance;
	static bool _initilized;

	GameManager(GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	GameManager() {};

	//Aqui irán todas la varibles que se necesite en el juego
	int _currentZone = 0;

public:
	~GameManager() {};

	static void init();
	static GameManager* getInstance();

	int getCurrentZone() const { return _currentZone; }
};

