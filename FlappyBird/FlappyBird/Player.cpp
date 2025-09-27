#include "stdafx.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Configurations.h"

Player::Player(const PlayerConfiguration& playerConfig) :
	MapObject(playerConfig.startingPoint, playerConfig.size, playerConfig.direction, playerConfig.speed, SceneInterface::objectID::player, std::make_unique<LinearMovement>()),
	frameSize(playerConfig.frameSize), velocityY(playerConfig.speed), gravity(playerConfig.gravity), jumpForce(playerConfig.jumpForce)
{
	MapObject::initObjectSprite(ResourceManager::get().getTexture(ResourceManager::TextureID::player), this->frameSize, playerConfig.frameScale);
}

void Player::jump()
{
	this->velocityY = -this->jumpForce;
}

void Player::update(float deltaTime)
{
	//calculationg speed
	this->velocityY += this->gravity * deltaTime;
	MapObject::setMoveDirection({ 0.f, this->velocityY >= 0.f ? 1.f : -1.f });
	MapObject::setObjectSpeed(std::abs(this->velocityY));

	MapObject::update(deltaTime);

	//calculating sprite frame
	this->animationTimer += deltaTime;
	
	if(this->velocityY >= 0.f)
		this->currentFrame = 0;
	else if (this->animationTimer >= this->animationSpeed)
	{
		this->animationTimer = 0.f;

		if (++this->currentFrame > 3)
			this->currentFrame = 0;
	}

	//calculating sprite angle
	float currentRotation = std::clamp(this->velocityY * 0.05f, -30.f, 90.f);
	MapObject::getObjectSprite().setRotation(sf::degrees(currentRotation));

}

void Player::draw(sf::RenderTarget& target)
{
	MapObject::setSpriteFrame({ currentFrame * this->frameSize.x, 0 }, this->frameSize);
	MapObject::draw(target);
}

void Player::onNotify(const Event& event)
{
	if (event.getEventType() == Event::EventType::pipeCollision || event.getEventType() == Event::EventType::screenCollision)
		this->setIsAlive(false);
}

