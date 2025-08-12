#pragma once

class GameManager
{
private:
	//private variables
	sf::RenderWindow gameWindow;
	std::optional<sf::Event> currentEvent;

	//private functions
	void initWindow();

public:
	//public functions
	GameManager();
	~GameManager();

	
	inline bool isRunning() const
	{
		return this->gameWindow.isOpen();
	}

	void updateGame();
	void renderGame();
};

