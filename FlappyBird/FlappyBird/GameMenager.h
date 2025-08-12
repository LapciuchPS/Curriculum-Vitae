#pragma once

class GameMenager
{
private:
	//private variables
	sf::RenderWindow gameWindow;

	//private functions
	void initWindow();

public:
	//public functions
	GameMenager();
	~GameMenager();

	
	inline bool isRunning() const
	{
		return this->gameWindow.isOpen();
	}

	void updateGame();
	void renderGame();
};

