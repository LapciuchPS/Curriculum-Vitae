#pragma once
#include "MapObject.h"

class Player: public MapObject
{
private:
	//private variables
	std::optional<sf::FloatRect> playerShape;
	std::optional<sf::Sprite> playerSprite;

	float velocityY;
	bool canJump;

	//for testing
	sf::RectangleShape playerSketch;

	//private functions
	void initPlayerVariables();

public:
	//public functions
	Player(sf::Vector2f playerPosition, sf::Vector2f playerSize);

	void jump();
};

