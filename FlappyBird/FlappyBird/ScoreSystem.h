#pragma once
#include "stdafx.h"

class ScoreSystem
{
private:
	//private variables
	int score = 0;
	sf::Font scoreFont;
	std::optional<sf::Text> scoreText;


public:
	ScoreSystem();

	void increaseScore(int points = 1);

	int getScore() const;

};