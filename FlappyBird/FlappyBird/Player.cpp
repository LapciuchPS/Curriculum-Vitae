#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"

void Player::initPlayerVariables()
{
	this->velocityY = 20.f;
	this->playerShape.emplace(MapObject::getObjectPosition(), MapObject::getObjectSize);
	this->playerSprite.emplace(ResourceManager::getResources().getPlayerSpriteSheet());
}

Player::Player(sf::Vector2f playerPosition, sf::Vector2f playerSize): MapObject(playerPosition, playerSize)
{
	this->initPlayerVariables();
	
	//for testing
	this->playerSketch.setPosition(playerPosition);
	this->playerSketch.setSize(playerSize);
	this->playerSketch.setFillColor(sf::Color::Yellow);
}

void Player::jump()
{

}
