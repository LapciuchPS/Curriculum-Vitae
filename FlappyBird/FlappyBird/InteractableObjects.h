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
	std::optional<MapObject> gap;
	bool isAlive;
	bool visitedByBird;

	void initSprite(objectID id);

public:
	Pipe(PipeConfiguration pipeConfig, int windowSizeY, bool isAlive = true);

	void update(float deltaTime);
	void draw(sf::RenderTarget& target);

	void onNotify(const Event& event) override;

	//getters
	const std::vector<std::unique_ptr<MapObject>>& getPipeParts() const;
	const sf::FloatRect& getObjectHitbox() const;
	bool getIsOnScreen() const;
	bool getIsAlive() const override;

};

//Cloud
class Cloud : public MapObject, public EventObserver
{
private:

public:
	Cloud(const CloudConfiguration& cloudConfig);

	void update(float deltaTime);
	void draw(sf::RenderTarget& target);

	void onNotify(const Event& event) override;
};
