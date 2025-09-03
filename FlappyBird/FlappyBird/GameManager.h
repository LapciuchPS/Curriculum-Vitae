#pragma once
#include "Scene.h"
#include "Configurations.h"
#include "EventHandler.h"

class GameManager
{
private:
	//private variables
	sf::RenderWindow gameWindow;
	std::optional<sf::Event> currentEvent;
	sf::Clock deltaTimeClock, gameClock;
	float deltaTime = 0;

	enum class ObjectName {player, pipe, cloud};

	//GameConfig
	GameConfiguration gameConfig;

	//Scenes
	Scene gameScene;

	//EventHandler
	EventHandler  eventHandler;

	//private functions
	int rand_int(int low, int high);
	void makeObject(ObjectName name);
	void makeObstacles();
	void initWindow();
	void startGame();

public:
	//public functions
	GameManager();
	~GameManager();


	bool isRunning() const;


	void updateGame();
	void renderGame();
};

