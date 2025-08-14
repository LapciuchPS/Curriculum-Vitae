#include "stdafx.h"
#include "InteractableObjects.h"

//InteractableObject class
InteractableObject::InteractableObject(const sf::Vector2f& objectPosition, const sf::Vector2f& objectSize, const objectID ID, const bool isOnScreen) :
	MapObject(objectPosition, objectSize), isOnScreen(isOnScreen), ID(ID)
{
}

bool InteractableObject::checkCollision(const sf::FloatRect& otherHitbox)
{
		return MapObject::getObjectHitbox().findIntersection(otherHitbox).has_value();
}

void InteractableObject::draw(sf::RenderTarget& target, const sf::Sprite& objectSprite) const
{
	if (this->isOnScreen)
		target.draw(objectSprite);
}

//Pipe class
Pipe::Pipe(const sf::Vector2f& pipePosition, const sf::Vector2f& pipeSize, const objectID& ID) :
	InteractableObject(pipePosition, pipeSize, ID)
{
}

void Pipe::update(const float deltaTime)
{
	
}
