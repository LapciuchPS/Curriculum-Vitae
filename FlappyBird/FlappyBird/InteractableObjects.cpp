#include "stdafx.h"
#include "InteractableObjects.h"
#include "Configurations.h"

//Pipe class
PipeElement::PipeElement(const PipeConfiguration& pipeConfig, objectID ID) :
	MapObject(ID, pipeConfig.pipeStartingPoint, pipeConfig.pipeSize),
	pipeElementSpeed(pipeConfig.speed)
{
	//for testing
	this->pipeElementSketch.setSize(pipeConfig.pipeSize);
	this->pipeElementSketch.setFillColor(sf::Color::Yellow);
	this->pipeElementSketch.setOutlineThickness(2);
	this->pipeElementSketch.setOutlineColor(sf::Color::White);
}

void PipeElement::update(const float& deltaTime)
{
	MapObject::moveObject({ -this->pipeElementSpeed *deltaTime, 0.f });

	//for testing
	this->pipeElementSketch.setPosition(MapObject::getObjectPosition());
}

void PipeElement::draw(sf::RenderTarget& target)
{
	this->drawPipe(target);
}

//for testing
void PipeElement::drawPipe(sf::RenderTarget& target)
{
	target.draw(this->pipeElementSketch);
}

Pipe::Pipe(PipeConfiguration pipeConfig, int windowSizeY)
{
	float holePosY = pipeConfig.gapPosition.y;

	//to assure that the gap is fully on the screen
	if (holePosY - pipeConfig.gapSizeY < 0)
		holePosY += pipeConfig.gapSizeY;
	else if (holePosY + pipeConfig.gapSizeY > windowSizeY)
		holePosY -= pipeConfig.gapSizeY;

	std::unique_ptr<PipeElement> pipeElementPointer;
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
			pipeElementPointer = std::make_unique<PipeElement>(pipeConfig, objectID::pipeEndUp);
			pipeBeginning = false;
		}
		else pipeElementPointer = std::make_unique<PipeElement>(pipeConfig, objectID::pipeMiddle);
		

		this->pipe.push_back(std::move(pipeElementPointer));
	}

	pipePositionY = holePosY + pipeConfig.gapSizeY;
	pipeBeginning = true;

	//lower pipe
	do
	{
		pipeConfig.pipeStartingPoint.y = pipePositionY;

		if (pipeBeginning)
		{
			pipeElementPointer = std::make_unique<PipeElement>(pipeConfig, objectID::pipeEndDown);
			pipeBeginning = false;
		}
		else pipeElementPointer = std::make_unique<PipeElement>(pipeConfig, objectID::pipeMiddle);

		this->pipe.push_back(std::move(pipeElementPointer));

		pipePositionY += pipeHeight;
	} while (pipePositionY + pipeHeight < windowSizeY + pipeHeight);

}

void Pipe::update(const float& deltaTime)
{
	for (const auto& element : this->pipe)
		element->update(deltaTime);
}

void Pipe::draw(sf::RenderTarget& target)
{
	for (auto& element : this->pipe)
		element->draw(target);
}
