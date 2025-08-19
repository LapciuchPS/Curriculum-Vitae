#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Configurations.h"

Player::Player(const PlayerConfiguration& playerCFG) :
	MapObject(SceneInterface::objectID::player, playerCFG.startingPoint, playerCFG.size),
	jumpingSpeed(playerCFG.jumpingSpeed), fallingSpeed(playerCFG.fallingSpeed), jumpDistance(playerCFG.jumpDistance), jumpDistanceLeft(0.f)
{
	
	//for testing
	this->playerSketch.setPosition(playerCFG.startingPoint);
	this->playerSketch.setSize(playerCFG.size);
	this->playerSketch.setFillColor(sf::Color::Yellow);
}

void Player::jump()
{
	this->jumpDistanceLeft = this->jumpDistance;
}

void Player::update(const float& deltaTime)
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

void Player::draw(sf::RenderTarget& target)
{
	this->drawPlayer(target);
}

//for testing
void Player::drawPlayer(sf::RenderTarget& target)
{
	target.draw(this->playerSketch);
}
