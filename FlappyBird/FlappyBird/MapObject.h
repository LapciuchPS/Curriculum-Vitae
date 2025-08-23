#pragma once
#include "Scene.h"
#include "MovementBehaviour.h"

class MapObject : public SceneInterface
{
private:
	//private variables
	sf::FloatRect objectHitbox;
	sf::Vector2f moveDirection;
	objectID ID;
	float speed;
	bool isOnScreen;
	std::unique_ptr<MovementBehaviour> movementStrategy;

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

public:
	//public functions
	inline MapObject(const sf::Vector2f& position = { 0.f,0.f }, const sf::Vector2f& size = sf::Vector2f({ 0.f,0.f }), const sf::Vector2f& moveDirection = { 0,0 }, float speed = 0.f,  const objectID ID = objectID::undefined, std::unique_ptr<MovementBehaviour> movementStrategy = nullptr, bool isOnScreen = false)
		: objectHitbox(position, size), moveDirection(moveDirection), speed(speed), isOnScreen(isOnScreen), ID(ID), movementStrategy(std::move(movementStrategy))
	{ }

	inline bool checkCollision(const sf::FloatRect& otherHitbox)
	{
		return this->objectHitbox.findIntersection(otherHitbox).has_value();
	}

	inline void moveObject(sf::Vector2f movement)
	{
		this->objectHitbox.position += movement;
	}

	inline void draw(sf::RenderTarget& target) override
	{
		sf::RectangleShape sketch(this->objectHitbox.size);
		sketch.setPosition(this->objectHitbox.position);

		target.draw(sketch);
	}

	inline void update(float deltaTime) override
	{
		if (this->movementStrategy)
			this->movementStrategy->move(*this, deltaTime);
	}

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

	inline const objectID& getObjectID() const override
	{
		return this->ID;
	}

	inline const sf::Vector2f& getObjectDirection() const
	{
		return this->moveDirection;
	}

	inline const float getObjectSpeed() const
	{
		return this->speed;
	}
};

