#pragma once
#include "MapObject.h"

class Player: public MapObject
{
private:
	//private variables
	sf::FloatRect playerShape;
	sf::Sprite playerSprite;

	float jumpingSpeed;
	float fallingSpeed;
	float jumpDistanceLeft;

	//for testing
	sf::RectangleShape playerSketch;

public:
	//public functions
	Player(sf::Vector2f playerPosition, sf::Vector2f playerSize = { 50,50 });

	void jump();
	void updatePlayer(const float deltaTime);
	void drawPlayer(sf::RenderTarget& target);
};

