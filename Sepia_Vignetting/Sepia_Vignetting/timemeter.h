#ifndef TIMEMETER_H
#define TIMEMETER_H

#include <deque>
#include <chrono>

using TimeContainer = std::deque<std::chrono::high_resolution_clock::duration>;

class TimeMeter
{
public:
    TimeMeter();

private:
    TimeContainer time_surveys{};
    std::chrono::high_resolution_clock::time_point start_point{};
    std::chrono::high_resolution_clock::time_point end_point{};
    static constexpr size_t max_container_size = 5;

    std::chrono::high_resolution_clock::duration countSurveysMean();

public:

    bool isFull() const;
    void startTimeSurvey();
    void endTimeSurvey();
    void addTimeSurvey();
    void clearSurveysContainer();

    template <typename TargetUnitTime>
    TargetUnitTime getMeanSurveys()
    {
        std::chrono::high_resolution_clock::duration mean = this->countSurveysMean();
        return std::chrono::duration_cast<TargetUnitTime>(mean);
    }

    const TimeContainer& getTimeSurveys() const;

};

#endif // TIMEMETER_H
