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
	float passedTime = 0.f;
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
};

struct CloudConfiguration : public ObjectConfiguration, public SpawnConfiguration
{	
};

struct BonusConfiguration : public ObjectConfiguration, public SpawnConfiguration
{
	std::pair<int, int> extraPointsInterval;
	sf::Vector2i frameSize;
	sf::Vector2f frameScale;
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
		if constexpr (std::is_base_of_v<SpawnConfiguration, T>)
			const_cast<T&>(getConfiguration<T>()).passedTime += deltaTime;
	}

public:
	enum class TimeType {passedTime, spawnTime};

	GameConfiguration(const sf::Vector2u& windowSize = { 1920, 1080 });

	void updatePassedTime(float deltaTime);

	template<typename T>
	inline bool canBeSpawned()
	{
		if constexpr (std::is_base_of_v<SpawnConfiguration, T>)
		{
			T& config = const_cast<T&>(this->getConfiguration<T>());
		
			return config.passedTime >= config.spawnTime;
		}
		
		return false;
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
		T& config = const_cast<T&>(this->getConfiguration<T>());

		config.startingPoint = newPos;
	}

	template<typename T>
	inline void setObjectTime(float time, TimeType type)
	{
		if constexpr (std::is_base_of_v<SpawnConfiguration, T>)
		{
			T& config = const_cast<T&>(this->getConfiguration<T>());

			if (type == TimeType::spawnTime)
			{
				config.spawnTime = time;
			}
			else if (type == TimeType::passedTime)
			{
				config.passedTime = time;
			}
		}
	}
};
