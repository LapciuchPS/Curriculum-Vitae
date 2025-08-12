#include "stdafx.h"
#include "GameManager.h"

//private functions

void GameManager::initWindow()
{
	this->gameWindow = sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "FlappyBird", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed);
	this->gameWindow.setFramerateLimit(60);
}


//public functions

GameManager::GameManager()
{
	this->initWindow();
}

GameManager::~GameManager()
{

}

void GameManager::updateGame()
{
	while (this->currentEvent = this->gameWindow.pollEvent())
	{
		if (this->currentEvent->is < sf::Event::Closed>())
			this->gameWindow.close();
	}
}

void GameManager::renderGame()
{

}
