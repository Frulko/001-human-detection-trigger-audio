#ifndef HUMANDETECTION_H /* include guards */
#define HUMANDETECTION_H
#include <NewPing.h>
#include <vector>
// #include <Filters.h>

// #include <AH/STL/cmath>                    // std::round
// #include <Filters/MedianFilter.hpp>        // MedianFilter

extern "C" {
typedef void (*callbackFunction)(void);
typedef void (*parameterizedCallbackFunction)(void *);
}

class HumanDetection
{
  private: 
    char name[30];
    std::vector<NewPing> sonars;

    // std::vector<MedianFilter<10, uint16_t>> mediaFilters;
    std::vector<int> previousDistance = {0, 0};
    int numberOfSonar = 2; // Number of sensors.
    int maxDistance = 500; // Maximum distance (in cm) to ping.
    int deltaDetection = 70;
    callbackFunction _humanDetectionFunc = NULL;
    parameterizedCallbackFunction _paramHumanDetectionFunc = NULL;
    void *_humanDetectionFuncParam = NULL;
    bool compareDistance(int distance, int previousDistance, int index);

  public: 
    HumanDetection();
    void init();
    void tick();
    void trigger();
    void attachDetection(callbackFunction newFunction);
    void attachDetection(parameterizedCallbackFunction newFunction, void *parameter);
};

#endif /* HUMANDETECTION_H */