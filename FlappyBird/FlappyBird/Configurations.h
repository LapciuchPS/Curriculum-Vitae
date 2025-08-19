#pragma once

struct PlayerConfiguration
{
	sf::Vector2f size;
	sf::Vector2f startingPoint;
	float jumpingSpeed;
	float fallingSpeed;
	float jumpDistance;
};

struct PipeConfiguration
{
	sf::Vector2f pipeSize;
	sf::Vector2f pipeStartingPoint;
	float gapSizeY;
	sf::Vector2f gapPosition;
	float speed;
};

struct CloudConfiguration
{
	sf::Vector2f cloudSize;
	sf::Vector2f cloudStartingPoint;
	float speed;
};

class GameConfiguration
{
private:
	//window
	sf::Vector2u gameWindowSize;

	//player
	PlayerConfiguration playerConfig;

	//pipe element
	PipeConfiguration pipeConfig;

	//cloud 
	CloudConfiguration cloudConfig;

	void initPlayerVariables();
	void initPipeVariables();
	void initCloudVariables();
	void initVariables();

public:
	GameConfiguration(const sf::Vector2u& windowSize = { 1920, 1080 });

	//getters
	const sf::Vector2u& getGameWindowSize() const;
	const PlayerConfiguration& getPlayerConfig() const;
	const PipeConfiguration& getPipeConfig() const;
	const CloudConfiguration& getCloudConfig() const;

	//setters
	void setPipeGapPos(const sf::Vector2f& gapPos);
	void setCloudPos(const sf::Vector2f& cloudPos);
};

