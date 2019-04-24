#include "Game.h"
#include <ctime>
#include "AnyarothError.h"
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

			_textures.insert(pair <string, Texture*>(id, new Texture(_renderer, SPRITE_PATH + name, fil, col)));
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

	_soundManager->addMusic("bgMusic", SOUNDS_PATH + "bgMusic.wav");
	_soundManager->addMusic("shop", SOUNDS_PATH + "shop.mp3");
	_soundManager->addSFX("example1", SOUNDS_PATH + "example1.wav");

	//UI SOUNDS
	_soundManager->addSFX("boton", SOUNDS_PATH + "boton.wav");
		//Next Text (CAMBIAR)
	_soundManager->addSFX("example", SOUNDS_PATH + "example.wav");
		//Dialogue
	_soundManager->addSFX("openDialogue", SOUNDS_PATH + "openDialogue.wav");
	_soundManager->addSFX("closeDialogue", SOUNDS_PATH + "closeDialogue.wav");

	//VOICES
		//Example
	_soundManager->addSFX("exampleVoice", SOUNDS_PATH + "exampleVoice.wav");
		//Boss
	_soundManager->addSFX("bossVoice", SOUNDS_PATH + "bossVoice.wav");

	//SOUND EFFECTS
	_soundManager->addSFX("pick1", SOUNDS_PATH + "itempick1.wav");

	_soundManager->addSFX("turretShot", SOUNDS_PATH + "turretShot.wav");
	_soundManager->addSFX("spentaSword", SOUNDS_PATH + "spentaSword.wav");
	_soundManager->addSFX("step", SOUNDS_PATH + "step.wav");
	_soundManager->addSFX("jump", SOUNDS_PATH + "jump.wav");
	_soundManager->addSFX("dash", SOUNDS_PATH + "dash.wav");
	_soundManager->addSFX("die1", SOUNDS_PATH + "die1.wav");
	_soundManager->addSFX("die2", SOUNDS_PATH + "die2.wav");
	_soundManager->addSFX("pain1", SOUNDS_PATH + "pain1.wav");
	_soundManager->addSFX("pain2", SOUNDS_PATH + "pain2.wav");
	_soundManager->addSFX("pain3", SOUNDS_PATH + "pain3.wav");
	_soundManager->addSFX("pain4", SOUNDS_PATH + "pain4.wav");
	_soundManager->addSFX("pain5", SOUNDS_PATH + "pain5.wav");
	_soundManager->addSFX("pain6", SOUNDS_PATH + "pain6.wav");

	_soundManager->addSFX("pistolShot", SOUNDS_PATH + "pistolShot.wav");
	_soundManager->addSFX("bulletGround", SOUNDS_PATH + "bulletGround.wav");
	_soundManager->addSFX("melee", SOUNDS_PATH + "melee.wav");
	_soundManager->addSFX("reload", SOUNDS_PATH + "reload.wav");
	_soundManager->addSFX("shotgun1", SOUNDS_PATH + "shotgun1.wav");
	_soundManager->addSFX("shotgun2", SOUNDS_PATH + "shotgun2.wav");
	_soundManager->addSFX("rifle1", SOUNDS_PATH + "rifle1.wav");
	_soundManager->addSFX("rifle2", SOUNDS_PATH + "rifle2.wav");
	_soundManager->addSFX("plasmaSniper", SOUNDS_PATH + "plasmaSniper.wav");
	_soundManager->addSFX("blackHole", SOUNDS_PATH + "blackHole.wav");
	_soundManager->addSFX("duringBH", SOUNDS_PATH + "duringBH.wav");
	_soundManager->addSFX("orb", SOUNDS_PATH + "orb.wav");
	_soundManager->addSFX("orbBounce", SOUNDS_PATH + "orbBounce.wav");
	_soundManager->addSFX("bombThrow", SOUNDS_PATH + "bombthrow.wav");
	_soundManager->addSFX("bombExplosion", SOUNDS_PATH + "bombexplosion.wav");

	_soundManager->addSFX("turretMeleeHit", SOUNDS_PATH + "turretMeleeHit.wav");
	_soundManager->addSFX("turretHit", SOUNDS_PATH + "turretHit.wav");
	_soundManager->addSFX("turretDeath", SOUNDS_PATH + "turretDeath.wav");
	_soundManager->addSFX("martyrHit", SOUNDS_PATH + "martyrHit.wav");
	_soundManager->addSFX("martyrMeleeHit", SOUNDS_PATH + "martyrMeleeHit.wav");
	_soundManager->addSFX("martyrDie", SOUNDS_PATH + "martyrDie.wav");
	_soundManager->addSFX("martyrExplosion", SOUNDS_PATH + "martyrExplosion.wav");
	_soundManager->addSFX("meleeEnemyHit", SOUNDS_PATH + "meleeEnemyHit.wav");
	_soundManager->addSFX("meleeDeath", SOUNDS_PATH + "meleeDeath.wav");
	_soundManager->addSFX("meleeHit", SOUNDS_PATH + "meleeHit.wav");
	_soundManager->addSFX("meleeEnemyAttack", SOUNDS_PATH + "meleeEnemyAttack.wav");
	_soundManager->addSFX("rocketLuncherUp", SOUNDS_PATH + "rocketLuncherUp.wav");
	_soundManager->addSFX("rocketLaunch", SOUNDS_PATH + "rocketLaunch.wav");
	_soundManager->addSFX("boss1Hit", SOUNDS_PATH + "boss1Hit.wav");
	_soundManager->addSFX("boss1Interfase1", SOUNDS_PATH + "boss1Interfase1.wav");
	_soundManager->addSFX("boss1Interfase2", SOUNDS_PATH + "boss1Interfase2.wav");
	_soundManager->addSFX("boss1Interfase3", SOUNDS_PATH + "boss1Interfase3.wav");
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
	_joystickAttached = _joystick != nullptr;
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
	SDL_Surface* icon = IMG_Load((SPRITE_PATH + "icon.png").c_str());
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
	//---Create world
	_world = new b2World(b2Vec2(0.0, 9.8));
	//---Create states
	_stateMachine->pushState(new MenuState(this));
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
	ParticleManager::deleteManager();
	delete _world;
	delete _soundManager;
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

		handleEvents();

		while (lag >= FRAME_RATE)
		{
			_world->Step((float)FRAME_RATE / 1000.0f, 8, 3);
			update(FRAME_RATE);
			lag -= FRAME_RATE;
		}
		render();
	}
}

void Game::update(const double& deltaTime)
{
	_stateMachine->currentState()->update(deltaTime);
	_stateMachine->currentState()->post_update();
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
		{
			if (event.key.keysym.sym == SDLK_F11)
				toggleFullscreen();
			else if (event.key.keysym.sym == SDLK_1)
				_soundManager->playSFX("example");
			else if (event.key.keysym.sym == SDLK_2)
				_soundManager->playSFX("example1");
		}

		_stateMachine->currentState()->handleEvent(event);
	}
}