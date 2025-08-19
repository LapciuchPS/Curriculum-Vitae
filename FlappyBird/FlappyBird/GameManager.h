#pragma once
#include "Scene.h"
#include "Configurations.h"

class GameManager
{
private:
	//private variables
	sf::RenderWindow gameWindow;
	std::optional<sf::Event> currentEvent;
	sf::Clock deltaTimeClock, gameClock;
	float deltaTime = 0;

	//GameConfig
	GameConfiguration gameConfig;

	//Scenes
	Scene gameScene;

	//private functions
	void initWindow();

public:
	//public functions
	GameManager();
	~GameManager();

	int rand_int(int low, int high);
	bool isRunning() const;

	void makeObstacles();
	void updateGame();
	void renderGame();
};

