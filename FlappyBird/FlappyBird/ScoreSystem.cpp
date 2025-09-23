#include "stdafx.h"
#include "ScoreSystem.h"
#include "ResourceManager.h"
#include "Configurations.h"

void ScoreSystem::increaseScore(int points)
{
	this->score += points;
}

void ScoreSystem::alignScore()
{
	sf::FloatRect scoreRect = this->scoreText->getLocalBounds();
	this->scoreText->setOrigin(scoreRect.getCenter());
	this->scoreText->setPosition(this->scorePosition);
}

void ScoreSystem::onNotify(const Event& event)
{
	if (event.getEventType() == Event::EventType::passedPipe)
	{
		this->increaseScore();
		this->updateScoreText();
	}	
}

void ScoreSystem::updateScoreText()
{
	this->scoreText->setString(std::to_string(this->score));
	this->alignScore();
}

ScoreSystem::ScoreSystem(const ScoreConfiguration& scoreConfig):
	scorePosition(scoreConfig.position)
{
	this->scoreText.emplace(ResourceManager::get().getFont());
	this->scoreText->setCharacterSize(scoreConfig.characterSize);
	this->scoreText->setFillColor(scoreConfig.outlineColor);
	this->updateScoreText();
}

void ScoreSystem::draw(sf::RenderTarget& target)
{
	target.draw(this->scoreText.value());
}

int ScoreSystem::getScore() const
{
	return this->score;
}