#include "Game.h"
#include "AnyarothError.h"
#include <json.hpp>

void Game::createTextures()
{
	ifstream input;
	input.open(INFO_PATH + "assets.json");
	if (input.is_open())
	{
		nlohmann::json j;
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

			_textures.insert(pair <string, Texture*>(id, new Texture(_renderer, SPRITE_PATH + name, fil, col)));
		}
	}
	else
		throw AnyarothError("No se ha encontrado el archivo");

	input.close();
}

void Game::createFonts()
{
	ifstream input;
	input.open(INFO_PATH + "assets.json");
	if (input.is_open())
	{
		nlohmann::json j;
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
		throw AnyarothError("No se ha encontrado el archivo");

	input.close();
}

void Game::pushState(GameState* state)
{
	_stateMachine->pushState(state);
}

void Game::changeState(GameState* state)
{
	_stateMachine->changeState(state);
}

void Game::popState()
{
	_stateMachine->popState();
}

Texture* Game::getTexture(string nameText)
{
	return _textures[nameText];
}

Font * Game::getFont(string nameFont)
{
	return _fonts[nameFont];
}

void Game::toggleFullscreen()
{
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP; //fake fullscreen (windowed mode)
	bool IsFullscreen = SDL_GetWindowFlags(_window) & FullscreenFlag;
	SDL_SetWindowFullscreen(_window, IsFullscreen ? 0 : FullscreenFlag);
}

Game::Game()
{
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	TTF_Init(); //Ventana del tamaño de la pantalla de cada dispositivo
	SDL_DisplayMode monitor;
	SDL_GetCurrentDisplayMode(0, &monitor);
	auto win_width = monitor.w - 50;
	auto win_height = monitor.h - 80;

	_window = SDL_CreateWindow("Anyaroth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(_renderer, GAME_RESOLUTION_X, GAME_RESOLUTION_Y);

	//Icon
	SDL_Surface* icon = IMG_Load("..\\icon.png");
	SDL_SetWindowIcon(_window, icon);

	//Show cursor
	SDL_ShowCursor(true);

	//---Create textures
	createTextures();
	//---Create fonts
	createFonts();
	//---Create world
	_world = new b2World(b2Vec2(0.0, 9.8));
	//---Create states
	_stateMachine->pushState(new MenuState(this));
}

Game::~Game()
{
	//delete textures
	for (auto it = _textures.begin(); it != _textures.end(); it++)
	{
		delete (*it).second;
	}

	//delete fonts
	for (auto it = _fonts.begin(); it != _fonts.end(); it++)
	{
		delete (*it).second;
	}

	delete _stateMachine;
	delete _world;
	delete _soundManager;
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Game::run()
{
	double frameTime = FRAME_RATE;

	while (!_exit)
	{
		double startTime = SDL_GetTicks();

		handleEvents();
		update(frameTime);
		_world->Step(1 / 60.0, 8, 3);
		render();

		frameTime = SDL_GetTicks() - startTime;

		if (frameTime < FRAME_RATE)
			SDL_Delay(FRAME_RATE - frameTime);
	}
}

void Game::update(double time)
{
	_stateMachine->currentState()->update(time);
}

void Game::render() const
{
	SDL_RenderClear(_renderer);
	_stateMachine->currentState()->render();
	_world->DrawDebugData();
	SDL_RenderPresent(_renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !_exit)
	{
		if (event.type == SDL_QUIT)
			_exit = true;
		else if (event.type == SDL_KEYDOWN)
			if (event.key.keysym.sym == SDLK_F11)
				toggleFullscreen();

		_stateMachine->currentState()->handleEvents(event);
	}
}