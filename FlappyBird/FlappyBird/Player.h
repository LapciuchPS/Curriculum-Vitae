#pragma once
#include "MapObject.h"

struct PlayerConfiguration;

class Player: public MapObject
{
private:
	//private variables
	float fallingSpeed;
	float jumpDistance;
	float jumpDistanceLeft;

	//for testing
	sf::RectangleShape playerSketch;

public:
	//public functions
	Player(const PlayerConfiguration& playerConfig);

	void jump();
	void update(float deltaTime) override;
	void draw(sf::RenderTarget& target);

	//for testing
	void drawPlayer(sf::RenderTarget& target);
};

