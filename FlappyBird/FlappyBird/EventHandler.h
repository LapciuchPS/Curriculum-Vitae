#pragma once
#include "MapObject.h"

class Scene;

class Event
{
public:
	enum class EventType {screenCollision, pipeCollision, outOfScreen };

private:
	EventType type;
	SceneInterface* obj1;
	SceneInterface* obj2;

public:
	Event(EventType type, SceneInterface* obj1 = nullptr, SceneInterface* obj2 = nullptr);

	Event::EventType getEventType() const;
	SceneInterface* getFirst() const;
	SceneInterface* getSecond() const;

};

//Interface
class EventObserver
{
private:
public:
	virtual ~EventObserver() = default;
	virtual void onNotify(const Event& event) = 0;
};

//Subject
class EventHandler
{
private:
	Scene* currentScene;
	std::vector<EventObserver*> observers;

	void checkPlayerCollision(const sf::Vector2u& windowSize);
	void checkPipesVisibility();

public:
	EventHandler(Scene* currentScene);
	void addObserver(EventObserver* observer);
	void removeObserver(EventObserver* observer);

	void update(const sf::Vector2u& windowSize);

protected:
	void notify(const Event& event);
};

