#pragma once
#include "MapObject.h"

struct PlayerConfiguration;

class Player: public MapObject
{
private:
	//private variables
	float jumpingSpeed;
	float fallingSpeed;
	float jumpDistance;
	float jumpDistanceLeft;

	//for testing
	sf::RectangleShape playerSketch;

public:
	//public functions
	Player(const PlayerConfiguration& playerCFG);

	void jump();
	void update(const float& deltaTime) override;
	void draw(sf::RenderTarget& target);

	//for testing
	void drawPlayer(sf::RenderTarget& target);
};

