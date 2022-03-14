#ifndef HUMANDETECTION_H /* include guards */
#define HUMANDETECTION_H
#include <NewPing.h>
#include <vector>

extern "C" {
typedef void (*callbackFunction)(void);
typedef void (*parameterizedCallbackFunction)(void *);
}

class HumanDetection
{
  private: 
    char name[30];
    std::vector<NewPing> sonars;
    int numberOfSonar = 2; // Number of sensors.
    int maxDistance = 200; // Maximum distance (in cm) to ping.

    callbackFunction _humanDetectionFunc = NULL;
    parameterizedCallbackFunction _paramHumanDetectionFunc = NULL;
    void *_humanDetectionFuncParam = NULL;

  public: 
    HumanDetection();
    void tick();
    void trigger();
    void attachDetection(callbackFunction newFunction);
    void attachDetection(parameterizedCallbackFunction newFunction, void *parameter);
    
};

#endif /* HUMANDETECTION_H */