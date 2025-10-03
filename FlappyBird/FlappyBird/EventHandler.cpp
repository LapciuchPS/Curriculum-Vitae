#include "stdafx.h"
#include "EventHandler.h"
#include "Player.h"
#include "InteractableObjects.h"
#include "ScoreSystem.h"

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

void EventHandler::checkPlayer(const sf::Vector2u& windowSize)
{
	//player is already dead
	if (this->currentScene->getPlayer() == nullptr) return;

	sf::FloatRect playerHitbox = this->currentScene->getPlayer()->getObjectHitbox();

	//collision with pipes
	for (const auto& pipe : this->currentScene->getAll<Pipe>())
	{
		//pipe parts
		for (const auto& pipeElement : pipe->getPipeParts())
			if (pipeElement->checkCollision(playerHitbox))
				this->notify(Event(Type::pipeCollision));

		//gap
		if (pipe->getGap()->checkCollision(playerHitbox))
			this->notify(Event(Type::birdInGap, pipe));
		else if (pipe->getVisitedByBird())
			//gap passed so add a point to the score
			this->notify(Event(Type::passedPipe, pipe));
	}

	//collision with bonuses
	for (const auto& bonus : this->currentScene->getAll<Bonus>())
	{
		if (bonus->checkCollision(playerHitbox))
			this->notify(Event(Type::bonusCollision, bonus));
	}

	//collision with screen edges
	if (playerHitbox.position.y <= 0 || playerHitbox.position.y + playerHitbox.size.y >= windowSize.y)
		this->notify(Event(Type::screenCollision));
}

template<typename T>
void EventHandler::checkVisibility()
{
	for (auto& object : this->currentScene->getAll<T>())
	{
		if (object->getIsAlive())
		{
			sf::FloatRect hitbox = object->getObjectHitbox();

			if (hitbox.position.x + hitbox.size.x < 0.f)
				this->notify(Event(Type::outOfScreen, object));
		}
	}		
}

void EventHandler::update(const sf::Vector2u& windowSize)
{
	this->checkPlayer(windowSize);
	this->checkVisibility<Pipe>();
	this->checkVisibility<Cloud>();
}

void EventHandler::notify(const Event& event)
{
	for (EventObserver* const observer : this->observers)
		observer->onNotify(event);
}

