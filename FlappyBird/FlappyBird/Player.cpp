#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"

Player::Player(const sf::Vector2f& playerPosition, const sf::Vector2f& playerSize) :
	MapObject(playerPosition, playerSize),
	jumpingSpeed(350.f), fallingSpeed(400.f), jumpDistanceLeft(0.f),
	playerSprite(ResourceManager::getResources().getPlayerSpriteSheet())
{
	
	//for testing
	this->playerSketch.setPosition(playerPosition);
	this->playerSketch.setSize(playerSize);
	this->playerSketch.setFillColor(sf::Color::Yellow);
}

void Player::jump()
{
	this->jumpDistanceLeft = 150.f;
}

void Player::update(const float deltaTime)
{
	sf::Vector2f currentPlayerPosition = MapObject::getObjectPosition();

	if (this->jumpDistanceLeft > 0.f)
	{
		float move = this->jumpingSpeed * deltaTime;

		this->jumpDistanceLeft -= move;
		currentPlayerPosition.y -= move;

	}
	else currentPlayerPosition.y += this->fallingSpeed * deltaTime;


	MapObject::setObjectPosition(currentPlayerPosition);

	//for testing
	this->playerSketch.setPosition(MapObject::getObjectPosition());
}


void Player::draw(sf::RenderTarget& target)
{
	target.draw(this->playerSketch);
}
