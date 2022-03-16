#include <HumanDetection.h>
#include <Arduino.h>
#include <NewPing.h>
#include <vector>



HumanDetection::HumanDetection()
{
  
}

void HumanDetection::init()
{
  Serial.println("Human starter");
  sonars = {
    NewPing(19, 18, maxDistance),
    NewPing(19, 21, maxDistance)
  };


  Serial.print("size");
  Serial.println(sonars.size());
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
    delay(50);  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

    int distance = sonars.at(i).ping_cm();

    if (distance < 1) { // returns true once every 10 ms, determines sampling frequency
      return;
    }

    bool canUpdate = compareDistance(distance, previousDistance[i], i);

    if(canUpdate) {
      previousDistance.at(i) = distance;
    }
  }
}

bool HumanDetection::compareDistance(int distance, int previousDistance, int index)
{
   if (distance < 1) {
   return false;
  }

  int diff = abs(distance - previousDistance);

  if(diff > deltaDetection){
    Serial.print("trigger cut: ");
    Serial.print(diff);
    Serial.print(" - ");
    Serial.print(distance);
    Serial.print(",");
    Serial.println(previousDistance);
    trigger();
  }

  return true;
}

