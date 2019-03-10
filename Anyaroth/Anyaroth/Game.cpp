#include "Game.h"
#include <json.hpp>

void Game::createTextures()
{
	ifstream input;
	input.open(INFO_PATH + "textures.json");
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

			textures.insert(pair <string, Texture*>(id, new Texture(renderer, SPRITE_PATH + name, fil, col)));
			texturesName.push_back(id);
		}
	}
	input.close();
}

void Game::pushState(GameState* state)
{
	stateMachine->pushState(state);
}

void Game::changeState(GameState* state)
{
	stateMachine->changeState(state);
}

void Game::popState()
{
	stateMachine->popState();
}

Texture* Game::getTexture(string nameText)
{
	return textures[nameText];
}


void Game::toggleFullscreen() {
	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP; //fake fullscreen (windowed mode)
	bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
	SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);

	//SDL_SetRelativeMouseMode(IsFullscreen ? SDL_FALSE : SDL_TRUE);
}

Font * Game::getFont(string nameFont)
{
	return _fonts[nameFont];

}

void Game::newGame()
{

}

void Game::load()
{

}

void Game::save()
{

}

Game::Game()
{
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS /*SDL_INIT_EVERYTHING*/);
	TTF_Init();//Ventana del tama�o de la pantalla de cada dispositivo
	SDL_DisplayMode monitor;
	SDL_GetCurrentDisplayMode(0, &monitor);
	auto win_width = monitor.w - 50;
	auto win_height = monitor.h - 80;

	window = SDL_CreateWindow("Anyaroth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(renderer, GAME_RESOLUTION_X, GAME_RESOLUTION_Y);

	//Icon
	SDL_Surface* icon = IMG_Load("..\\icon.png");
	SDL_SetWindowIcon(window, icon);

	//Show cursor
	SDL_ShowCursor(true);
	//-----------------------------------------
	//Ajustamos el viewPort
	/*SDL_Rect viewport;
	viewport.x = 0;
	viewport.y = 0;
	viewport.w = 480 * RESOLUTION;
	viewport.h = 270 * RESOLUTION;
	SDL_RenderSetViewport(renderer, &viewport);*/
	//-----------------------------------------

	//---Create textures
	createTextures();
	//---Create world
	_world = new b2World(b2Vec2(0.0, 9.8));
	//---Create fonts
	_fonts["ARIAL12"] = new Font(FONTS_PATH + "arial.ttf", 12);
	//---Create states
	stateMachine->pushState(new MenuState(this));
}

Game::~Game()
{
	int tamV = texturesName.size();
	for (int i = 0; i < tamV; i++)
	{
		delete textures[texturesName[i]];
		textures.erase(texturesName[i]);
	}

	for (auto it = _fonts.begin(); it != _fonts.end(); it++)
		delete it->second;
		
	//delete guns
	for (int i = 0; i < gameGuns.size(); i++)
	{
		delete gameGuns[i].shooter;
	}
	delete stateMachine;
	delete _world;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run()
{
	while (!exit) {
		Uint32 startTime = SDL_GetTicks();
		handleEvents(startTime);
		update(startTime);
		render(startTime);

		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 60)
			SDL_Delay(60 - frameTime);
	}
}

void Game::update(Uint32 time)
{
	stateMachine->currentState()->update();
}

void Game::render(Uint32 time) const
{
	SDL_RenderClear(renderer);
	stateMachine->currentState()->render();
	//_world->DrawDebugData();

	SDL_RenderPresent(renderer);
}

void Game::handleEvents(Uint32 time)
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit)
	{
		if (event.type == SDL_QUIT)
			exit = true;
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_F11)
			{
				toggleFullscreen();
			}
		}

		stateMachine->currentState()->handleEvents(event);
	}
}