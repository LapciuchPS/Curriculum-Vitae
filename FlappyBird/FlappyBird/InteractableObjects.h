#pragma once
#include "MapObject.h"

//Pipe
class PipeElement : public MapObject
{
private:
	float pipeSpeed = 200.f;

	//for testing
	sf::RectangleShape pipeElementSketch;

public:
	PipeElement(const sf::Vector2f& pipePosition, objectID ID = objectID::pipeMiddle, const sf::Vector2f& pipeSize = { 100.f, 100.f });

	void update(const float& deltaTime) override;
	void draw(sf::RenderTarget& target) override;

	//for testing
	void drawPipe(sf::RenderTarget& target);
};

class Pipe : public SceneInterface
{
private:
	std::vector<std::unique_ptr<PipeElement>> pipe;

public:
	Pipe(const sf::Vector2f& holePosition, int windowSizeY);

	void update(const float& deltaTime) override;
	void draw(sf::RenderTarget& target) override;
	//const objectID& getObjectID() const override;
};