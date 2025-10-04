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
	float spawnTime;
	float passedTime = 0;
	std::pair<int, int > spawnTimeInterval;
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
	float spawnLocationX;

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

	template<typename T>
	inline bool canBeSpawned()
	{
		float passedTime;
		float spawnTime;

		if constexpr (std::is_same_v<T, CloudConfiguration>)
		{
			passedTime = this->cloudConfig.passedTime;
			spawnTime = this->cloudConfig.spawnTime;
		}
		else if constexpr (std::is_same_v<T, BonusConfiguration>)
		{
			passedTime = this->bonusConfig.passedTime;
			spawnTime = this->bonusConfig.spawnTime;
		}

		return passedTime >= spawnTime;
	}

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
	template<typename T>
	inline void setObjectPos(const sf::Vector2f& newPos)
	{
		if constexpr (std::is_same_v<T, PipeConfiguration>)
			this->pipeConfig.gapPosition = newPos;
		else if constexpr (std::is_same_v<T, CloudConfiguration>)
			this->cloudConfig.startingPoint = newPos;
		else if constexpr (std::is_same_v<T, BonusConfiguration>)
			this->bonusConfig.startingPoint = newPos;
	}

	template<typename T>
	inline void setObjectTime(float time, std::string timeName)
	{
		if (timeName == "spawnTime")
		{
			if constexpr (std::is_same_v<T, CloudConfiguration>)
				this->cloudConfig.spawnTime = time;
			else if constexpr (std::is_same_v<T, BonusConfiguration>)
				this->bonusConfig.spawnTime = time;
		}
		else if (timeName == "passedTime")
		{
			if constexpr (std::is_same_v<T, CloudConfiguration>)
				this->cloudConfig.passedTime = 0;
			else if constexpr (std::is_same_v<T, BonusConfiguration>)
				this->bonusConfig.passedTime = 0;
		}
	}
};
