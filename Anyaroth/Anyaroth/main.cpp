#include "Game.h"
#include "checkML.h"

int main(int argc, char* argv[])
{
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