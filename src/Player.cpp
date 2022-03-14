#include "Player.h"
#include <Arduino.h>

Player::Player()
{

}

void Player::play(){
  
}

void Player::tick(){
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

  Serial.print("volume: ");
  Serial.print(volume);
  Serial.print(" - ");
  Serial.print("step: ");
  Serial.println(currentFadeStep);
  delay(25 * 2);
}

void Player::fadeIn(){
  if (fadeStarted) {
    return;
  }
  Serial.println("FadeIn"); 
  fadeStarted = true;
  currentFadeStep = 0;
  volume = 0;
  fadeDirection = 1;
}

void Player::fadeOut(){
  if (fadeStarted) {
    return;
  }
  Serial.println("fadeOut"); 
  fadeStarted = true;
  currentFadeStep = maxFadeStep;
  volume = maxVolume;
  fadeDirection = -1;
}

void Player::stopFade(){
  fadeStarted = false;
}
