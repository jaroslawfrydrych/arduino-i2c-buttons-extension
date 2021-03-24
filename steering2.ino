#include "Arduino.h"
#include "PCF8575.h"

#define BUTTONS_COUNT 9
#define LEDS_COUNT 1

PCF8575 pcf8575(0x20);

#include "buttontype.enum.h"
#include "button.h"
#include "relay.h"
#include "led.h"

Button buttons[] = {
  Button(P0, MOMENTARY),
  Button(P1, NON_MOMENTARY),
  Button(P2, NON_MOMENTARY),
  Button(P3, MOMENTARY),
  Button(P4, MOMENTARY),
  Button(P5, MOMENTARY),
  Button(P6, MOMENTARY),
  Button(P7, MOMENTARY),
  Button(P8, MOMENTARY)
};

Relay relays[] = {
  Relay(2, HIGH),
  Relay(3, HIGH),
  Relay(4, HIGH),
  Relay(5, HIGH),
  Relay(6, HIGH),
  Relay(7, HIGH),
  Relay(8, HIGH),
  Relay(9, HIGH)
};

Led leds[] = {
  Led(P9)
};

void setup() {
	Serial.begin(115200);

  setupPcf();
  setupButtons();
  setupLeds();
  readButtonsState();
}

void loop() { 
  readButtonsState();

  delay(50);
}

void setupPcf() {
  Serial.println("Init pcf8575...");
  pcf8575.begin();
}

void setupButtons() {
  for (int i = 0; i < BUTTONS_COUNT; i++) {
    buttons[i].setupPin();
  }
}

void setupLeds() {
  for (int i = 0; i < LEDS_COUNT; i++) {
    leds[i].setupPin();
  }
}

void readButtonsState() {  
  for (int i = 0; i < BUTTONS_COUNT; i++) {
    buttons[i].readButtonState(onButtonKeydown, onButtonKeyup, i);
  }
}

void onButtonKeydown(int index) {
  
  Relay *relay = &relays[index];

  if (buttons[index].isMomenatryType() || !relay->isRelayOn()) {
    relays[index].turnOn();

    if (index == 1) {
      leds[0].turnOn();
    }
  } else {
    relays[index].turnOff();

    if (index == 1) {
      leds[0].turnOff();
    }
  }
}

void onButtonKeyup(int index) {
  if (buttons[index].isMomenatryType()) {
    relays[index].turnOff();
  }
}
