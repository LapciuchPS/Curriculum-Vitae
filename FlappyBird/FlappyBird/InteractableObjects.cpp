#include "stdafx.h"
#include "InteractableObjects.h"
#include "Configurations.h"
#include "ResourceManager.h"

using Texture = ResourceManager::TextureID;

//Pipe
void Pipe::initSprite(objectID id)
{
	switch (id)
	{
	case objectID::pipeMiddle: this->pipe.back()->initObjectSprite(ResourceManager::get().getTexture(Texture::pipeMiddle)); break;

	case objectID::pipeEndDown: this->pipe.back()->initObjectSprite(ResourceManager::get().getTexture(Texture::pipeEnd)); break;

	case objectID::pipeEndUp:
		this->pipe.back()->initObjectSprite(ResourceManager::get().getTexture(Texture::pipeEnd));
		this->pipe.back()->getObjectSprite().rotate(sf::degrees(180.f));
		break;

	default:;

	}
}

Pipe::Pipe(PipeConfiguration pipeConfig, int windowSizeY, bool isAlive):
	isAlive(isAlive)
{
	float holePosY = pipeConfig.gapPosition.y;

	//to assure that the gap is fully on the screen
	if (holePosY + pipeConfig.gapSizeY > windowSizeY)
		holePosY -= pipeConfig.gapSizeY;

	objectID newID = objectID::undefined;
	float pipeHeight = pipeConfig.pipeSize.y;
	float pipePositionY = holePosY;
	bool pipeBeginning = true;

	//upper pipe
	while (pipePositionY - pipeHeight > -pipeHeight)
	{
		pipePositionY -= pipeHeight;
		pipeConfig.pipeStartingPoint.y = pipePositionY;

		if (pipeBeginning)
		{
			newID = objectID::pipeEndUp;
			pipeBeginning = false;
		}
		else newID = objectID::pipeMiddle;
		
		this->pipe.emplace_back(std::make_unique<MapObject>(pipeConfig.pipeStartingPoint, pipeConfig.pipeSize, pipeConfig.direction ,pipeConfig.speed, newID, std::make_unique<LinearMovement>()));
		this->initSprite(this->pipe.back()->getObjectID());
	}

	pipePositionY = holePosY + pipeConfig.gapSizeY;
	pipeBeginning = true;

	//lower pipe
	do
	{
		pipeConfig.pipeStartingPoint.y = pipePositionY;

		if (pipeBeginning)
		{
			newID = objectID::pipeEndDown;
			pipeBeginning = false;
		}
		else newID = objectID::pipeMiddle;


		this->pipe.emplace_back(std::make_unique<MapObject>(pipeConfig.pipeStartingPoint, pipeConfig.pipeSize, pipeConfig.direction, pipeConfig.speed, newID, std::make_unique<LinearMovement>()));
		this->initSprite(this->pipe.back()->getObjectID());

		pipePositionY += pipeHeight;
	} while (pipePositionY + pipeHeight < windowSizeY + pipeHeight);

}

void Pipe::update(float deltaTime)
{
	for (auto& element : this->pipe)
		element->update(deltaTime);
}

void Pipe::draw(sf::RenderTarget& target)
{
	for (auto& element : this->pipe)
		element->draw(target);
}

void Pipe::onNotify(const Event& event)
{
	if (event.getEventType() == Event::EventType::outOfScreen && event.getFirst() == this)
		this->isAlive = false;
}

const std::vector<std::unique_ptr<MapObject>>& Pipe::getPipeParts() const
{
	return this->pipe;
}

const sf::FloatRect& Pipe::getObjectHitbox() const
{
	return this->pipe.front()->getObjectHitbox();
}

bool Pipe::getIsOnScreen() const
{
	return this->pipe.front()->getIsOnScreen();
}

bool Pipe::getIsAlive() const
{
	return this->isAlive;
}

//Cloud
Cloud::Cloud(const CloudConfiguration& cloudConfig):
	MapObject(cloudConfig.cloudStartingPoint, cloudConfig.cloudSize, cloudConfig.direction, cloudConfig.speed, objectID::cloud, std::make_unique<LinearMovement>())
{
	this->initObjectSprite(ResourceManager::get().getTexture(Texture::cloud));
}

void Cloud::update(float deltaTime)
{
	MapObject::update(deltaTime);
}

void Cloud::draw(sf::RenderTarget& target)
{
	MapObject::draw(target);
}

void Cloud::onNotify(const Event& event)
{
	if (event.getEventType() == Event::EventType::outOfScreen && event.getFirst() == this)
		this->setIsAlive(false);
}

