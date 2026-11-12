#include "timemeter.h"

TimeMeter::TimeMeter() {}

std::chrono::high_resolution_clock::duration TimeMeter::countSurveysMean()
{
    std::chrono::high_resolution_clock::duration sum {0};

    for(std::chrono::high_resolution_clock::duration& duration : this->time_surveys)
        sum += duration;

    return sum / this->time_surveys.size();
}

bool TimeMeter::isFull() const
{
    return this->time_surveys.size() == this->max_container_size;
}

void TimeMeter::addTimeSurvey()
{
    if(this->time_surveys.size() >= this->max_container_size)
        this->time_surveys.pop_front();

    this->time_surveys.push_back(this->end_point - this->start_point);
}

void TimeMeter::clearSurveysContainer()
{
    this->time_surveys.clear();
}

const TimeContainer &TimeMeter::getTimeSurveys() const
{
    return this->time_surveys;
}

void TimeMeter::startTimeSurvey()
{
    this->start_point = std::chrono::high_resolution_clock::now();
}

void TimeMeter::endTimeSurvey()
{
    this->end_point = std::chrono::high_resolution_clock::now();
}
