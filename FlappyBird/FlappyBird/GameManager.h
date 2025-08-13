#pragma once
#include "Player.h"

class GameManager
{
private:
	//private variables
	sf::RenderWindow gameWindow;
	std::optional<sf::Event> currentEvent;
	sf::Clock gameClock;
	float deltaTime = 0;

	//Player
	std::optional<Player> player;

	//private functions
	void initWindow();

public:
	//public functions
	GameManager();
	~GameManager();

	
	inline bool isRunning() const
	{
		return this->gameWindow.isOpen();
	}

	void updateGame();
	void renderGame();
};

