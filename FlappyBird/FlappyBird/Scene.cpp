#include "stdafx.h"
#include "Scene.h"
#include "Player.h"

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

void Scene::update(const float& deltaTime)
{
	for (auto& object : this->sceneObjects)
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



