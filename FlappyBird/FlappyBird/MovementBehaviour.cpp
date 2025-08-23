#include "stdafx.h"
#include "MovementBehaviour.h"
#include "MapObject.h"

//Linear movement
void LinearMovement::move(MapObject& object, float deltaTime)
{
	float speed = object.getObjectSpeed();
	sf::Vector2f direction = object.getObjectDirection();

	sf::Vector2f move = speed * deltaTime * direction;

	object.moveObject(move);
}
