#include "stdafx.h"
#include "InteractableObjects.h"
#include "Configurations.h"

//Pipe class
LinearMover::LinearMover(const sf::Vector2f& objectPosition, const sf::Vector2f& objectSize, float speed, objectID ID) :
	MapObject(ID, objectPosition, objectSize),
	linearMoverSpeed(speed)
{
	//for testing
	this->linearMoverSketch.setSize(objectSize);
	this->linearMoverSketch.setFillColor(sf::Color::Yellow);
	this->linearMoverSketch.setOutlineThickness(2);
	this->linearMoverSketch.setOutlineColor(sf::Color::White);
}

void LinearMover::update(const float& deltaTime)
{
	MapObject::moveObject({ - this->linearMoverSpeed * deltaTime, 0.f });

	//for testing
	this->linearMoverSketch.setPosition(MapObject::getObjectPosition());
}

void LinearMover::draw(sf::RenderTarget& target)
{
	this->drawLinearMover(target);
}

//for testing
void LinearMover::drawLinearMover(sf::RenderTarget& target)
{
	target.draw(this->linearMoverSketch);
}

Pipe::Pipe(PipeConfiguration pipeConfig, int windowSizeY)
{
	float holePosY = pipeConfig.gapPosition.y;

	//to assure that the gap is fully on the screen
	if (holePosY - pipeConfig.gapSizeY < 0)
		holePosY += pipeConfig.gapSizeY;
	else if (holePosY + pipeConfig.gapSizeY > windowSizeY)
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
		
		this->pipe.emplace_back(pipeConfig.pipeStartingPoint, pipeConfig.pipeSize, pipeConfig.speed, newID);
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


		this->pipe.emplace_back(pipeConfig.pipeStartingPoint, pipeConfig.pipeSize, pipeConfig.speed, newID);

		pipePositionY += pipeHeight;
	} while (pipePositionY + pipeHeight < windowSizeY + pipeHeight);

}

void Pipe::update(const float& deltaTime)
{
	for (auto& element : this->pipe)
		element.update(deltaTime);
}

void Pipe::draw(sf::RenderTarget& target)
{
	for (auto& element : this->pipe)
		element.draw(target);
}

//Cloud
Cloud::Cloud(const CloudConfiguration& cloudConfig, objectID ID) :
	LinearMover(cloudConfig.cloudStartingPoint, cloudConfig.cloudSize, cloudConfig.speed, ID)
{
}

void Cloud::update(const float& deltaTime)
{
	LinearMover::update(deltaTime);
}

void Cloud::draw(sf::RenderTarget& target)
{
	LinearMover::draw(target);
}
