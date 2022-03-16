#include <Arduino.h>

#include <OneButton.h>
#include <Player.h>
#include <HumanDetection.h>
#include <arduino-timer.h>

#define BUTTON_PIN 27
// int delay_to_stop = 1000 * 1 * 60 * 5;
int delay_to_stop = 1000 * 1 * 30;
int incomingByte = 0;

OneButton btn = OneButton(
  BUTTON_PIN,  // Input pin for the button
  false,        // Button is active LOW
  false         // Enable internal pull-up resistor
);

auto timer = timer_create_default();
Player player = Player();
HumanDetection detector = HumanDetection();

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
  player.init();
  detector.init();

  btn.attachClick([]() {
    Serial.println("Clicked!");
    detector.trigger();
  });

  btn.attachDoubleClick([]() {
    player.fadeOut();
  });

  btn.attachLongPressStart([]() {
    player.stopFade();
  });

  detector.attachDetection([]() {
    Serial.println("Human detected !");
    if (!player.isFaded()) {
      startSound();
    }
  });
}

void loop() {
  timer.tick();
  btn.tick();
  player.tick();
  detector.tick();
}
