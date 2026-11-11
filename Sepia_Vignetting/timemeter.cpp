#include "timemeter.h"

TimeMeter::TimeMeter() {}

std::chrono::high_resolution_clock::duration TimeMeter::countSurveysMean()
{
    std::chrono::high_resolution_clock::duration sum {0};

    for(std::chrono::high_resolution_clock::duration& duration : this->time_surveys)
        sum += duration;

    return sum / this->time_surveys.size();
}

void TimeMeter::addTimeSurvey()
{
    if(this->time_surveys.size() >= this->max_container_size)
        this->time_surveys.pop_front();

    this->time_surveys.push_front(this->end_point - this->start_point);
}

void TimeMeter::startTimeSurvey()
{
    this->start_point = std::chrono::high_resolution_clock::now();
}

void TimeMeter::endTimeSurvey()
{
    this->end_point = std::chrono::high_resolution_clock::now();
}
