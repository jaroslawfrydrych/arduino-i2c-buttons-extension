#include "PCF8574.h"

/*
 * @deprecated
 */
class Relay {
  private:
    int pin;
    bool isOn;
    uint8_t initialState;
    int pcfRelayIndex;
    
    void setupPins() {
      pinMode(this->pin, OUTPUT);

      this->turnOffRelay();
    }

    void turnOffRelay() {
      if (this->initialState == HIGH) {
        pcfRelays[this->pcfRelayIndex].digitalWrite(this->pin, HIGH);
      } else {
        pcfRelays[this->pcfRelayIndex].digitalWrite(this->pin, LOW);
      }
    }

    void turnOnRelay() {      
      if (this->initialState == HIGH) {
        pcfRelays[this->pcfRelayIndex].digitalWrite(this->pin, LOW);
      } else {
        pcfRelays[this->pcfRelayIndex].digitalWrite(this->pin, HIGH);
      }
    }
    
  public:
    Relay(int pin, uint8_t initialState, int pcfRelayIndex) {
      this->pin = pin;
      this->initialState = initialState;
      this->pcfRelayIndex = pcfRelayIndex;
      this->setupPins();
    }

    void turnOn() {
      this->isOn = true;
      this->turnOnRelay();
    }

    void turnOff() {
      this->isOn = false;
      this->turnOffRelay();
    }

    bool isRelayOn() {
      return this->isOn;
    }
};
