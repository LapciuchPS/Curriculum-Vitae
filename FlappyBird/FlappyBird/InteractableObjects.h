#pragma once
#include "MapObject.h"

struct PipeConfiguration;
struct CloudConfiguration;

//Pipe
class Pipe : public SceneInterface
{
private:
	std::vector<std::unique_ptr<MapObject>> pipe;

public:
	Pipe(PipeConfiguration pipeConfig, int windowSizeY);

	void update(float deltaTime);
	void draw(sf::RenderTarget& target);
};

//Cloud
class Cloud : public MapObject
{
private:

public:
	Cloud(const CloudConfiguration& cloudConfig);

	void update(float deltaTime);
	void draw(sf::RenderTarget& target);
};
