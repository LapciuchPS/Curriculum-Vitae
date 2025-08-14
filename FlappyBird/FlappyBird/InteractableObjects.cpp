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

//Pipe class
Pipe::Pipe(const sf::Vector2f& pipePosition, const sf::Vector2f& pipeSize) :
	InteractableObject(pipePosition, pipeSize, objectID::pipeMiddle)
{
}

void Pipe::update(const float deltaTime)
{
}
