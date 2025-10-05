#pragma once

class ResourceManager
{
public:
	enum class TextureID { player, pipeMiddle, pipeEnd, cloud, baloon, score_changer };

private:
	//private variables
	std::unordered_map<TextureID, sf::Texture> textures;
	sf::Font gameFont;

	//private functions
	std::string convertToStringTextureID(TextureID id);
 
	void initTexture(TextureID id);
	void initFont();

	inline ResourceManager()
	{
		this->initTexture(TextureID::player);
		this->initTexture(TextureID::cloud);
		this->initTexture(TextureID::pipeMiddle);
		this->initTexture(TextureID::pipeEnd);
		this->initTexture(TextureID::baloon);
		this->initTexture(TextureID::score_changer);
		this->initFont();
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
	const sf::Font& getFont() const;

};


