#pragma once

class ResourceManager
{
public:
	enum class TextureID { player, pipeMiddle, pipeEnd, cloud };

private:
	//private variables
	std::unordered_map<TextureID, sf::Texture> textures;
	
	//private functions
	void initPlayerSpriteSheet();
	void initCloudTexture();
	void initPipeMiddleTexture();
	void initPipeEndTexture();

	inline ResourceManager()
	{
		this->initPlayerSpriteSheet();
		this->initCloudTexture();
		this->initPipeMiddleTexture();
		this->initPipeEndTexture();
	}
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

public:
	//public functions
	inline static ResourceManager& get()
	{
		static ResourceManager resources;
		return resources;
	}

	//getters
	const sf::Texture& getTexture(TextureID id) const;

};

