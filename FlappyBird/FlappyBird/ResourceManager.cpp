#include "stdafx.h"
#include "ResourceManager.h"


std::string ResourceManager::convertToStringTextureID(TextureID id)
{
	switch (id)
	{
		case TextureID::player: return "bird_sprite_sheet.png"; break;
		case TextureID::pipeMiddle: return "pipe_middle.png"; break;
		case TextureID::pipeEnd: return "pipe_end.png"; break;
		case TextureID::cloud: return "cloud.png"; break;

		//added exception!
		default:"Unknown textureID";
	}
}

void ResourceManager::initTexture(TextureID id)
{
	sf::Texture texture;

	std::string fileName = "Textures/" + this->convertToStringTextureID(id);
	std::cout << fileName << std::endl;

	if (!texture.loadFromFile(fileName))
	{
		std::cerr << "Error::ResourceManager::initCloudTexture: Couldn't load the " + fileName <<"!"<< std::endl;
	}

	this->textures[id] = texture;
}

const sf::Texture& ResourceManager::getTexture(TextureID id) const
{
	return this->textures.at(id);
}