#include "Game.h"
#include "AnyarothError.h"
#include "ParticleManager.h"
#include <ctime>
#include <json.hpp>

using namespace nlohmann;

void Game::createTextures()
{
	ifstream input;
	input.open(INFO_PATH + "assets.json");
	if (input.is_open())
	{
		json j;
		input >> j;
		j = j["textures"];
		int numTextures = j.size();
		for (int i = 0; i < numTextures; i++)
		{
			string id, name;
			int fil, col;
			id = j[i][0].get<string>();
			name = j[i][1].get<string>();
			fil = j[i][2];
			col = j[i][3];

			_textures.insert(pair <string, Texture*>(id, new Texture(_renderer, SPRITES_PATH + name, fil, col)));
		}
	}
	else
		throw AnyarothError("No se ha encontrado el archivo introducido");

	input.close();
}

void Game::createFonts()
{
	ifstream input;
	input.open(INFO_PATH + "assets.json");
	if (input.is_open())
	{
		json j;
		input >> j;
		j = j["fonts"];
		int numFonts = j.size();
		string id, name;
		int size;
		for (int i = 0; i < numFonts; i++)
		{
			id = j[i][0].get<string>();
			name = j[i][1].get<string>();
			size = j[i][2];
			
			_fonts.insert(pair <string, Font*>(id, new Font(FONTS_PATH + name, size)));
		}
	}
	else
		throw AnyarothError("No se ha encontrado el archivo introducido");

	input.close();
}

void Game::createSounds()
{
	ifstream input;
	input.open(INFO_PATH + "assets.json");
	if (input.is_open())
	{
		json j, aux;
		input >> j;
		aux = j["sounds"];
		int numSounds = aux.size();
		string id, name;
		for (int i = 0; i < numSounds; i++)
		{
			id = aux[i][0].get<string>();
			name = aux[i][1].get<string>();

			_soundManager->addSFX(id, SOUNDS_PATH + name);
		}

		aux = j["music"];
		int numMusic = aux.size();
		for (int i = 0; i < numMusic; i++)
		{
			id = aux[i][0].get<string>();
			name = aux[i][1].get<string>();

			_soundManager->addMusic(id, SOUNDS_PATH + name);
		}
	}
	else
		throw AnyarothError("No se ha encontrado el archivo introducido");

	input.close();
}

void Game::createDialogues()
{
	ifstream input;
	input.open(INFO_PATH + "dialogues.json");
	if (input.is_open())
	{
		json j;
		input >> j;
		j = j["dialogues"];
		for (json::iterator it = j.begin(); it != j.end(); ++it) 
		{
			string id = it.key();
			json aux = it.value();
			int numDialogues = j.size();
			string face, voice, name;
			vector<string> conversation;
			vector<int> faces;
			vector<string> sounds;

			face = aux["face"].get<string>();
			name = aux["name"].get<string>();
			voice = aux["voice"].get<string>();
			conversation = aux["dialogue"].get<vector<string>>();
			faces = aux["faces"].get<vector<int>>();
			sounds = aux["sounds"].get<vector<string>>();

			_dialogues.insert(pair <string, Dialogue>(id, Dialogue{ getTexture(face),voice,name, conversation,faces,sounds }));
		}
	}
	else
		throw AnyarothError("No se ha encontrado el archivo introducido");

	input.close();
}


void Game::initialiseJoysticks()
{
	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			_joystick = SDL_GameControllerOpen(i);
		}
	}
	_joystickAttached = _usingJoystick = _joystick != nullptr;
}


void Game::setSensitivity(double sensitiviy)
{
	if (sensitiviy > 10)
		_controllerSensitivity = 10;
	else if (sensitiviy < 1)
		_controllerSensitivity = 1;
	else
		_controllerSensitivity = sensitiviy;
}

void Game::toggleFullscreen()
{
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP; //fake fullscreen (windowed mode)
	bool IsFullscreen = SDL_GetWindowFlags(_window) & FullscreenFlag;
	SDL_SetWindowFullscreen(_window, IsFullscreen ? 0 : FullscreenFlag);
}

Game::Game()
{
	srand(time(NULL));//random seed

	SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS| SDL_INIT_GAMECONTROLLER);
	TTF_Init(); //Ventana del tamaño de la pantalla de cada dispositivo
	SDL_DisplayMode monitor;
	SDL_GetCurrentDisplayMode(0, &monitor);
	auto win_width = monitor.w - 50;
	auto win_height = monitor.h - 80;

	_window = SDL_CreateWindow("Anyaroth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(_renderer, GAME_RESOLUTION_X, GAME_RESOLUTION_Y);

	//Icon
	SDL_Surface* icon = IMG_Load((SPRITES_PATH + "icon.png").c_str());
	SDL_SetWindowIcon(_window, icon);

	//Show cursor
	SDL_ShowCursor(true);

	//---Create textures
	createTextures();
	//---Create fonts
	createFonts();
	//---Create sounds
	_soundManager = new SoundManager();
	createSounds();
	//---Create dialogues
	createDialogues();
	//---Initialise Joysticks
	initialiseJoysticks();
	//---Create states
	_stateMachine->pushState(new MenuState(this));
	toggleFullscreen();
}

Game::~Game()
{
	//delete textures
	for (auto it = _textures.begin(); it != _textures.end(); it++)
		delete (*it).second;

	//delete fonts
	for (auto it = _fonts.begin(); it != _fonts.end(); it++)
		delete (*it).second;

	//close joysticks
	SDL_GameControllerClose(_joystick);


	delete _stateMachine;
	delete _soundManager;
	ParticleManager::deleteManager();
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Game::run()
{
	Uint32 deltaTime = FRAME_RATE;
	Uint32 startTime = SDL_GetTicks();
	Uint32 lag = 0;

	while (!_exit)
	{
		Uint32 current = SDL_GetTicks();
		Uint32 elapsed = current - startTime;
		startTime = current;
		lag += elapsed;

		start();
		handleEvents();

		while (lag >= FRAME_RATE && !_stateMachine->currentState()->hasToStart())
		{
			updateWorld(_timestep, 8, 3);
			update(FRAME_RATE);
			lag -= FRAME_RATE;
		}
		render();
	}
}

void Game::start()
{
	if (_stateMachine->currentState()->hasToStart())
	{
		_stateMachine->currentState()->start();
		_stateMachine->currentState()->setStarted(true);
	}
}

void Game::updateWorld(float timeStep, int velocityIterations, int positionIterations)
{
	_stateMachine->currentState()->updateWorld(timeStep, velocityIterations, positionIterations);
}

void Game::update(double deltaTime)
{
	_stateMachine->currentState()->update(deltaTime);
	_stateMachine->currentState()->post_update();
}

void Game::render() const
{
	SDL_RenderClear(_renderer);
	_stateMachine->currentState()->render();
	_stateMachine->currentState()->getWorld()->DrawDebugData();
	SDL_RenderPresent(_renderer);
}

void Game::handleEvents()
{
	bool handled = _stateMachine->currentState()->pre_handleEvent();

	SDL_Event event;
	while (SDL_PollEvent(&event) && !_exit && !handled)
	{
		if (event.type == SDL_QUIT)
			_exit = true;
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_F11)
				toggleFullscreen();
		}
		else if (event.type == SDL_CONTROLLERDEVICEADDED)
		{
			if (!isJoystick())
				initialiseJoysticks();
		}
		else if (event.type == SDL_CONTROLLERDEVICEREMOVED)
		{
			_joystickAttached = false;
			_usingJoystick = false;
			_joystick = nullptr;
		}
			
		else if (!_usingJoystick)
		{
			if (event.type == SDL_CONTROLLERAXISMOTION && abs(event.caxis.value) > JOYSTICK_DEADZONE) 
				changeControlMode();
			else if (event.type == SDL_CONTROLLERBUTTONDOWN)
				changeControlMode();
		}
		else if (_usingJoystick && (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_KEYDOWN))
			changeControlMode();

		_stateMachine->currentState()->handleEvent(event);
	}
}