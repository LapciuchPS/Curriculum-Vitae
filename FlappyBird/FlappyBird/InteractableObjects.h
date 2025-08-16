#pragma once
#include "MapObject.h"

class Pipe : public MapObject
{
private:
	float pipeSpeed = 200.f;

	//for testing
	sf::RectangleShape pipeSketch;

public:
	Pipe(const sf::Vector2f& pipePosition, const sf::Vector2f& pipeSize = { 100.f, 100.f });

	void update(const float& deltaTime) override;
	void draw(sf::RenderTarget& target) override;

	//for testing
	void drawPipe(sf::RenderTarget& target);
};

