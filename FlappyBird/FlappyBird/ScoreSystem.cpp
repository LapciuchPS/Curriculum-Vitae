#include "stdafx.h"
#include "ScoreSystem.h"
#include "ResourceManager.h"
#include "Configurations.h"
#include "InteractableObjects.h"

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
	int points = 0;

	if (event.getEventType() == Event::EventType::passedPipe)
		points = 1;
	else if (event.getEventType() == Event::EventType::bonusCollision)
		if(auto* ptr = dynamic_cast<ScoreChanger*>(event.getFirst()))
			points = ptr->getExtraPoints();

	if (points)
	{
		this->increaseScore(points);
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