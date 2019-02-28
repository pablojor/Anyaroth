#include "Game.h"

void Game::createVariables()
{
	ifstream input;
	input.open(INFO_PATH + "info.txt");
	if (input.is_open())
	{
		for (int i = 0; i < NUM_VARIABLES; i++)
		{
			int value;
			string trash;
			input >> trash; input >> value;
			var.push_back(value);
		}
	}
	input.close();
}

void Game::createTextures()
{
	ifstream input;
	input.open(INFO_PATH + "textures.txt");
	if (input.is_open())
	{
		for (int i = 0; i < NUM_TEXTURES; i++)
		{
			string id; input >> id;
			string name; input >> name;
			int fil; input >> fil;
			int col; input >> col;
			textures.insert(pair <string, Texture*>(id, new Texture(renderer, SPRITE_PATH + name, fil, col)));
			texturesName.push_back(id);
		}
	}
	input.close();
}

void Game::pushState(StateName nameState)
{
	stateMachine->pushState(states[nameState]);
}

void Game::changeState(StateName nameState)
{
	stateMachine->changeState(states[nameState]);
}


Texture* Game::getTexture(string nameText)
{
	return textures[nameText];
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

//**************************************************************************************************************************//
//**************************************************************************************************************************//
//**************************************************************************************************************************//
//**************************************************************************************************************************//

Game::Game()
{
	createVariables();

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();//Ventana del tama�o de la pantalla de cada dispositivo
	SDL_DisplayMode monitor;
	SDL_GetCurrentDisplayMode(0, &monitor);
	auto win_width = monitor.w - 50;
	auto win_height = monitor.h - 80;
	//----------------------------------------

	window = SDL_CreateWindow("Anyaroth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
	//window = SDL_CreateWindow("Anayroth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 760, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface* icon = IMG_Load("..\\icon.png");
	SDL_SetWindowIcon(window, icon);

	//-----------------------------------------
	//Ajustamos el viewPort
	/*SDL_Rect viewport;
	viewport.x = 0;
	viewport.y = 0;
	viewport.w = 480 * RESOLUTION;
	viewport.h = 270 * RESOLUTION;
	SDL_RenderSetViewport(renderer, &viewport);*/
	//-----------------------------------------
	SDL_RenderSetLogicalSize(renderer, GAME_RESOLUTION_X, GAME_RESOLUTION_Y);
	//-----------------------------------------

	//---Create textures
	createTextures();
	//---Create fonts
	_fonts["ARIAL12"] = new Font(FONTS_PATH + "arial.ttf", 12);

	_world = new b2World(b2Vec2(0.0, 20));
	//---Create states
	states[Play] = new PlayState(this);

	stateMachine->pushState(states[Play]);
	//World	
	debugger.getRenderer(renderer);
	debugger.getTexture(getTexture("body"));
	debugger.SetFlags(b2Draw::e_shapeBit);
	debugger.getTexture(getTexture("body"));

	//Gestion de colisiones
	_world->SetContactListener(&colManager);
	//_world->SetDebugDraw(&debugger);
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

	for (int i = 0; i < NUM_STATES; i++)
		delete states[i];

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
	_world->Step(1 / 20.0, 8, 3);
}

void Game::render(Uint32 time) const
{
	SDL_RenderClear(renderer);
	
	stateMachine->currentState()->render();
	_world->DrawDebugData();

	SDL_RenderPresent(renderer);
}

void Game::handleEvents(Uint32 time)
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit)
	{
		if (event.type == SDL_QUIT)
			exit = true;

		stateMachine->currentState()->handleEvents(event);
	}
}