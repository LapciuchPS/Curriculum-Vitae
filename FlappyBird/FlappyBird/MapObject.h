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
	bool isAlive;
	std::unique_ptr<MovementBehaviour> movementStrategy;
	std::optional<sf::Sprite> objectSprite;

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

	inline void setIsAlive(bool truthValue)
	{
		this->isAlive = truthValue;
	}

public:
	//public functions
	inline MapObject(const sf::Vector2f& position = { 0.f,0.f }, const sf::Vector2f& size = sf::Vector2f({ 0.f,0.f }), const sf::Vector2f& moveDirection = { 0,0 }, float speed = 0.f,  const objectID ID = objectID::undefined, std::unique_ptr<MovementBehaviour> movementStrategy = nullptr, bool isOnScreen = true, bool isAlive = true)
		: objectHitbox(position, size), moveDirection(moveDirection), speed(speed), isOnScreen(isOnScreen), ID(ID), movementStrategy(std::move(movementStrategy)), isAlive(isAlive)
	{ }

	virtual ~MapObject() = default;

	inline void initObjectSprite(const sf::Texture& texture)
	{
		this->objectSprite.emplace(texture);

		float scaleX = this->objectHitbox.size.x / texture.getSize().x;
		float scaleY = this->objectHitbox.size.y / texture.getSize().y;

		this->objectSprite->setScale({ scaleX, scaleY });
	}

	inline void rotateSprite(float degrees)
	{
		this->objectSprite->setOrigin(this->objectSprite->getLocalBounds().size / 2.f);
		this->objectSprite->setRotation(sf::degrees(degrees));
		this->objectSprite->setOrigin(this->objectSprite->getLocalBounds().size);
	}

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
		//for testing
		sf::RectangleShape sketch(this->objectHitbox.size);
		sketch.setFillColor(sf::Color::Yellow);
		sketch.setOutlineColor(sf::Color::Black);
		sketch.setOutlineThickness(1);
		sketch.setPosition(this->objectHitbox.position);
		if (this->getObjectID() != SceneInterface::objectID::cloud && this->getObjectID() != SceneInterface::objectID::pipeEndUp &&
			this->getObjectID() != SceneInterface::objectID::pipeEndDown && this->getObjectID() != SceneInterface::objectID::pipeMiddle)
			target.draw(sketch);

		if (this->objectSprite.has_value())
			target.draw(this->objectSprite.value());
	}

	inline void update(float deltaTime) override
	{
		if (this->movementStrategy)
			this->movementStrategy->move(*this, deltaTime);

		if (this->objectSprite.has_value())
			this->objectSprite->setPosition(this->objectHitbox.position);
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

	inline const objectID getObjectID() const override
	{
		return this->ID;
	}

	inline const sf::Vector2f& getObjectDirection() const
	{
		return this->moveDirection;
	}

	inline float getObjectSpeed() const
	{
		return this->speed;
	}

	inline bool getIsOnScreen() const
	{
		return this->isOnScreen;
	}

	inline bool getIsAlive() const override
	{
		return this->isAlive;
	}
};

