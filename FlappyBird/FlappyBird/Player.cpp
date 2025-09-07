#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Configurations.h"

Player::Player(const PlayerConfiguration& playerConfig) :
	MapObject(playerConfig.startingPoint, playerConfig.size, playerConfig.direction, playerConfig.jumpingSpeed, SceneInterface::objectID::player, std::make_unique<LinearMovement>(), true),
	fallingSpeed(playerConfig.fallingSpeed), jumpDistance(playerConfig.jumpDistance), jumpDistanceLeft(0.f)
{

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
}

void Player::draw(sf::RenderTarget& target)
{
	MapObject::draw(target);
}

void Player::onNotify(const Event& event)
{
	if (event.getEventType() == Event::EventType::pipeCollision || event.getEventType() == Event::EventType::screenCollision)
		this->setIsAlive(false);
}

