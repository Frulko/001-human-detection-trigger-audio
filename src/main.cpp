#include <Arduino.h>
#include <HardwareSerial.h>
#include <HCSR04.h>
#include <Button.h>
#include <blinky.h>

#include <DFRobotDFPlayerMini.h>
#include <OneButton.h>
#include <Player.h>
#include <HumanDetection.h>

#define BUTTON_PIN 27

OneButton btn = OneButton(
  BUTTON_PIN,  // Input pin for the button
  false,        // Button is active LOW
  false         // Enable internal pull-up resistor
);

Player player = Player();
HumanDetection detector = HumanDetection();

// Handler function for a single click:
static void handleClick() {
  Serial.println("Clicked!");
  player.fadeIn();
}

void setup() {
  Serial.begin(115200);

  // blinky_init();
  // Button btn = Button(1);
  // btn.debug();

  // Single Click event attachment
  btn.attachClick(handleClick);

  // // Double Click event attachment with lambda
  btn.attachDoubleClick([]() {
    // Serial.println("Double Pressed!");
    player.fadeOut();
  });

  // btn.attachMultiClick([]() {
  //   Serial.println("MultiClick Pressed!");
  // });

  btn.attachLongPressStart([]() {
    // Serial.println("Long press start");
    player.stopFade();
  });

  // btn.attachDuringLongPress([]() {
  //   Serial.println("Long press progress");
  // });

  // btn.attachLongPressStop([]() {
  //   Serial.println("Long press stop");
  // });
}

void loop() {
  // do_blink(500);
  btn.tick();
  player.tick();
}
