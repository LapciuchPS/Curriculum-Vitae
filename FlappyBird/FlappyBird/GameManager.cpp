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
		newObject = std::make_unique<Player>(this->gameConfig.getConfiguration<PlayerConfiguration>());
		break;

	case ObjectName::pipe:
		randomPosY = this->rand_int(0, this->gameWindow.getSize().y);

		this->gameConfig.setObjectPos<PipeConfiguration>(sf::Vector2f(this->gameWindow.getSize().x, randomPosY));
		newObject = std::make_unique<Pipe>(this->gameConfig.getConfiguration<PipeConfiguration>(), this->gameWindow.getSize().y);
		break;

	case ObjectName::cloud:
		randomPosY = this->rand_int(0, this->gameWindow.getSize().y - this->gameConfig.getConfiguration<CloudConfiguration>().size.y/2);

		this->gameConfig.setObjectPos<CloudConfiguration>(sf::Vector2f(this->gameWindow.getSize().x, randomPosY));
		newObject = std::make_unique<Cloud>(this->gameConfig.getConfiguration<CloudConfiguration>());
		break;

	case ObjectName::bonus:
		randomPosY = this->rand_int(0, this->gameWindow.getSize().y);
		float posX = this->gameConfig.getConfiguration<BonusConfiguration>().spawnLocationX;

		this->gameConfig.setObjectPos<BonusConfiguration>(sf::Vector2f(posX, randomPosY));

		int pointsNumber = this->rand_int(-1,1);

		newObject = std::make_unique<ScoreChanger>(this->gameConfig.getConfiguration<BonusConfiguration>(),this->gameWindow.getSize().y, pointsNumber);
		break;
	}

	if (EventObserver* ptr = dynamic_cast<EventObserver*>(newObject.get()))
		this->eventHandler.addObserver(ptr);

	this->gameScene.addObject(std::move(newObject));
}

template<typename T>
void GameManager::changeSpawnCondition()
{
	//reset passed time
	this->gameConfig.setObjectTime<T>(0, GameConfiguration::TimeType::passedTime);

	//change spawn time for the next cloud
	int spawnIntervalMin = this->gameConfig.getConfiguration<T>().spawnTimeInterval.first;
	int spawnIntervalMax = this->gameConfig.getConfiguration<T>().spawnTimeInterval.second;

	int newSpawnTime = this->rand_int(spawnIntervalMin, spawnIntervalMax);
	this->gameConfig.setObjectTime<T>(newSpawnTime, GameConfiguration::TimeType::spawnTime);
}

void GameManager::makeObstacles()
{ 
	static bool bonusGenerate = false;

	if (!this->gameScene.getLastPipe())
		return;

	//spawn pipe
	float lastPipePosX = this->gameScene.getLastPipe()->getObjectHitbox().position.x;

	if (lastPipePosX <= this->gameConfig.getConfiguration<PipeConfiguration>().spawnLocationX)
	{
		this->makeObject(ObjectName::pipe);

		if (bonusGenerate)
		{
			this->makeObject(ObjectName::bonus);
			bonusGenerate = false;
		}
	}
		
	//spawn other objects
	this->gameConfig.updatePassedTime(this->deltaTime);

	//spawn cloud
	if (this->gameConfig.canBeSpawned<CloudConfiguration>())
	{
		this->makeObject(ObjectName::cloud);

		this->changeSpawnCondition<CloudConfiguration>();
	}

	//spawn cloud
	if (this->gameConfig.canBeSpawned<BonusConfiguration>())
	{
		bonusGenerate = true;

		this->changeSpawnCondition<BonusConfiguration>();
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

	//init pipe
	this->makeObject(ObjectName::pipe);

	//init score
	this->score.emplace(this->gameConfig.getConfiguration<ScoreConfiguration>());
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


