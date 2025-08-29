#pragma once
#include "MapObject.h"
#include "EventHandler.h"

struct PipeConfiguration;
struct CloudConfiguration;

//Pipe
class Pipe : public SceneInterface, public EventObserver
{
private:
	std::vector<std::unique_ptr<MapObject>> pipe;
	bool isAlive;

public:
	Pipe(PipeConfiguration pipeConfig, int windowSizeY, bool isAlive = true);
	~Pipe() = default;

	void update(float deltaTime);
	void draw(sf::RenderTarget& target);

	void onNotify(const Event& event) override;

	//getters
	const std::vector<std::unique_ptr<MapObject>>& getPipeElements() const;
	bool isOnScreen() const;

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
