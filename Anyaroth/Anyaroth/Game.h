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
#include "ShooterInterface.h"
#include "Shooter.h"
#include "ShotgunShooter.h"
#include "GunType_def.h"

//Resolución interna del juego
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

const int NUM_FONTS = 0;
const int TILES_SIZE = 16;

const double M_TO_PIXEL = 8;
const double BUTTON_SCALE = 0.25;


//Tags
enum _Category 
{
	FLOOR = 1,
	ENEMIES = 2,
	PLAYER = 4,
	OBJECTS = 8,
	PLAYER_BULLETS = 16,
};

class Game
{
private:
	SDL_Window* window = nullptr;
	map <string, Texture*> textures;
	map <string, Font*> _fonts;
	GameStateMachine* stateMachine = new GameStateMachine();
	vector<string> texturesName;
	b2World* _world = nullptr;
	bool exit = false;

public:
	SDL_Renderer* renderer = nullptr;
	vector<int> var;

	//Metodos
	void createTextures();

	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();

	inline GameState* getCurrentState() const { return stateMachine->currentState(); }
	Texture* getTexture(string nameText);
	Font* getFont(string nameFont);

	inline SDL_Renderer* getRenderer() const { return renderer; }
	inline SDL_Window* getWindow() const { return window; }
	inline b2World* getWorld() const { return _world; }
	inline void setExit(bool quit) { exit = quit; }
	void toggleFullscreen();

	Game();
	~Game();
	void run();
	void update(Uint32 time);
	void render(Uint32 time) const;
	void handleEvents(Uint32 time);
};