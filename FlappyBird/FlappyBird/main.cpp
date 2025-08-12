#include "stdafx.h"
#include "GameMenager.h"

int main()
{
	GameMenager game;

	while (game.isRunning())
	{
		game.updateGame();

		game.renderGame();
	}
}