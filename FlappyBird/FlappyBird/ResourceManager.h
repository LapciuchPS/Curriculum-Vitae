#pragma once

class ResourceManager
{
private:
	//private variables
	sf::Texture playerSpriteSheet;
	

	//private functions
	void initPlayerSpriteSheet();

	inline ResourceManager()
	{
		this->initPlayerSpriteSheet();
	}

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	
public:
	//public functions
	inline static ResourceManager& getResources()
	{
		static ResourceManager resources;
		return resources;
	}

	const sf::Texture& getPlayerSpriteSheet() const;
};

