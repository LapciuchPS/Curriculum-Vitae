#pragma once
#include "MapObject.h"

class InteractableObject : public MapObject
{
protected:
	enum class objectID { pipeEnd = 1, pipeMiddle, enemyBird, cloud, wind };

private:
	bool isOnScreen;
	objectID ID;

public:
	InteractableObject(const sf::Vector2f& objectPosition, const sf::Vector2f& objectSize, const objectID ID, const bool isOnScreen = false);

	bool checkCollision(const sf::FloatRect& otherHitbox);
};

class Pipe : public InteractableObject
{
private:

public:
	Pipe(const sf::Vector2f& pipePosition, const sf::Vector2f& pipeSize = { 100.f, 100.f });

	void update(const float deltaTime) override;
};

