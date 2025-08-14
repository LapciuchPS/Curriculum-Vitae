#pragma once
#include "stdafx.h"

class MapObject
{
private:
	//private variables
	sf::FloatRect objectHitbox;

protected:
	//protected functions
	//setters
	inline void setObjectPosition(const sf::Vector2f& newPosition)
	{
		this->objectHitbox.position = newPosition;
	}

	inline void setObjectSize(const sf::Vector2f& newSize)
	{
		this->objectHitbox.size = newSize;
	}

	inline void moveObject(sf::Vector2f move)
	{
		this->objectHitbox.position += move;
	}

public:
	//public functions
	inline MapObject(const sf::Vector2f& position = sf::Vector2f({0.f,0.f}) , const sf::Vector2f& size = sf::Vector2f({0.f,0.f}))
		: objectHitbox(position, size)
	{ }

	virtual void update(const float deltaTime) = 0;
	virtual void draw(sf::RenderTarget& target, const sf::Sprite& objectSprite) const = 0;

	//getters
	inline const sf::Vector2f& getObjectPosition() const
	{
		return this->objectHitbox.position;
	}

	inline const sf::Vector2f& getObjectSize() const
	{
		return this->objectHitbox.size;
	}

	inline const sf::FloatRect& getObjectHitbox() const
	{
		return this->objectHitbox;
	}
};

