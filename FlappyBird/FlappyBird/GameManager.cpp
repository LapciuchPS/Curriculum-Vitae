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

	this->player.emplace(sf::Vector2f(this->gameWindow.getSize().x / 3.0f, this->gameWindow.getSize().y / 2.0f));

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
				this->player->jump();

		}
	}

	this->player->update(this->deltaTime);
}

void GameManager::renderGame()
{
	this->gameWindow.clear();

	this->player->drawPlayer(this->gameWindow);

	this->gameWindow.display();
}
