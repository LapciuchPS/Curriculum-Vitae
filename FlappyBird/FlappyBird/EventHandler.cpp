#include "stdafx.h"
#include "EventHandler.h"
#include "Player.h"
#include "InteractableObjects.h"

using Type = Event::EventType;

//Event class
Event::Event(EventType type, SceneInterface* obj1, SceneInterface* obj2):
	type(type), obj1(obj1), obj2(obj2)
{

}

Event::EventType Event::getEventType() const
{
	return this->type;
}

SceneInterface* Event::getFirst() const
{
	return this->obj1;
}

SceneInterface* Event::getSecond() const
{
	return this->obj2;
}

//EventHandler class
EventHandler::EventHandler(Scene* currentScene) :
	currentScene(currentScene)
{
}

void EventHandler::addObserver(EventObserver* observer)
{
	this->observers.push_back(observer);
}

void EventHandler::removeObserver(EventObserver* const observer)
{
	auto condition = [&observer](EventObserver* observerInVector)
		{
			return observer == observerInVector;
		};

	this->observers.erase(std::remove_if(this->observers.begin(), this->observers.end(), condition), this->observers.end());
}

void EventHandler::removeAllObservers()
{
	this->observers.clear();
}

void EventHandler::checkPlayerCollision(const sf::Vector2u& windowSize)
{
	//player is already dead
	if (this->currentScene->getPlayer() == nullptr) return;

	sf::FloatRect playerHitbox = this->currentScene->getPlayer()->getObjectHitbox();

	//collision with pipes
	for (const auto& pipe : this->currentScene->getAll<Pipe>())
		for (const auto& pipeElement : pipe->getPipeElements())
			if (pipeElement->checkCollision(playerHitbox))
				this->notify(Event(Type::pipeCollision));

	//collision with screen edges
	if (playerHitbox.position.y <= 0 || playerHitbox.position.y + playerHitbox.size.y >= windowSize.y)
		this->notify(Event(Type::screenCollision));
}

void EventHandler::checkPipesVisibility()
{
	//pipes
	for (auto& pipe : this->currentScene->getAll<Pipe>())
	{
		if (pipe->getIsOnScreen())
		{
			sf::FloatRect element = pipe->getPipeElements().front()->getObjectHitbox();

			if (element.position.x + element.size.x < 0.f)
				this->notify(Event(Type::outOfScreen, pipe));
		}
	}

	//clouds
	for (auto& cloud : this->currentScene->getAll<Cloud>())
		std::cout << cloud->getObjectSpeed() << std::endl;
}

void EventHandler::update(const sf::Vector2u& windowSize)
{
	this->checkPlayerCollision(windowSize);
	this->checkPipesVisibility();
}

void EventHandler::notify(const Event& event)
{
	for (EventObserver* const observer : this->observers)
		observer->onNotify(event);
}

