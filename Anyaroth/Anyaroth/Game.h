#pragma once
#include <list>
#include <vector>
#include <map>

#include "Texture.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "Gun.h"

// Resolución interna del juego
const int GAME_RESOLUTION_X = 480;
const int GAME_RESOLUTION_Y = 270;

//Distancia que recorre la camara
const int LEVEL_WIDTH = GAME_RESOLUTION_X * 10;
const int LEVEL_HEIGHT = GAME_RESOLUTION_Y * 3;

const string INFO_PATH = "..\\files\\info\\";
const string FONTS_PATH = "..\\assets\\fonts\\";
const string FILES_PATH = "..\\files\\levels\\";
const string SAVES_PATH = "..\\files\\saves\\";
const string SPRITE_PATH = "..\\assets\\sprites\\";
const string TILEMAP_PATH = "..\\files\\tilemaps\\";

const int FRAME_RATE = 1000 / 60;
const int TILES_SIZE = 16;
const double M_TO_PIXEL = 8;
const double BUTTON_SCALE = 0.25;

enum _Category
{
	FLOOR = 1,
	ENEMIES = 2,
	PLAYER = 4,
	OBJECTS = 8,
	ENEMY_BULLETS = 16,
	PLAYER_BULLETS = 32,
	DEAD_ENEMIES = 64,
	COLLECTED_OBJECTS = 128,
	MELEE = 256,
};

class Game
{
private:
	SDL_Window* _window = nullptr;

	map <string, Texture*> _textures;
	vector<string> _texturesName;
	map <string, Font*> _fonts;
	vector<string> _fontsName;

	GameStateMachine* _stateMachine = new GameStateMachine();

	b2World* _world = nullptr;
	float _timestep = 1 / 60.0;
	bool _exit = false;

public:
	SDL_Renderer* _renderer = nullptr;

	//Metodos
	void createTextures();
	void createFonts();

	inline GameState* getCurrentState() const { return _stateMachine->currentState(); }
	inline void pushState(GameState* state) { _stateMachine->pushState(state); }
	inline void changeState(GameState* state) { _stateMachine->changeState(state); }
	inline void popState() { _stateMachine->popState(); }

	inline Texture* getTexture(string nameText) { return _textures[nameText]; }
	inline Font* getFont(string nameFont) { return _fonts[nameFont]; }

	inline SDL_Renderer* getRenderer() const { return _renderer; }
	inline SDL_Window* getWindow() const { return _window; }

	inline b2World* getWorld() const { return _world; }
	inline void setTimestep(float timestep) { _timestep = timestep; }
	inline void setExit(bool quit) { _exit = quit; }

	void toggleFullscreen();

	Game();
	~Game();
	void run();
	void update(double time);
	void render() const;
	void handleEvents();
};