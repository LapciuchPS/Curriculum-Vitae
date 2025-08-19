#pragma once
#include "MapObject.h"

struct PipeConfiguration;

//Pipe
class PipeElement : public MapObject
{
private:
	float pipeElementSpeed;

	//for testing
	sf::RectangleShape pipeElementSketch;

public:
	PipeElement(const PipeConfiguration& pipeConfig, objectID ID = objectID::pipeMiddle);

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
	Pipe(PipeConfiguration pipeConfig, int windowSizeY);

	void update(const float& deltaTime) override;
	void draw(sf::RenderTarget& target) override;
	//const objectID& getObjectID() const override;
};
