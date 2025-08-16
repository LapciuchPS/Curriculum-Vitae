#include "stdafx.h"
#include "InteractableObjects.h"

//Pipe class
Pipe::Pipe(const sf::Vector2f& pipePosition, const sf::Vector2f& pipeSize) :
	MapObject(objectID::pipeMiddle, pipePosition, pipeSize)
{

	//for testing
	this->pipeSketch.setPosition(pipePosition);
	this->pipeSketch.setSize(pipeSize);
	this->pipeSketch.setFillColor(sf::Color::Yellow);
}

void Pipe::update(const float& deltaTime)
{
	MapObject::moveObject({ -this->pipeSpeed*deltaTime, 0.f });

	//for testing
	this->pipeSketch.setPosition(MapObject::getObjectPosition());
}

void Pipe::draw(sf::RenderTarget& target)
{
	this->drawPipe(target);
}

//for testing
void Pipe::drawPipe(sf::RenderTarget& target)
{
	target.draw(this->pipeSketch);
}
