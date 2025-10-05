#include "stdafx.h"
#include "Configurations.h"

//Game Config
void GameConfiguration::initPlayerVariables()
{
	float playerSideSize = this->gameWindowSize.y * 0.07f;

	this->playerConfig.size = sf::Vector2f({ playerSideSize, playerSideSize });
	this->playerConfig.startingPoint = sf::Vector2f({ this->gameWindowSize.x * 0.3f, this->gameWindowSize.y * 0.5f });
	this->playerConfig.frameScale = { 2.3f, 2.3f };
	this->playerConfig.frameSize = sf::Vector2i({ 64,64 });
	this->playerConfig.speed = 0.f;
	this->playerConfig.gravity = 2000.f;
	this->playerConfig.jumpForce = 700.f;
	this->playerConfig.direction = { 0.f, -1.f };
}

void GameConfiguration::initPipeVariables()
{
	//pipe
	float pipeSideSize = this->gameWindowSize.y * 0.12f;

	this->pipeConfig.size = sf::Vector2f({ pipeSideSize, pipeSideSize });
	this->pipeConfig.speed = this->gameWindowSize.x * 0.15f;
	this->pipeConfig.startingPoint = sf::Vector2f({ static_cast<float>(this->gameWindowSize.x), static_cast<float>(this->gameWindowSize.y)});
	this->pipeConfig.direction = { -1.0, 0.f };

	//gap
	this->pipeConfig.gapSizeY = this->gameWindowSize.y * 0.23f;

	//space between pipes
	this->pipeConfig.spawnLocationX = this->gameWindowSize.x * 0.55;
}

void GameConfiguration::initCloudVariables()
{
	//Texture proportion: x - 55px, y - 25px

	float cloudSideX = this->gameWindowSize.x * 0.27f;
	float cloudSideY = cloudSideX * 25/55;

	this->cloudConfig.size = sf::Vector2f(cloudSideX, cloudSideY);
	this->cloudConfig.startingPoint = sf::Vector2f({ static_cast<float>(this->gameWindowSize.x), static_cast<float>(this->gameWindowSize.y) });
	this->cloudConfig.speed = this->gameWindowSize.x * 0.08f;
	this->cloudConfig.direction = { -1.0, 0.f };
	this->cloudConfig.spawnTime = 5.f;
	this->cloudConfig.spawnTimeInterval = {1, 15};
}

void GameConfiguration::initBonusVariables()
{
	//texture proportion (balloon texture): x - 20, y - 24 px
	//balloon with a rope: x - 20, y - 41 px

	float cloudSideY = this->gameWindowSize.y * 0.07f;
	float cloudSideX = cloudSideY * 20 / 24;
	
	this->bonusConfig.extraPointsInterval = std::pair(-2, 1);
	this->bonusConfig.size = { cloudSideX, cloudSideY };
	this->bonusConfig.startingPoint = sf::Vector2f({ static_cast<float>(this->gameWindowSize.x), static_cast<float>(this->gameWindowSize.y) });
	this->bonusConfig.direction = { -1.f, 1.f };
	this->bonusConfig.speed = this->gameWindowSize.x * 0.15f;
	this->bonusConfig.frameSize = { 20, 24 };
	this->bonusConfig.spawnTime = 8.f;
	this->bonusConfig.spawnTimeInterval = { 15, 20 };

	//bonus location - the center between two pipes (without hitboxes size)
	this->bonusConfig.spawnLocationX = this->gameWindowSize.x + (this->gameWindowSize.x - this->pipeConfig.spawnLocationX)/2 + this->pipeConfig.size.x/2;
}

void GameConfiguration::initScoreVariables()
{
	sf::Vector2f scorePosition = sf::Vector2f({ this->gameWindowSize.x/2.f, this->gameWindowSize.y*0.2f });

	this->scoreConfig.position = scorePosition;
	this->scoreConfig.characterSize = this->gameWindowSize.y * 0.1f;
	this->scoreConfig.outlineColor = sf::Color::Black;
}

void GameConfiguration::initVariables()
{
	//player
	this->initPlayerVariables();

	//pipe element
	this->initPipeVariables();

	//cloud
	this->initCloudVariables();

	//bonus
	this->initBonusVariables();

	//score
	this->initScoreVariables();
}

//public functions
GameConfiguration::GameConfiguration(const sf::Vector2u& windowSize) :
	gameWindowSize(windowSize)
{
	this->initVariables();
}

void GameConfiguration::updatePassedTime(float deltaTime)
{
	this->addTimeToPassedTime<CloudConfiguration>(deltaTime);
	this->addTimeToPassedTime<BonusConfiguration>(deltaTime);
}

//getters
const sf::Vector2u& GameConfiguration::getGameWindowSize() const
{
	return this->gameWindowSize;
}

