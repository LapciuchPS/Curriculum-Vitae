#include "stdafx.h"
#include "ResourceManager.h"

void ResourceManager::initPlayerSpriteSheet()
{
	/*if (!this->playerSpriteSheet.loadFromFile())
	{
		std::cerr << "Error::ResourceMenager::initPlayerSpriteSheet::Couldn't load the player sprite sheet!";
	}*/
}

const sf::Texture& ResourceManager::getPlayerSpriteSheet() const
{
	return this->playerSpriteSheet;
}
