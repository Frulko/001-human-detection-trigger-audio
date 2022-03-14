#include <Arduino.h>
#include <HardwareSerial.h>


#include <DFRobotDFPlayerMini.h>
#include <OneButton.h>
#include <Player.h>
#include <HumanDetection.h>
#include <arduino-timer.h>

#define BUTTON_PIN 27
// int delay_to_stop = 1000 * 1 * 60 * 5;
int delay_to_stop = 1000 * 5;

OneButton btn = OneButton(
  BUTTON_PIN,  // Input pin for the button
  false,        // Button is active LOW
  false         // Enable internal pull-up resistor
);

auto timer = timer_create_default();
Player player = Player();
HumanDetection detector = HumanDetection();

// Handler function for a single click:
static void handleClick() {
  Serial.println("Clicked!");

  detector.trigger();
}

bool stopSound(void *argument /* optional argument given to in/at/every */) {
  player.fadeOut();
  Serial.println("<--- stop sound");
  return true;
}

void startSound() {
  player.fadeIn();
  Serial.println("---> start sound");
  timer.cancel();
  timer.in(delay_to_stop, stopSound );
}

void setup() {
  Serial.begin(115200);


  btn.attachClick(handleClick);
  btn.attachDoubleClick([]() {
    // Serial.println("Double Pressed!");
    // player.fadeOut();
  });

  btn.attachLongPressStart([]() {
    // Serial.println("Long press start");
    player.stopFade();
  });

  detector.attachDetection([]() {
    Serial.println("Human detected !");
    startSound();
  });
}





void loop() {
  timer.tick();
  btn.tick();
  player.tick();
  detector.tick();
}
