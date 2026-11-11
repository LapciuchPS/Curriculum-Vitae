#ifndef TIMEMETER_H
#define TIMEMETER_H

#include <deque>
#include <chrono>

class TimeMeter
{
public:
    TimeMeter();

private:
    std::deque<std::chrono::high_resolution_clock::duration> time_surveys{};
    std::chrono::high_resolution_clock::time_point start_point{};
    std::chrono::high_resolution_clock::time_point end_point{};
    static constexpr size_t max_container_size = 5;

    std::chrono::high_resolution_clock::duration countSurveysMean();

public:

    void startTimeSurvey();
    void endTimeSurvey();
    void addTimeSurvey();

    template <typename TargetUnitTime>
    TargetUnitTime getMeanSurveys()
    {
        std::chrono::high_resolution_clock::duration mean = this->countSurveysMean();
        return std::chrono::duration_cast<TargetUnitTime>(mean);
    }

};

#endif // TIMEMETER_H
