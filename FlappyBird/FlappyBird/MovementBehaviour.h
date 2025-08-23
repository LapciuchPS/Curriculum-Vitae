#pragma once

class MapObject;

class MovementBehaviour
{
private:

public:
	virtual ~MovementBehaviour() = default;
	virtual void move(MapObject& object, float deltaTime) = 0;
};

class LinearMovement : public MovementBehaviour
{
private:

public:
	void move(MapObject& object, float deltaTime) override;
};