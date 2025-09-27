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
	bool isAlive;
	std::unique_ptr<MovementBehaviour> movementStrategy;
	std::optional<sf::Sprite> objectSprite;

protected:
	//protected functions
	//setters
	inline void setObjectSpeed(float newSpeed)
	{
		this->speed = newSpeed;
	}

	inline void setObjectPosition(const sf::Vector2f& newPosition)
	{
		this->objectHitbox.position = newPosition;
	}

	inline void setObjectSize(const sf::Vector2f& newSize)
	{
		this->objectHitbox.size = newSize;
	}

	inline void setMoveDirection(const sf::Vector2f& direction)
	{
		this->moveDirection = direction;
	}

	inline void setIsAlive(bool truthValue)
	{
		this->isAlive = truthValue;
	}

	inline void setSpriteFrame(sf::Vector2i textureStartingPoint, sf::Vector2i frameSize)
	{
		if(this->objectSprite.has_value())
			this->objectSprite->setTextureRect({ textureStartingPoint, frameSize });
	}

public:
	//public functions
	inline MapObject(const sf::Vector2f& position = { 0.f,0.f }, const sf::Vector2f& size = sf::Vector2f({ 0.f,0.f }), const sf::Vector2f& moveDirection = { 0,0 }, float speed = 0.f,  const objectID ID = objectID::undefined, std::unique_ptr<MovementBehaviour> movementStrategy = nullptr, bool isAlive = true)
		: objectHitbox(position, size), moveDirection(moveDirection), speed(speed), ID(ID), movementStrategy(std::move(movementStrategy)), isAlive(isAlive)
	{ }

	virtual ~MapObject() = default;

	inline void initObjectSprite(const sf::Texture& texture, sf::Vector2i frameSize = { 0,0 }, sf::Vector2f spriteScale = { 1.f, 1.f })
	{
		this->objectSprite.emplace(texture);

		//it means that a texture isn't a spritesheet so it can be easly rescaled
		if (frameSize == sf::Vector2i({ 0,0 }))
			frameSize = { static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y) };

		float scaleX = (this->objectHitbox.size.x / frameSize.x) * spriteScale.x;
		float scaleY = (this->objectHitbox.size.y / frameSize.y) * spriteScale.y;

		this->objectSprite->setOrigin({frameSize.x / 2.f, frameSize.y / 2.f});
		this->objectSprite->setScale({ scaleX, scaleY });
		this->objectSprite->setTextureRect({ {0,0}, frameSize });
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
		/*sf::RectangleShape sketch(this->objectHitbox.size);
		sketch.setFillColor(sf::Color::Yellow);
		sketch.setOutlineColor(sf::Color::Black);
		sketch.setOutlineThickness(1);
		sketch.setPosition(this->objectHitbox.position);
		if (this->getObjectID() == SceneInterface::objectID::undefined)
			target.draw(sketch);*/

		if (this->objectSprite.has_value()&&this->isAlive)
		{
			this->objectSprite->setPosition(this->objectHitbox.position + this->objectHitbox.size / 2.f);
			target.draw(this->objectSprite.value());
		}		
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

	inline sf::Sprite& getObjectSprite()
	{
		if (this->objectSprite.has_value())
			return *this->objectSprite;
	}

	inline bool getIsAlive() const override
	{
		return this->isAlive;
	}
};

