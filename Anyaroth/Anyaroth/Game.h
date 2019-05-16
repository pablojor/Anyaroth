#pragma once
#include <list>
#include <vector>
#include <map>

#include "Texture.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "DialoguePanel.h"
#include "SoundManager.h"

// Resolución interna del juego
const int GAME_RESOLUTION_X = 1920;
const int GAME_RESOLUTION_Y = 1080;

//Distancia que recorre la camara
const int LEVEL_WIDTH = GAME_RESOLUTION_X * 10;
const int LEVEL_HEIGHT = GAME_RESOLUTION_Y * 3;

const string INFO_PATH = "..\\files\\info\\";
const string TILEMAPS_PATH = "..\\files\\tilemaps\\";
const string SPRITES_PATH = "..\\assets\\sprites\\";
const string SOUNDS_PATH = "..\\assets\\sounds\\";
const string FONTS_PATH = "..\\assets\\fonts\\";

const Uint32 FRAME_RATE = 1000 / 60;
const int TILES_SIZE = 16;
const double M_TO_PIXEL = 8;
const double BUTTON_SCALE = 0.25;
const int JOYSTICK_DEADZONE = 8000;

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
	MISIL = 1024,
	LASER = 2048,
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
	map <string, Dialogue> _dialogues;
	
	SDL_GameController* _joystick = nullptr;
	bool _joystickAttached;//Indica si hay algun mando conectado se este usando o no
	bool _usingJoystick = false; // Indica si se esta usando el mando, si es falso se usa el raton 
	
	float _timestep = FRAME_RATE / 1000.0f;
	bool _exit = false;

	//valor entre 1 y 10
	double _controllerSensitivity = 10;

public:
	Game();
	~Game();

	void run();
	void start();
	void updateWorld(float timeStep, int velocityIterations, int positionIterations);
	void update(double deltaTime);
	void render() const;
	void handleEvents();

	//Metodos
	void createTextures();
	void createFonts();
	void createSounds();
	void createDialogues();
	void initialiseJoysticks();

	inline GameState* getCurrentState() const { return _stateMachine->currentState(); }
	inline void pushState(GameState* state) { _stateMachine->pushState(state); }
	inline void changeState(GameState* state) { _stateMachine->changeState(state); }
	inline void popState() { _stateMachine->popState(); }

	inline Texture* getTexture(string nameText) { return _textures[nameText]; }
	inline Font* getFont(string nameFont) { return _fonts[nameFont]; }
	inline Dialogue getDialogue(string nameDialogue) { return _dialogues[nameDialogue]; }
	inline SDL_GameController* getJoystick() const { return _joystick; }
	inline bool isJoystick() const { return _joystickAttached; }
	inline bool usingJoystick() const{ return _usingJoystick; }
	inline void changeControlMode() { _usingJoystick = !_usingJoystick; }
	inline void setControlMode(bool controlMode) { _usingJoystick = controlMode; }// si control mode es true o 1 se usa el mando si no se usa el raton 

	inline SDL_Renderer* getRenderer() const { return _renderer; }
	inline SDL_Window* getWindow() const { return _window; }

	inline SoundManager* getSoundManager() const { return _soundManager; }

	inline void setTimestep(float timestep) { _timestep = timestep; }
	inline void setExit(bool quit) { _exit = quit; }

	inline int random(int low, int high) const { return low + (rand() % abs(high - low)); }

	void setSensitivity(double sensitiviy);
	inline double getSensitivity() const { return _controllerSensitivity; }

	void toggleFullscreen();
};