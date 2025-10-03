#include "stdafx.h"
#include "InteractableObjects.h"
#include "Configurations.h"
#include "ResourceManager.h"

using Texture = ResourceManager::TextureID;
using Type = Event::EventType;

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
	visitedByBird(false), isAlive(isAlive)
{
	float holePosY = pipeConfig.gapPosition.y;

	//to assure that the gap is fully on the screen
	if (holePosY + pipeConfig.gapSizeY > windowSizeY)
		holePosY -= pipeConfig.gapSizeY;

	this->gap = std::make_unique<MapObject>(sf::Vector2f(pipeConfig.gapPosition.x, holePosY), sf::Vector2f(pipeConfig.size.x , pipeConfig.gapSizeY), pipeConfig.direction, pipeConfig.speed, objectID::undefined, std::make_unique<LinearMovement>());

	objectID newID = objectID::undefined;
	float pipeHeight = pipeConfig.size.y;
	float pipePositionY = holePosY;
	bool pipeBeginning = true;

	//upper pipe
	while (pipePositionY - pipeHeight > -pipeHeight)
	{
		pipePositionY -= pipeHeight;
		pipeConfig.startingPoint.y = pipePositionY;

		if (pipeBeginning)
		{
			newID = objectID::pipeEndUp;
			pipeBeginning = false;
		}
		else newID = objectID::pipeMiddle;
		
		this->pipe.emplace_back(std::make_unique<MapObject>(pipeConfig.startingPoint, pipeConfig.size, pipeConfig.direction ,pipeConfig.speed, newID, std::make_unique<LinearMovement>()));
		this->initSprite(this->pipe.back()->getObjectID());
	}

	pipePositionY = holePosY + pipeConfig.gapSizeY;
	pipeBeginning = true;

	//lower pipe
	do
	{
		pipeConfig.startingPoint.y = pipePositionY;

		if (pipeBeginning)
		{
			newID = objectID::pipeEndDown;
			pipeBeginning = false;
		}
		else newID = objectID::pipeMiddle;


		this->pipe.emplace_back(std::make_unique<MapObject>(pipeConfig.startingPoint, pipeConfig.size, pipeConfig.direction, pipeConfig.speed, newID, std::make_unique<LinearMovement>()));
		this->initSprite(this->pipe.back()->getObjectID());

		pipePositionY += pipeHeight;
	} while (pipePositionY + pipeHeight < windowSizeY + pipeHeight);

}

void Pipe::update(float deltaTime)
{
	for (auto& element : this->pipe)
		element->update(deltaTime);

	this->gap->update(deltaTime);
}

void Pipe::draw(sf::RenderTarget& target)
{
	for (auto& element : this->pipe)
		element->draw(target);
}

void Pipe::onNotify(const Event& event)
{
	if (event.getFirst() == this)
	{
		if (event.getEventType() == Type::outOfScreen)
			this->isAlive = false;

		else if (event.getEventType() == Type::birdInGap)
			this->visitedByBird = true;

		//got a point so the variable must be turned into false to prevent player from getting extra points
		else if (event.getEventType() == Type::passedPipe)
			this->visitedByBird = false;
	}
}

const std::vector<std::unique_ptr<MapObject>>& Pipe::getPipeParts() const
{
	return this->pipe;
}

const sf::FloatRect& Pipe::getObjectHitbox() const
{
	return this->pipe.front()->getObjectHitbox();
}

MapObject* const Pipe::getGap() const
{
	return this->gap.get();
}


bool Pipe::getIsAlive() const
{
	return this->isAlive;
}

bool Pipe::getVisitedByBird() const
{
	return this->visitedByBird;
}

//Cloud
Cloud::Cloud(const CloudConfiguration& cloudConfig):
	MapObject(cloudConfig.startingPoint, cloudConfig.size, cloudConfig.direction, cloudConfig.speed, objectID::cloud, std::make_unique<LinearMovement>())
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
	if (event.getEventType() == Type::outOfScreen && event.getFirst() == this)
		this->setIsAlive(false);
}

//Bonus
Bonus::Bonus(const BonusConfiguration& bonusConfig, BonusType type, float windowSizeY) :
	MapObject(bonusConfig.startingPoint, bonusConfig.size, bonusConfig.direction, bonusConfig.speed, objectID::bonus, std::make_unique<LinearMovement>()),
	type(type), windowSizeY(windowSizeY)
{
	this->initObjectSprite(ResourceManager::get().getTexture(Texture::baloon), bonusConfig.frameSize, {1.25f, 1.25f});
	//this->initBonusSprite(this->type);
}

void Bonus::initBonusSprite(BonusType type)
{
	switch (type)
	{
	case BonusType::scoreChanger: break;
	case BonusType::shield: break;
	case BonusType::gravity: break;

	default:;
	}
}

void Bonus::update(float deltaTime)
{
	if (MapObject::getObjectPosition().y <= windowSizeY * 0.1)
		MapObject::setMoveDirection({ -1.f, 1.f });
	else if (MapObject::getObjectPosition().y >= windowSizeY * 0.9 - MapObject::getObjectSize().y)
		MapObject::setMoveDirection({ -1.f, -1.f });

	MapObject::update(deltaTime);
	//this->bonusSprite->setPosition(MapObject::getObjectPosition());
}

void Bonus::draw(sf::RenderTarget& target)
{
	MapObject::draw(target);
	//target.draw(this->bonusSprite.value());
}

void Bonus::onNotify(const Event& event)
{
	if (event.getFirst() == this)
		this->setIsAlive(false);
}

Bonus::BonusType Bonus::getBonusType() const
{
	return this->type;
}

//ScoreChanger
ScoreChanger::ScoreChanger(const BonusConfiguration& bonusConfig, float windowSizeY, int extraPoints):
	Bonus(bonusConfig, BonusType::scoreChanger, windowSizeY),
	extraPoints(extraPoints)
{

}

int ScoreChanger::getExtraPoints() const
{
	return this->extraPoints;
}
