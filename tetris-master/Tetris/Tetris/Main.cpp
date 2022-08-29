#include "Game.h"

int main(int argc, char* args[])
{
	Game::Init();

	while (Game::IsRunning())
	{
		Game::Draw();
		Game::Update();
	}

	Game::Destroy();

	return 0;
}