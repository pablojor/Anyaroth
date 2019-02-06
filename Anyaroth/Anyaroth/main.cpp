#include "Game.h"
#include "Layer.h"

int main(int argc, char* argv[])
{
	Layer* l = new Layer(2, nullptr);
	l->LoadTilemap("Prueba.json");

	try
	{
		Game game;
		game.run();
	}
	catch (string& exception)
	{
		cout << exception << endl;
	}

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	return 0;
}