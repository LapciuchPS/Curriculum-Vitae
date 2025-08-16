#pragma once

class Player;

class SceneInterface
{
protected:
	enum class objectID { undefined = 0, player, pipeEnd, pipeMiddle, enemyBird, cloud, wind };

public:
	~SceneInterface() = default;

	virtual void update(const float& deltaTime) = 0;
	virtual void draw(sf::RenderTarget& target) = 0;
	inline virtual const objectID& getObjectID() const 
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

	void update(const float& deltaTime);

	void draw(sf::RenderTarget& target);

	Player* getPlayer() const;

};