#pragma once
#include "MapObject.h"

class InteractableObject : public MapObject
{
protected:
	enum class objectID { pipeEnd = 1, pipeMiddle, enemyBird, cloud, wind };

private:
	bool isOnScreen;
	const objectID ID;

public:
	InteractableObject(const sf::Vector2f& objectPosition, const sf::Vector2f& objectSize, const objectID ID, const bool isOnScreen = false);

	bool checkCollision(const sf::FloatRect& otherHitbox);

	void draw(sf::RenderTarget& target, const sf::Sprite& objectSprite) const override;
};

class Pipe : public InteractableObject
{
private:
	//for testing
	sf::RectangleShape pipeSketch;

public:
	Pipe(const sf::Vector2f& pipePosition, const sf::Vector2f& pipeSize = { 100.f, 100.f }, const objectID& ID = objectID::pipeMiddle);

	void update(const float deltaTime) override;

	//for testing
	void drawPipe(sf::RenderTarget& target);
};

