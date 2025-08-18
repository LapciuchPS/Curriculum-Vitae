#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "InteractableObjects.h"

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

	//init Player
	this->gameScene.addObject(std::make_unique<Player>(sf::Vector2f(this->gameWindow.getSize().x / 3.0f, this->gameWindow.getSize().y / 2.0f)));

	//init Pipe 
	this->gameScene.addObject(std::make_unique<Pipe>(sf::Vector2f(this->gameWindow.getSize().x,300.f), this->gameWindow.getSize().y));
}

GameManager::~GameManager()
{

}

void GameManager::updateGame()
{
	//passed time since the last frame
	this->deltaTime = this->gameClock.restart().asSeconds();

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

	this->gameScene.update(deltaTime);
}

void GameManager::renderGame()
{
	this->gameWindow.clear();

	this->gameScene.draw(this->gameWindow);

	this->gameWindow.display();
}
