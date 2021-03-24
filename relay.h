class Relay {
  private:
    int pin;
    bool isOn;
    uint8_t initialState;

    void setupPins() {
      pinMode(this->pin, OUTPUT);

      this->turnOffRelay();
    }

    void turnOffRelay() {
      if (this->initialState == HIGH) {
        digitalWrite(this->pin, HIGH);
      } else {
        digitalWrite(this->pin, LOW);
      }
    }

    void turnOnRelay() {      
      if (this->initialState == HIGH) {
        digitalWrite(this->pin, LOW);
      } else {
        digitalWrite(this->pin, HIGH);
      }
    }
    
  public:
    Relay(int pin, uint8_t initialState) {
      this->pin = pin;
      this->initialState = initialState;
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
