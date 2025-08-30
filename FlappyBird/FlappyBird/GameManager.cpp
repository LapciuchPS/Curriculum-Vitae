#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "InteractableObjects.h"


//private functions
void GameManager::initWindow()
{
	this->gameWindow = sf::RenderWindow(sf::VideoMode(this->gameConfig.getGameWindowSize()), "FlappyBird", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed);
	this->gameWindow.setFramerateLimit(60);
}

//public functions

GameManager::GameManager():
	eventHandler(&gameScene)
{
	this->initWindow();

	//init Player
	this->makeObject(ObjectName::player);

	//init clock
	this->gameClock.start();
}

GameManager::~GameManager()
{

}

int GameManager::rand_int(int low, int high)
{
	static std::default_random_engine re{ std::random_device{}() };

	using Dist = std::uniform_int_distribution<int>;
	static Dist uid{};
	return uid(re, Dist::param_type{ low,high });
}

bool GameManager::isRunning() const
{
	return this->gameWindow.isOpen();
}

void GameManager::makeObject(ObjectName name)
{
	std::unique_ptr<SceneInterface> newObject;
	int randomPosY = this->rand_int(0, this->gameWindow.getSize().y);

	switch (name)
	{
	case ObjectName::player:
		newObject = std::make_unique<Player>(this->gameConfig.getPlayerConfig());
		break;

	case ObjectName::pipe:
		this->gameConfig.setPipeGapPos(sf::Vector2f(this->gameWindow.getSize().x, randomPosY));
		newObject = std::make_unique<Pipe>(this->gameConfig.getPipeConfig(), this->gameWindow.getSize().y);
		break;
	case ObjectName::cloud:
		this->gameConfig.setCloudPos(sf::Vector2f(this->gameWindow.getSize().x, randomPosY));
		newObject = std::make_unique<Cloud>(this->gameConfig.getCloudConfig());
		break;
	}

	if (EventObserver* ptr = dynamic_cast<EventObserver*>(newObject.get()))
		this->eventHandler.addObserver(ptr);

	this->gameScene.addObject(std::move(newObject));
}

void GameManager::makeObstacles()
{
	//init Pipe 
	if (this->gameClock.getElapsedTime().asSeconds() >= 3.f)
	{
		//this->makeObject(ObjectName::pipe);

		switch (this->rand_int(0, 1))
		{
		case 0: this->makeObject(ObjectName::pipe); break;

		case 1: this->makeObject(ObjectName::cloud); break;

		}
		
		this->gameClock.restart();
	}
}

void GameManager::updateGame()
{
	//passed time since the last frame
	this->deltaTime = this->deltaTimeClock.restart().asSeconds();

	while ((this->currentEvent = this->gameWindow.pollEvent()))
	{
		if (this->currentEvent->is<sf::Event::Closed>())
			this->gameWindow.close();

		if (this->currentEvent->is<sf::Event::KeyReleased>() )
		{
			const sf::Event::KeyReleased* key = this->currentEvent->getIf<sf::Event::KeyReleased>();

			if (key->code == sf::Keyboard::Key::Space)
				this->gameScene.getPlayer()->jump();
		}
	}

	this->makeObstacles();

	this->gameScene.clearDeadObject(this->eventHandler);
	this->gameScene.update(deltaTime);

	this->eventHandler.update(this->gameWindow.getSize());
}

void GameManager::renderGame()
{
	this->gameWindow.clear();

	this->gameScene.draw(this->gameWindow);

	this->gameWindow.display();
}


