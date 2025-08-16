#pragma once
#include "Scene.h"

class GameManager
{
private:
	//private variables
	sf::RenderWindow gameWindow;
	std::optional<sf::Event> currentEvent;
	sf::Clock gameClock;
	float deltaTime = 0;

	//Scenes
	Scene gameScene;

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

