#pragma once
#include <list>
#include <vector>
#include <map>

#include "Texture.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "SoundManager.h"

// Resolución interna del juego
const int GAME_RESOLUTION_X = 1920;
const int GAME_RESOLUTION_Y = 1080;

//Distancia que recorre la camara
const int LEVEL_WIDTH = GAME_RESOLUTION_X * 10;
const int LEVEL_HEIGHT = GAME_RESOLUTION_Y * 3;

const string INFO_PATH = "..\\files\\info\\";
const string FONTS_PATH = "..\\assets\\fonts\\";
const string FILES_PATH = "..\\files\\levels\\";
const string SAVES_PATH = "..\\files\\saves\\";
const string SPRITE_PATH = "..\\assets\\sprites\\";
const string TILEMAP_PATH = "..\\files\\tilemaps\\";
const string SOUNDS_PATH = "..\\assets\\sounds\\";

const int FRAME_RATE = 1000 / 60;
const int TILES_SIZE = 16;
const double M_TO_PIXEL = 8;
const double BUTTON_SCALE = 0.25;

enum _Category
{
	FLOOR = 1,
	PLATFORMS = 2,
	ENEMIES = 4,
	OBJECTS = 8,
	PLAYER = 16,
	ENEMY_BULLETS = 32,
	PLAYER_BULLETS = 64,
	DEAD_ENEMIES = 128,
	COLLECTED_OBJECTS = 256,
	MELEE = 512,
	MISIL=1024,
	LASER = 2048
};

class Game
{
private:
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;

	GameStateMachine* _stateMachine = new GameStateMachine();
	SoundManager* _soundManager;

	map <string, Texture*> _textures;
	map <string, Font*> _fonts;
	
	b2World* _world = nullptr;
	float _timestep = 1 / 60.0;
	bool _exit = false;

public:
	//Metodos
	void createTextures();
	void createFonts();
	void createSounds();

	inline GameState* getCurrentState() const { return _stateMachine->currentState(); }
	inline void pushState(GameState* state) { _stateMachine->pushState(state); }
	inline void changeState(GameState* state) { _stateMachine->changeState(state); }
	inline void popState() { _stateMachine->popState(); }

	//Texture* newTexture(string id, string nameText);
	inline Texture* getTexture(string nameText) { return _textures[nameText]; }
	inline Font* getFont(string nameFont) { return _fonts[nameFont]; }

	inline SDL_Renderer* getRenderer() const { return _renderer; }
	inline SDL_Window* getWindow() const { return _window; }

	inline SoundManager* getSoundManager() const { return _soundManager; }

	inline b2World* getWorld() const { return _world; }
	inline void setTimestep(float timestep) { _timestep = timestep; }
	inline void setExit(bool quit) { _exit = quit; }

	void toggleFullscreen();

	Game();
	~Game();
	void run();
	void update(const double& deltaTime);
	void render() const;
	void handleEvents();
};