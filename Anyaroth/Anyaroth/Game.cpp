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
	TTF_Init();
	window = SDL_CreateWindow("Anyaroth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480 * RESOLUTION, 270 * RESOLUTION, SDL_WINDOW_SHOWN);
	//window = SDL_CreateWindow("Anayroth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 760, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//---Create textures
	createTextures();
	_world = new b2World(b2Vec2(0.0, 9.8));
	//---Create states
	states[Play] = new PlayState(this);

	stateMachine->pushState(states[Play]);
	//World

	
	debugger.getRenderer(renderer);
	debugger.SetFlags(b2Draw::e_shapeBit);

	//Gestion de colisiones
	_world->SetContactListener(&colManager);
	_world->SetDebugDraw(&debugger);
}

Game::~Game()
{
	int tamV = texturesName.size();
	for (int i = 0; i < tamV; i++)
	{
		delete textures[texturesName[i]];
		textures.erase(texturesName[i]);
	}

	for (int i = 0; i < NUM_STATES; i++)
		delete states[i];

	delete stateMachine;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run()
{
	uint startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!exit)
	{
		render();
		handleEvents();
		frameTime = SDL_GetTicks() - startTime;
		//if (frameTime >= var[FRAME_RATE])
		if (frameTime >= 60)
		{
			update();
			startTime = SDL_GetTicks();
		}

	}
}

void Game::update()
{
	stateMachine->currentState()->update();
	_world->Step(1 / 20.0, 8, 3);
}

void Game::render() const
{
	SDL_RenderClear(renderer);
	
	stateMachine->currentState()->render();
	//_world->DrawDebugData();

	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit)
	{
		if (event.type == SDL_QUIT)
			exit = true;

		stateMachine->currentState()->handleEvents(event);
	}
}