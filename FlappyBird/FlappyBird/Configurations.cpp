#include "stdafx.h"
#include "Configurations.h"

//Game Config
void GameConfiguration::initPlayerVariables()
{
	float playerSideSize = this->gameWindowSize.y * 0.05f;

	this->playerConfig.size = sf::Vector2f({ playerSideSize, playerSideSize });
	this->playerConfig.startingPoint = sf::Vector2f({ this->gameWindowSize.x * 0.3f, this->gameWindowSize.y * 0.5f });
	this->playerConfig.jumpingSpeed = this->gameWindowSize.y * 0.4f;
	this->playerConfig.fallingSpeed = this->gameWindowSize.y * 0.55f;
	this->playerConfig.jumpDistance = this->gameWindowSize.y * 0.16f;
	this->playerConfig.direction = { 0.f, -1.f };
}

void GameConfiguration::initPipeVariables()
{
	//pipe
	float pipeSideSize = this->gameWindowSize.y * 0.12f;

	this->pipeConfig.pipeSize = sf::Vector2f({ pipeSideSize, pipeSideSize });
	this->pipeConfig.speed = this->gameWindowSize.x * 0.15f;
	this->pipeConfig.pipeStartingPoint = sf::Vector2f({ static_cast<float>(this->gameWindowSize.x), static_cast<float>(this->gameWindowSize.y)});
	this->pipeConfig.direction = { -1.0, 0.f };

	//gap
	this->pipeConfig.gapSizeY = this->gameWindowSize.y * 0.28f;
	this->pipeConfig.gapPosition = { 0,0 };
}

void GameConfiguration::initCloudVariables()
{
	//Texture proportion: x - 55px, y - 25px

	float cloudSideX = this->gameWindowSize.x * 0.27f;
	float cloudSideY = cloudSideX * 25/55;

	this->cloudConfig.cloudSize = sf::Vector2f(cloudSideX, cloudSideY);
	this->cloudConfig.cloudStartingPoint = sf::Vector2f({ static_cast<float>(this->gameWindowSize.x), static_cast<float>(this->gameWindowSize.y) });
	this->cloudConfig.speed = this->gameWindowSize.x * 0.08f;
	this->cloudConfig.direction = { -1.0, 0.f };
}

void GameConfiguration::initVariables()
{
	//player
	this->initPlayerVariables();

	//pipe element
	this->initPipeVariables();

	//cloud
	this->initCloudVariables();
}

//public functions
GameConfiguration::GameConfiguration(const sf::Vector2u& windowSize) :
	gameWindowSize(windowSize)
{
	this->initVariables();
}

//getters
const sf::Vector2u& GameConfiguration::getGameWindowSize() const
{
	return this->gameWindowSize;
}

const PlayerConfiguration& GameConfiguration::getPlayerConfig() const
{
	return this->playerConfig;
}

const PipeConfiguration& GameConfiguration::getPipeConfig() const
{
	return this->pipeConfig;
}

const CloudConfiguration& GameConfiguration::getCloudConfig() const
{
	return this->cloudConfig;
}

void GameConfiguration::setPipeGapPos(const sf::Vector2f& gapPos)
{
	this->pipeConfig.gapPosition = gapPos;
}

void GameConfiguration::setCloudPos(const sf::Vector2f& cloudPos)
{
	this->cloudConfig.cloudStartingPoint = cloudPos;
}
