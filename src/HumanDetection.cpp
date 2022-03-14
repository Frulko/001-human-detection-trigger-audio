#include <HumanDetection.h>
#include <Arduino.h>
#include <NewPing.h>
#include <vector>


HumanDetection::HumanDetection()
{
  std::vector<NewPing> sonars = {
    NewPing(19, 18, maxDistance),
    NewPing(19, 21, maxDistance)
  };
}

void HumanDetection::trigger()
{
  if(_humanDetectionFunc) _humanDetectionFunc();
  if(_paramHumanDetectionFunc) _paramHumanDetectionFunc(_humanDetectionFuncParam);
}

void HumanDetection::attachDetection(callbackFunction newFunction)
{
  _humanDetectionFunc = newFunction;
}

void HumanDetection::attachDetection(parameterizedCallbackFunction newFunction, void *parameter)
{
  _paramHumanDetectionFunc = newFunction;
  _humanDetectionFuncParam = parameter;
}

void HumanDetection::tick()
{
  for (int i = 0; i < sonars.size(); ++i) {
    delay(30); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    Serial.print(i);
    Serial.print("=");
    Serial.print(sonars[i].ping_cm());
    Serial.print("cm ");
  }
}