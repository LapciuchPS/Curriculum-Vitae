#include "stdafx.h"
#include "Scene.h"
#include "Player.h"
#include "InteractableObjects.h"
#include "EventHandler.h"

void Scene::addObject(std::unique_ptr<SceneInterface> object)
{
	this->sceneObjects.push_back(std::move(object));
}

void Scene::removeObject(SceneInterface* object)
{
	auto condition = [object](const std::unique_ptr<SceneInterface>& ptr)
		{
			return ptr.get() == object;
		};

	auto it = std::remove_if(this->sceneObjects.begin(), this->sceneObjects.end(), condition);
	this->sceneObjects.erase(it, this->sceneObjects.end());
}

void Scene::clearDeadObject(EventHandler& eventHandler)
{
	auto condition = [&eventHandler](const std::unique_ptr<SceneInterface>& object)
		{
			if (!object->getIsAlive())
			{
				//remove observer
				if (EventObserver* ptr = dynamic_cast<EventObserver*>(object.get()))
					eventHandler.removeObserver(ptr);

				return true;
			}
			
			return false;
		};

	this->sceneObjects.erase(std::remove_if(this->sceneObjects.begin(), this->sceneObjects.end(), condition), this->sceneObjects.end());
}

void Scene::clearWholeScene()
{
	this->sceneObjects.clear();
}

void Scene::update(float deltaTime)
{
	for (const auto& object : this->sceneObjects)
		object->update(deltaTime);
}

void Scene::draw(sf::RenderTarget& target)
{
	for (const auto& object : this->sceneObjects)
		object->draw(target);
}

Player* Scene::getPlayer() const
{
	for (const auto& object : this->sceneObjects)
		if (object->getObjectID() == objectID::player)
			return dynamic_cast<Player*>(object.get());

	return nullptr;
}

std::vector<Pipe*> Scene::getPipes() const
{
	std::vector<Pipe*> pipes;

	for (const auto& object : this->sceneObjects)
		if (auto* pipe = dynamic_cast<Pipe*>(object.get()))
		{
			pipes.push_back(pipe);
		}
			
			
	return pipes;
		
}



