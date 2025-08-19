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
}

void GameConfiguration::initPipeVariables()
{
	float pipeSideSize = this->gameWindowSize.y * 0.12f;

	this->pipeConfig.pipeSize = sf::Vector2f({ pipeSideSize, pipeSideSize });
	this->pipeConfig.speed = this->gameWindowSize.x * 0.15f;
	this->pipeConfig.pipeStartingPoint = sf::Vector2f({ static_cast<float>(this->gameWindowSize.x), static_cast<float>(this->gameWindowSize.y)});

	this->pipeConfig.gapSizeY = this->gameWindowSize.y * 0.28f;
	this->pipeConfig.gapPosition = { 0,0 };
}

void GameConfiguration::initVariables()
{
	//player
	this->initPlayerVariables();

	//pipe element
	this->initPipeVariables();
}

GameConfiguration::GameConfiguration(const sf::Vector2u& windowSize) :
	gameWindowSize(windowSize)
{
	this->initVariables();
}

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

void GameConfiguration::setPipeGapPos(const sf::Vector2f& gapPos)
{
	this->pipeConfig.gapPosition = gapPos;
}
