#pragma once
#include "MapObject.h"

struct PipeConfiguration;
struct CloudConfiguration;

//Pipe
class LinearMover : public MapObject
{
private:
	float linearMoverSpeed;

	//for testing
	sf::RectangleShape linearMoverSketch;

public:
	LinearMover(const sf::Vector2f& objectPosition, const sf::Vector2f& objectSize, float speed, objectID ID = objectID::pipeMiddle);

	void update(const float& deltaTime) override;
	void draw(sf::RenderTarget& target) override;

	//for testing
	void drawLinearMover(sf::RenderTarget& target);
};

class Pipe : public SceneInterface
{
private:
	std::vector<LinearMover> pipe;

public:
	Pipe(PipeConfiguration pipeConfig, int windowSizeY);

	void update(const float& deltaTime) override;
	void draw(sf::RenderTarget& target) override;
};

//Cloud
class Cloud : public LinearMover
{
private:

public:
	Cloud(const CloudConfiguration& cloudConfig, objectID ID = objectID::cloud);

	void update(const float& deltaTime);
	void draw(sf::RenderTarget& target);
};