#pragma once
#include "stdafx.h"

class MapObject
{
private:
	//private variables
	sf::Vector2f objectPosition;
	sf::Vector2f objectSize;

protected:
	//protected functions
	inline void setObjectPosition(const sf::Vector2f& newPosition)
	{
		this->objectPosition = newPosition;
	}

	inline void setObjectSize(const sf::Vector2f& newSize)
	{
		this->objectSize = newSize;
	}


public:
	//public functions
	inline MapObject(const sf::Vector2f& position = sf::Vector2f({0.f,0.f}) , const sf::Vector2f& size = sf::Vector2f({0.f,0.f}))
		: objectPosition(position), objectSize(size)
	{ }

	inline const sf::Vector2f& getObjectPosition() const
	{
		return this->objectPosition;
	}

	inline const sf::Vector2f& getObjectSize() const
	{
		return this->objectSize;
	}
};

