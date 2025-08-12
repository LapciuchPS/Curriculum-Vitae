#include "stdafx.h"
#include "GameManager.h"

int main()
{
	GameManager game;

	while (game.isRunning())
	{
		game.updateGame();

		game.renderGame();
	}
}