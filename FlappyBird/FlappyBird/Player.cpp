#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Configurations.h"

Player::Player(const PlayerConfiguration& playerConfig) :
	MapObject(playerConfig.startingPoint, playerConfig.size, playerConfig.direction, playerConfig.jumpingSpeed, SceneInterface::objectID::player, std::make_unique<LinearMovement>(), true),
	fallingSpeed(playerConfig.fallingSpeed), jumpDistance(playerConfig.jumpDistance), jumpDistanceLeft(0.f)
{
	
	//for testing
	this->playerSketch.setPosition(playerConfig.startingPoint);
	this->playerSketch.setSize(playerConfig.size);
	this->playerSketch.setFillColor(sf::Color::Yellow);
}

void Player::jump()
{
	this->jumpDistanceLeft = this->jumpDistance;
}

void Player::update(float deltaTime)
{

	if (this->jumpDistanceLeft > 0.f)
	{
		float move = MapObject::getObjectSpeed() * deltaTime;
		this->jumpDistanceLeft -= move;
		MapObject::update(deltaTime);
	}
	else MapObject::moveObject({ 0.f, this->fallingSpeed * deltaTime });

	//for testing
	this->playerSketch.setPosition(MapObject::getObjectPosition());
}

void Player::draw(sf::RenderTarget& target)
{
	this->drawPlayer(target);
}

//for testing
void Player::drawPlayer(sf::RenderTarget& target)
{
	target.draw(this->playerSketch);
}
