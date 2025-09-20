#pragma once
#include "MapObject.h"
#include "EventHandler.h"

struct PlayerConfiguration;

class Player: public MapObject, public EventObserver
{
private:
	//private variables
	float velocityY;
	float gravity;
	float jumpForce;

	float animationTimer = 0.f;
	float animationSpeed = 0.15f;
	int currentFrame = 0;
	sf::Vector2i frameSize;

public:
	//public functions
	Player(const PlayerConfiguration& playerConfig);

	void jump();
	void update(float deltaTime) override;
	void draw(sf::RenderTarget& target);

	void onNotify(const Event& event) override;
};

