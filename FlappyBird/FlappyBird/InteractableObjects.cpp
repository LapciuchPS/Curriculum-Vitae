#include "stdafx.h"
#include "InteractableObjects.h"

//Pipe class
PipeElement::PipeElement(const sf::Vector2f& pipePosition, objectID ID, const sf::Vector2f& pipeSize) :
	MapObject(ID, pipePosition, pipeSize)
{

	//for testing
	this->pipeElementSketch.setSize(pipeSize);
	this->pipeElementSketch.setFillColor(sf::Color::Yellow);
}

void PipeElement::update(const float& deltaTime)
{
	MapObject::moveObject({ -this->pipeSpeed*deltaTime, 0.f });

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

Pipe::Pipe(const sf::Vector2f& holePosition, int windowSizeY)
{
	std::unique_ptr<PipeElement> pipeElementPointer;
	float pipePositionY = holePosition.y;
	bool pipeBeginning = true;

	//upper pipe
	while (pipePositionY - 100 > -100)
	{
		pipePositionY -= 100;

		if (pipeBeginning)
		{
			pipeElementPointer = std::make_unique<PipeElement>(sf::Vector2f(holePosition.x, pipePositionY), objectID::pipeEndUp);
			pipeBeginning = false;
		}
		else pipeElementPointer = std::make_unique<PipeElement>(sf::Vector2f(holePosition.x, pipePositionY), objectID::pipeMiddle);
		

		this->pipe.push_back(std::move(pipeElementPointer));
	}

	pipePositionY = holePosition.y;
	pipeBeginning = true;

	//lower pipe
	while (pipePositionY + 100 < windowSizeY + 100)
	{
		pipePositionY += 100;

		if (pipeBeginning)
		{
			pipeElementPointer = std::make_unique<PipeElement>(sf::Vector2f(holePosition.x, pipePositionY), objectID::pipeEndDown);
			pipeBeginning = false;
		}
		else pipeElementPointer = std::make_unique<PipeElement>(sf::Vector2f(holePosition.x, pipePositionY), objectID::pipeMiddle);

		this->pipe.push_back(std::move(pipeElementPointer));
	}
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
