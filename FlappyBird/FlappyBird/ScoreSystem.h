#pragma once
#include "stdafx.h"
#include "EventHandler.h"

struct ScoreConfiguration;

class ScoreSystem: public EventObserver
{
private:
	//private variables
	int score = 0;
	sf::Vector2f scorePosition;
	std::optional<sf::Text> scoreText;

	//private methods
	void updateScoreText();
	void increaseScore(int points = 1);
	void alignScore();
	void onNotify(const Event& event) override;

public:
	ScoreSystem(const ScoreConfiguration& scoreConfig);

	void draw(sf::RenderTarget& target);
	int getScore() const;

};