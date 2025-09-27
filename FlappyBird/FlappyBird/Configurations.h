#pragma once

struct ObjectConfiguration
{
	sf::Vector2f size;
	sf::Vector2f startingPoint;
	sf::Vector2f direction;
	float speed;
};

struct PlayerConfiguration : public ObjectConfiguration
{
	sf::Vector2f frameScale;
	sf::Vector2i frameSize;
	float gravity;
	float jumpForce;
};

struct PipeConfiguration : public ObjectConfiguration
{
	//gap
	float gapSizeY;
	sf::Vector2f gapPosition;
};

struct CloudConfiguration : public ObjectConfiguration
{	
};

struct BonusConfiguration : public ObjectConfiguration
{
	std::pair<int, int> extraPointsInterval;
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

	//bonus
	BonusConfiguration bonusConfig;

	void initPlayerVariables();
	void initPipeVariables();
	void initCloudVariables();
	void initScoreVariables();
	void initBonusVariables();
	void initVariables();

public:
	GameConfiguration(const sf::Vector2u& windowSize = { 1920, 1080 });

	//getters
	const sf::Vector2u& getGameWindowSize() const;

	template<typename T>
	inline const T& getConfiguration() const
	{
		if constexpr (std::is_same_v<T, PlayerConfiguration>)
			return this->playerConfig;
		else if constexpr (std::is_same_v<T, PipeConfiguration>)
			return this->pipeConfig;
		else if constexpr (std::is_same_v<T, CloudConfiguration>)
			return this->cloudConfig;
		else if constexpr (std::is_same_v<T, BonusConfiguration>)
			return this->bonusConfig;
		else if constexpr (std::is_same_v<T, ScoreConfiguration>)
			return  this->scoreConfig;
	}

	//setters
	void setPipeGapPos(const sf::Vector2f& gapPos);
	void setCloudPos(const sf::Vector2f& cloudPos);
};
