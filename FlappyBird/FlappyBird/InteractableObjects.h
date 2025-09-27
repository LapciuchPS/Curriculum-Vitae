#pragma once
#include "MapObject.h"
#include "EventHandler.h"

struct PipeConfiguration;
struct CloudConfiguration;
struct BonusConfiguration;

//Pipe
class Pipe : public SceneInterface, public EventObserver
{
private:
	std::vector<std::unique_ptr<MapObject>> pipe;
	std::unique_ptr<MapObject> gap;
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
	MapObject* const getGap() const;
	bool getIsAlive() const override;
	bool getVisitedByBird() const;

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

//Bonus
class Bonus : public MapObject, public EventObserver
{
protected:
	//protected variables
	enum class BonusType {scoreChanger, shield, gravity};
	BonusType type;

private:
	std::optional<sf::Sprite> bonusSprite;

public:
	Bonus(BonusConfiguration& bonusConfig, BonusType type);

	void initBonusSprite(BonusType type);

	void update(float deltaTime);
	void draw(sf::RenderTarget& target);
};

class ScoreChanger : public Bonus
{
private:
	int extraPoints;
public:
	ScoreChanger(BonusConfiguration& bonusConfig, int extraPoints);

	void onNotify(const Event& event) override;
};