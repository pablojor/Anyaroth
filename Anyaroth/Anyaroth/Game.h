#pragma once
#include <list>
#include <vector>
#include <map>

#include "Texture.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PauseState.h"
#include "Gun.h"
#include "Shooter.h"

// Resolución interna del juego
const int GAME_RESOLUTION_X = 480;
const int GAME_RESOLUTION_Y = 270;

const int LEVEL_WIDTH = GAME_RESOLUTION_X * 5;
const int LEVEL_HEIGHT = GAME_RESOLUTION_Y * 5;

const string INFO_PATH = "..\\files\\info\\";
const string FONTS_PATH = "..\\font\\";
const string FILES_PATH = "..\\files\\levels\\";
const string SAVES_PATH = "..\\files\\saves\\";
const string SPRITE_PATH = "..\\assets\\sprites\\";
const string TILEMAP_PATH = "..\\files\\tilemaps\\";

const int NUM_TEXTURES = 15;
const int NUM_FONTS = 0;
const int TILES_W = 16;
const int TILES_H = 16;

const double M_TO_PIXEL = 8;
const double BUTTON_SCALE = 0.25;

//ARMAS
const int NUM_GUNS = 2; //N�mero de armas en el juego

struct GunAttributes
{
	Shooter shooter;
	string name;
	int maxAmmo;
	int maxClip;
};

enum _Category {
	FLOOR = 0x0001,
	ENEMIES = 0x0002,
	PLAYER = 0x0003,
	OBJECTS = 0x0004,
	PLAYER_BULLETS=0x0005,
	ENEMY_BULLETS=0x0006

};

class Game
{
	private:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		map <string, Texture*> textures;
		GameStateMachine* stateMachine = new GameStateMachine();
		vector<string> texturesName;
		b2World* _world = nullptr;
		bool exit = false;

	public:
		vector<int> var;

		//Las armas que hay en el juego
		enum GameGun
		{
			BasicGun,
			BasicShotgun
		};
		GunAttributes gameGuns[NUM_GUNS] = 
		{
			{ Shooter(),"Pistola",60,12 },
			{ Shooter(),"Escopeta",30,2 }
		};

		//Metodos
		void createTextures();
		void pushState(GameState* state);
		void changeState(GameState* state);
		void popState();
		Texture* getTexture(string nameText);
		inline SDL_Renderer* getRenderer() const { return renderer; }
		inline b2World* getWorld() const { return _world; }
		inline void setExit(bool quit) { exit = quit; }
		void newGame();
		void load();
		void save();

		Game();
		~Game();
		void run();
		void update(Uint32 time);
		void render(Uint32 time) const;
		void handleEvents(Uint32 time);
};