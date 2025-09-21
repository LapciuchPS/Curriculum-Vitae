#pragma once

class ResourceManager
{
public:
	enum class TextureID { player, pipeMiddle, pipeEnd, cloud };

private:
	//private variables
	std::unordered_map<TextureID, sf::Texture> textures;
	
	//private functions
	std::string convertToStringTextureID(TextureID id);
 
	void initTexture(TextureID id);

	inline ResourceManager()
	{
		this->initTexture(TextureID::player);
		this->initTexture(TextureID::cloud);
		this->initTexture(TextureID::pipeMiddle);
		this->initTexture(TextureID::pipeEnd);
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


