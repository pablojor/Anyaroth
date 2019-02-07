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
			_textures.insert(pair <string, Texture*> (id, new Texture(_renderer, SPRITE_PATH + name, fil, col)));
			_texturesName.push_back(id);
		}
	}
	input.close();
}

void Game::pushState(StateName nameState)
{
	_stateMachine->pushState(_states[nameState]);
}
void Game::changeState(StateName nameState)
{
	_stateMachine->changeState(_states[nameState]);
}


Texture* Game::getTexture(string nameText)
{
	return _textures[nameText];
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
	_window = SDL_CreateWindow("Anyaroth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, var[WIN_WIDTH], var[WIN_HEIGHT], SDL_WINDOW_SHOWN);
	
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

//---Create textures

	createTextures();
	
//---Create states
	_states[Play] = new PlayState(this);

	_stateMachine->pushState(_states[Play]);
}

Game::~Game()
{
	int tamV = _texturesName.size();
	for (int i = 0; i < tamV; i++)
	{
		delete _textures[_texturesName[i]];
		_textures.erase(_texturesName[i]);
	}

	for (int i = 0; i < NUM_STATES; i++)
		delete _states[i];


	delete _stateMachine;

	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Game::run()
{
	uint startTime, frameTime;
	startTime = SDL_GetTicks();

	while (!exit)
	{
		handleEvents();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= var[FRAME_RATE])
		{
			update();
			startTime = SDL_GetTicks();
		}
		render();
	}
}

void Game::update()
{
	_stateMachine->currentState()->update();
}

void Game::render() const
{
	SDL_RenderClear(_renderer);

	_stateMachine->currentState()->render();

	SDL_RenderPresent(_renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit)
	{
		if (event.type == SDL_QUIT)
			exit = true;

		_stateMachine->currentState()->handleEvents(event);
	}
}