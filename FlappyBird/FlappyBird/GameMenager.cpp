#include "stdafx.h"
#include "GameMenager.h"

//private functions

void GameMenager::initWindow()
{
	this->gameWindow = sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "FlappyBird", sf::Style::Titlebar || sf::Style::Close, sf::State::Windowed);
	this->gameWindow.setFramerateLimit(60);
}


//public functions

GameMenager::GameMenager()
{
	this->initWindow();
}

GameMenager::~GameMenager()
{

}

void GameMenager::updateGame()
{

}

void GameMenager::renderGame()
{

}
