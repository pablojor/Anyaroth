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
	int _currentLevel = 1;

public:
	~GameManager() {};

	static void init();
	static GameManager* getInstance();

	int getCurrentLevel() const { return _currentLevel; }
	void setCurrentLevel(const int& a) { _currentLevel = a; }
};

