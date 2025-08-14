#pragma once
#include "MapObject.h"

class Player: public MapObject
{
private:
	//private variables

	float jumpingSpeed;
	float fallingSpeed;
	float jumpDistanceLeft;

	//for testing
	sf::RectangleShape playerSketch;

public:
	//public functions
	Player(const sf::Vector2f& playerPosition, const sf::Vector2f& playerSize = {50.f,50.f});

	void jump();
	void update(const float deltaTime) override;
	void draw(sf::RenderTarget& target, const sf::Sprite& objectSprite) const;

	//for testing
	void drawPlayer(sf::RenderTarget& target);
};

