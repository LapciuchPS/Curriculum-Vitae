#include "stdafx.h"
#include "ScoreSystem.h"


ScoreSystem::ScoreSystem()
{
	//load the scoreFont
	//this->scoreFont.openFromFile()
}

void ScoreSystem::increaseScore(int points)
{
	this->score += points;
}

int ScoreSystem::getScore() const
{
	return this->score;
}