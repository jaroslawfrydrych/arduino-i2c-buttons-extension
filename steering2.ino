#include "Arduino.h"
#include "PCF8574.h"

#define BUTTONS_COUNT 8

PCF8574 pcf8574(0x20);

#include "buttontype.enum.h"
#include "button.h"
#include "relay.h"

Button buttons[] = {
  Button(P0, MOMENTARY),
  Button(P1, NON_MOMENTARY),
  Button(P2, NON_MOMENTARY),
  Button(P3, MOMENTARY),
  Button(P4, MOMENTARY),
  Button(P5, MOMENTARY),
  Button(P6, MOMENTARY),
  Button(P7, MOMENTARY)
};

Relay relays[] = {
  Relay(2),
  Relay(3),
  Relay(4),
  Relay(5),
  Relay(6),
  Relay(7),
  Relay(8),
  Relay(9)
};

void setup() {
	Serial.begin(115200);

  setupPcf();
  setupButtons();
  readButtonsState();
}

void loop() { 
  readButtonsState();

  delay(50);
}

void setupPcf() {
  Serial.print("Init pcf8574...");
  if (pcf8574.begin()) {
    Serial.println("OK");
  } else {
    Serial.println("KO");
  }
}

void setupButtons() {
  for (int i = 0; i < BUTTONS_COUNT; i++) {
    buttons[i].setupPin();
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
  } else {
    relays[index].turnOff();
  }
}

void onButtonKeyup(int index) {
  if (buttons[index].isMomenatryType()) {
    relays[index].turnOff();
  }
}
