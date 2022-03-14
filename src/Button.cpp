#include "Button.h"
#include <Arduino.h> /* we need arduino functions to implement this */


Button::Button(int aPin)
{ 
  pin = aPin;
}

void Button::debug()
{
  Serial.print("Button:");
  Serial.println(pin);
}
