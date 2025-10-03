#pragma once

struct ObjectConfiguration
{
	sf::Vector2f size;
	sf::Vector2f startingPoint;
	sf::Vector2f direction;
	float speed;
};

struct SpawnConfiguration
{
	float spawnLocationX;
	sf::Time spawnTime;
	sf::Time passedTime = sf::seconds(0);
};

struct PlayerConfiguration : public ObjectConfiguration
{
	sf::Vector2f frameScale;
	sf::Vector2i frameSize;
	float gravity;
	float jumpForce;
};

struct PipeConfiguration : public ObjectConfiguration, public SpawnConfiguration
{
	//gap
	float gapSizeY;
	sf::Vector2f gapPosition;
};

struct CloudConfiguration : public ObjectConfiguration, public SpawnConfiguration
{	
};

struct BonusConfiguration : public ObjectConfiguration, public SpawnConfiguration
{
	std::pair<int, int> extraPointsInterval;
	sf::Vector2i frameSize;
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

	//bonus
	BonusConfiguration bonusConfig;

	//score
	ScoreConfiguration scoreConfig;

	void initPlayerVariables();
	void initPipeVariables();
	void initCloudVariables();
	void initScoreVariables();
	void initBonusVariables();
	void initVariables();

	template<typename T>
	inline void addTimeToPassedTime(float deltaTime)
	{
		if constexpr (std::is_same_v<T, CloudConfiguration>)
			this->cloudConfig.passedTime += deltaTime;
		else if constexpr (std::is_same_v<T, BonusConfiguration>)
			this->bonusConfig.passedTime += deltaTime;
	}

public:
	GameConfiguration(const sf::Vector2u& windowSize = { 1920, 1080 });

	void updatePassedTime(float deltaTime);

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
	void setBonusPos(const sf::Vector2f& BonusPos);

	template<typename T>
	inline void setObjectSpawnTime(float time, std::string timeType)
	{
		if (timeType = "spawnTime")
		{
			if constexpr (std::is_same_v<T, CloudConfiguration>)
				this->cloudConfig.spawnTime = sf::seconds(time);
			else if constexpr (std::is_same_v<T, BonusConfiguration>)
				this->bonusConfig.spawnTime = sf::seconds(time);
		}
		else if (timeType = "passedTime")
		{
			if constexpr (std::is_same_v<T, CloudConfiguration>)
				this->cloudConfig.passedTime = 0;
			else if constexpr (std::is_same_v<T, BonusConfiguration>)
				this->bonusConfig.Time = 0;
		}
		
	}
};
