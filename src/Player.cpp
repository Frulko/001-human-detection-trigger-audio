#include "Player.h"
#include <Arduino.h>
#include <HardwareSerial.h>

Player::Player()
{

}

void Player::init()
{
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Fast"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  Serial2.begin(9600);
  dfPlayer.begin(Serial2, true);
  dfPlayer.loop(1);
  dfPlayer.randomAll();
  dfPlayer.volume(0);

  if (autoplay) {
    dfPlayer.play(0);
  }
}

void Player::play()
{
  dfPlayer.randomAll();
  dfPlayer.play(0);
}

void Player::tick()
{
  if(!fadeStarted){
    return;
  }

  if(fadeDirection == 1 && currentFadeStep > maxFadeStep){
    Serial.println("End loop- fadeIn");
    fadeStarted = false;
    return;
  }

  if(fadeDirection == -1 && currentFadeStep < 0){
    Serial.println("End loop- fadeOut");
    fadeStarted = false;
    return;
  }

  volume = map(currentFadeStep, 0, maxFadeStep, 0, 30);
  
  currentFadeStep = currentFadeStep + (1 * fadeDirection);

  dfPlayer.volume(volume);

  Serial.print("volume: ");
  Serial.print(volume);
  Serial.print(" - ");
  Serial.print("step: ");
  Serial.println(currentFadeStep);
  delay(25 * 2);
}

void Player::fadeIn()
{
  if (fadeStarted) {
    return;
  }
  Serial.println("FadeIn"); 
  fadeStarted = true;
  currentFadeStep = 0;
  volume = 0;
  fadeDirection = 1;
}

void Player::fadeOut()
{
  if (fadeStarted) {
    return;
  }
  Serial.println("fadeOut"); 
  fadeStarted = true;
  currentFadeStep = maxFadeStep;
  volume = maxVolume;
  fadeDirection = -1;
}

void Player::stopFade()
{
  fadeStarted = false;
}

bool Player::isFaded()
{
  return volume == maxVolume && !fadeStarted;
}
