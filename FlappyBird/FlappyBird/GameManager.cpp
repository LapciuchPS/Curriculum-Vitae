#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "InteractableObjects.h"


//private functions
int GameManager::rand_int(int low, int high)
{
	static std::default_random_engine re{ std::random_device{}() };

	using Dist = std::uniform_int_distribution<int>;
	static Dist uid{};
	return uid(re, Dist::param_type{ low,high });
}

void GameManager::makeObject(ObjectName name)
{
	std::unique_ptr<SceneInterface> newObject;
	int randomPosY = 0;

	switch (name)
	{
	case ObjectName::player:
		newObject = std::make_unique<Player>(this->gameConfig.getPlayerConfig());
		break;

	case ObjectName::pipe:
		randomPosY = this->rand_int(0, this->gameWindow.getSize().y);

		this->gameConfig.setPipeGapPos(sf::Vector2f(this->gameWindow.getSize().x, randomPosY));
		newObject = std::make_unique<Pipe>(this->gameConfig.getPipeConfig(), this->gameWindow.getSize().y);
		break;

	case ObjectName::cloud:
		randomPosY = this->rand_int(0, this->gameWindow.getSize().y - this->gameConfig.getCloudConfig().cloudSize.y/2);

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
	
	if (this->gameClock.getElapsedTime().asSeconds() >= 3.f)
	{
		//init Pipe 
		this->makeObject(ObjectName::pipe);

		switch (this->rand_int(0, 3))
		{
		case 0: //this->makeObject(ObjectName::pipe); break;

		case 1: this->makeObject(ObjectName::cloud); break;

		}

		this->gameClock.restart();
	}
}

void GameManager::initWindow()
{
	this->gameWindow = sf::RenderWindow(sf::VideoMode(this->gameConfig.getGameWindowSize()), "FlappyBird", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed);
	this->gameWindow.setFramerateLimit(144);
}

void GameManager::startGame()
{
	//init Player
	this->makeObject(ObjectName::player);

	//init score
	this->score.emplace(this->gameConfig.getScoreConfig());
	this->eventHandler.addObserver(&this->score.value());

	//start clock
	this->gameClock.start();
}

//public functions
GameManager::GameManager():
	eventHandler(&gameScene)
{
	this->initWindow();
	this->startGame();
}

GameManager::~GameManager()
{

}

bool GameManager::isRunning() const
{
	return this->gameWindow.isOpen();
}

void GameManager::updateGame()
{
	//if the player is dead, restart the game
	if (!this->gameScene.getPlayer()->getIsAlive())
	{
		this->eventHandler.removeAllObservers();
		this->gameScene.clearWholeScene();
		this->gameClock.reset();

		this->startGame();
	}


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
	this->gameWindow.clear(sf::Color::Cyan);

	this->gameScene.draw(this->gameWindow);
	this->score->draw(this->gameWindow);

	this->gameWindow.display();
}


