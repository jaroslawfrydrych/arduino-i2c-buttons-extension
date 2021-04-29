#include "Arduino.h"
#include "PCF8575.h"
#include "PCF8574.h"

#define BUTTONS_COUNT 9
#define LEDS_COUNT 5

PCF8575 pcfSteering(0x21);
PCF8574 pcfRelay1(0x3E);
PCF8574 pcfRelay2(0x38);

PCF8574 pcfRelays[] = {
  pcfRelay1,
  pcfRelay2
};


#include "buttontype.enum.h"
#include "button.h"
#include "relay.h"
#include "relay2.h"
#include "led.h"

Button buttons[] = {
  Button(8, MOMENTARY),
  Button(9, MOMENTARY),
  Button(10, MOMENTARY),
  Button(11, MOMENTARY),
  Button(12, MOMENTARY),
  Button(13, MOMENTARY),
  Button(14, MOMENTARY),
  Button(15, MOMENTARY)
};

Relay2 relays[] = {
  Relay2(P1, 0, LOW),
//  Relay(P2, LOW, 0),
//  Relay(P3, LOW, 0),
//  Relay(P4, LOW, 0),
//  Relay(P1, LOW, 1),
//  Relay(P2, LOW, 1),
//  Relay(P3, LOW, 1),
//  Relay(P4, LOW, 1)
};

Led leds[] = {
  Led(P0),
  Led(P2),
  Led(P3),
  Led(P4),
  Led(P5)
};

void setup() {
	Serial.begin(115200);

  pinMode(A3, OUTPUT);  // sets the pin as output
  analogWrite(A3, 120);

  setupPcf();
  setupButtons();
  setupLeds();
  readButtonsState();
  setupRelays();

//  pcfSteering.pinMode(P0, OUTPUT);
//  pcfSteering.digitalWrite(P0, HIGH);
}

void loop() { 
  readButtonsState();

  delay(50);
}

void setupPcf() {
  Serial.println("Starting RACING CONTROLLER PRO...");
  pcfSteering.begin();
//  pcfRelays[0].begin();
//  pcfRelays[1].begin();
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

void setupRelays() {
  for (int i = 1; i <= 4; i++) {
    relays[i].setupPin();
//    pcfRelays[0].pinMode(i, OUTPUT);
//    pcfRelays[0].digitalWrite(i, HIGH);
    
//    pcfRelays[1].pinMode(i, OUTPUT);
//    pcfRelays[1].digitalWrite(i, HIGH);
  }
}

void readButtonsState() {
  for (int i = 0; i < BUTTONS_COUNT; i++) {
    buttons[i].readButtonState(onButtonKeydown, onButtonKeyup, i);
  }
}

/*
 * Keydowns
 */

void onButton0Keydown() {
  Serial.print("Button pressed ");
  Serial.println("0");
  pcfRelays[0].digitalWrite(1, LOW);
  pcfSteering.digitalWrite(1, LOW);
//  relays[0].turnOn();
}

void onButton1Keydown() {
  Serial.print("Button pressed ");
  Serial.println("1");
//  relays[1].turnOn();
}

void onButton2Keydown() {
  Serial.print("Button pressed ");
  Serial.println("2");
  leds[4].turnOn();
//  relays[2].turnOn();
}

void onButton3Keydown() {
  Serial.print("Button pressed ");
  Serial.println("3");
  leds[3].turnOn();
//  relays[3].turnOn();
}

void onButton4Keydown() {
  Serial.print("Button pressed ");
  Serial.println("4");
  pcfRelays[0].digitalWrite(1, LOW);
  leds[2].turnOn();
//  relays[4].turnOn();
}

void onButton5Keydown() {
  Serial.print("Button pressed ");
  Serial.println("5");
  leds[1].turnOn();
//  relays[5].turnOn();
}

void onButton6Keydown() {
  Serial.print("Button pressed ");
  Serial.println("6");
//  relays[6].turnOn();
}

void onButton7Keydown() {
  Serial.print("Button pressed ");
  Serial.println("7");
  leds[0].turnOn();
//  relays[7].turnOn();
}


/*
 * Keyups
 */

void onButton0Keyup() {
  pcfSteering.digitalWrite(1, HIGH);
//  relays[0].turnOff();
}

void onButton1Keyup() {
//  relays[1].turnOff();
}

void onButton2Keyup() {
//  relays[2].turnOff();
  leds[4].turnOff();
}

void onButton3Keyup() {
  leds[3].turnOff();
//  relays[3].turnOff();
}

void onButton4Keyup() {
  pcfRelays[0].digitalWrite(1, HIGH);
  leds[2].turnOff();
//  relays[4].turnOff();
}

void onButton5Keyup() {
//  relays[5].turnOff();
  leds[1].turnOff();
}

void onButton6Keyup() {
//  relays[6].turnOff();
}

void onButton7Keyup() {
//  relays[7].turnOff();
  leds[0].turnOff();
}

/*
 * Mapping
 */
 
void onButtonKeydown(int index) {
  switch (index) {
    case 0:
      onButton0Keydown();
      break;
      
    case 1:
      onButton1Keydown();
      break;
      
    case 2:
      onButton2Keydown();
      break;
      
    case 3:
      onButton3Keydown();
      break;
      
    case 4:
      onButton4Keydown();
      break;
      
    case 5:
      onButton5Keydown();
      break;
      
    case 6:
      onButton6Keydown();
      break;
      
    case 7:
      onButton7Keydown();
      break;
  }
}

void onButtonKeyup(int index) {

  switch (index) {
    case 0:
      onButton0Keyup();
      break;
      
    case 1:
      onButton1Keyup();
      break;
      
    case 2:
      onButton2Keyup();
      break;
      
    case 3:
      onButton3Keyup();
      break;
      
    case 4:
      onButton4Keyup();
      break;
      
    case 5:
      onButton5Keyup();
      break;
      
    case 6:
      onButton6Keyup();
      break;
      
    case 7:
      onButton7Keyup();
      break;
  }
}
