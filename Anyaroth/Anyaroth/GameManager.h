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
	bool _onDialogue = false, _onShop = false;

public:
	~GameManager() {}

	static void init();
	static GameManager* getInstance();

	int getCurrentLevel() const { return _currentLevel; }
	void setCurrentLevel(const int& a) { _currentLevel = a; }

	bool getOnDialogue() const { return _onDialogue; }
	void setOnDialogue(const bool& b) { _onDialogue = b; }

	bool getOnShop() const { return _onShop; }
	void setOnShop(const bool& b) { _onShop = b; }
};