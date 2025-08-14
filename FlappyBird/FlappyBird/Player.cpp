#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"

Player::Player(const sf::Vector2f& playerPosition, const sf::Vector2f& playerSize) :
	MapObject(playerPosition, playerSize),
	jumpingSpeed(350.f), fallingSpeed(400.f), jumpDistanceLeft(0.f)
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

	if (this->jumpDistanceLeft > 0.f)
	{
		float move = this->jumpingSpeed * deltaTime;
		this->jumpDistanceLeft -= move;
		MapObject::moveObject({ 0.f, -move });
	}
	else MapObject::moveObject({ 0.f, this->fallingSpeed * deltaTime });

	//for testing
	this->playerSketch.setPosition(MapObject::getObjectPosition());
}

void Player::draw(sf::RenderTarget& target, const sf::Sprite& objectSprite) const
{
}

//for testing
void Player::drawPlayer(sf::RenderTarget& target)
{
	target.draw(this->playerSketch);
}
