#include "stdafx.h"
#include "ResourceManager.h"

void ResourceManager::initPlayerSpriteSheet()
{
	/*if (!this->playerSpriteSheet.loadFromFile())
	{
		std::cerr << "Error::ResourceMenager::initPlayerSpriteSheet::Couldn't load the player sprite sheet!";
	}*/
}

void ResourceManager::initCloudTexture()
{
	sf::Texture texture;

	if (!texture.loadFromFile("Textures/cloud.png"))
	{
		std::cerr << "Error::ResourceManager::initCloudTexture: Couldn't load the cloud texture!\n";
	}

	this->textures[TextureID::cloud] = texture;
}

void ResourceManager::initPipeMiddleTexture()
{
	sf::Texture texture;
	if (!texture.loadFromFile("Textures/pipe_middle.png"))
	{
		std::cerr << "Error::ResourceManager::initCloudTexture: Couldn't load the pipeMiddle texture!\n";
	}

	this->textures[TextureID::pipeMiddle] = texture;
}

void ResourceManager::initPipeEndTexture()
{
	sf::Texture texture;
	if (!texture.loadFromFile("Textures/pipe_end.png"))
	{
		std::cerr << "Error::ResourceManager::initCloudTexture: Couldn't load the pipeEnd texture!\n";
	}

	this->textures[TextureID::pipeEnd] = texture;
}

const sf::Texture& ResourceManager::getTexture(TextureID id) const
{
	return this->textures.at(id);
}
