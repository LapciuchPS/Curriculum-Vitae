#pragma once

class Player;
class EventHandler;

class SceneInterface
{
protected:
	enum class objectID { undefined = 0, player, pipeEndUp, pipeEndDown, pipeMiddle, enemyBird, cloud, wind };

public:
	virtual ~SceneInterface() = default;

	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderTarget& target) = 0;

	//getters
	inline virtual bool getIsAlive() const
	{
		return true; 
	}

	inline virtual const objectID getObjectID() const 
	{
		return objectID::undefined;
	}
};

class Scene : public SceneInterface
{
private:
	std::vector<std::unique_ptr<SceneInterface>> sceneObjects;

public:
	Scene() = default;

	void addObject(std::unique_ptr<SceneInterface> object);
	void removeObject(SceneInterface* object);
	void clearDeadObject(EventHandler& eventHandler);
	void clearWholeScene();
	void update(float deltaTime) override;
	void draw(sf::RenderTarget& target);

	//gettes
	Player* getPlayer() const;

	template<typename T>
	inline std::vector<T*> getAll() const
	{
		std::vector<T*> wantedObjects;

		for (auto& object : this->sceneObjects)
			if (T* ptr = dynamic_cast<T*>(object.get()))
			{
				wantedObjects.push_back(ptr);
			}

		return wantedObjects;
	}


};