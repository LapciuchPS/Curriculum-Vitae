#pragma once

struct PlayerConfiguration
{
	sf::Vector2f size;
	sf::Vector2f startingPoint;
	sf::Vector2f direction;
	sf::Vector2f frameScale;
	sf::Vector2i frameSize;
	float velocityY;
	float gravity;
	float jumpForce;
};

struct PipeConfiguration
{
	//pipe
	sf::Vector2f pipeSize;
	sf::Vector2f pipeStartingPoint;
	sf::Vector2f direction;
	float speed;

	//gap
	float gapSizeY;
	sf::Vector2f gapPosition;
	
};

struct CloudConfiguration
{
	sf::Vector2f cloudSize;
	sf::Vector2f cloudStartingPoint;
	sf::Vector2f direction;
	float speed;
};

struct ScoreConfiguration
{
	unsigned int characterSize;
	sf::Color outlineColor;
	sf::Vector2f position;
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

	//score
	ScoreConfiguration scoreConfig;

	void initPlayerVariables();
	void initPipeVariables();
	void initCloudVariables();
	void initScoreVariables();
	void initVariables();

public:
	GameConfiguration(const sf::Vector2u& windowSize = { 1920, 1080 });

	//getters
	const sf::Vector2u& getGameWindowSize() const;
	const PlayerConfiguration& getPlayerConfig() const;
	const PipeConfiguration& getPipeConfig() const;
	const CloudConfiguration& getCloudConfig() const;
	const ScoreConfiguration& getScoreConfig() const;

	//setters
	void setPipeGapPos(const sf::Vector2f& gapPos);
	void setCloudPos(const sf::Vector2f& cloudPos);
};

