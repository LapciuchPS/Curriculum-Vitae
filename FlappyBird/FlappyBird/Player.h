#pragma once
#include "MapObject.h"
#include "EventHandler.h"

struct PlayerConfiguration;

class Player: public MapObject, public EventObserver
{
private:
	//private variables
	float fallingSpeed;
	float jumpDistance;
	float jumpDistanceLeft;

public:
	//public functions
	Player(const PlayerConfiguration& playerConfig);

	void jump();
	void update(float deltaTime) override;
	void draw(sf::RenderTarget& target);

	void onNotify(const Event& event) override;
};

