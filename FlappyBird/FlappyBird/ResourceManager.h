#pragma once

class ResourceManager
{
private:
	//private variables
	sf::Texture playerSpriteSheet;
	

	//private functions
	void initPlayerSpriteSheet();

	ResourceManager()
	{
		this->initPlayerSpriteSheet();
	}

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	
public:
	//public functions
	static ResourceManager& getResources()
	{
		static ResourceManager resources;
		return resources;
	}

	const sf::Texture& getPlayerSpriteSheet() const;
};

