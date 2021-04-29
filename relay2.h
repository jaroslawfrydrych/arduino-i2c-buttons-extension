class Relay2 {
  private:
    int pin;
    int pcfRelayIndex;
    uint8_t initialState;
    bool isOn;

    void setLow() {
      if (this->pcfRelayIndex == 0) {
        pcfRelays[0].digitalWrite(this->pin, LOW);
      } else {
        pcfRelays[1].digitalWrite(this->pin, LOW);
      }
    }

    void setHigh() {
      if (this->pcfRelayIndex == 0) {
        pcfRelays[0].digitalWrite(this->pin, HIGH);
      } else {
        pcfRelays[1].digitalWrite(this->pin, HIGH);
      }
    }
    
  public:
    Relay2(int pin, int pcfRelayIndex, uint8_t initialState) {
      this->pin = pin;
      this->pcfRelayIndex = pcfRelayIndex;
      this->initialState = initialState;
    }

    void setupPin() {
      pcfRelays[this->pcfRelayIndex].pinMode(this->pin, OUTPUT);

      if (this->initialState == LOW) {
        this->turnOff();
      } else {
        this->turnOn();
      }
    }

    void turnOn() {
      this->isOn = true;
      this->setLow();
    }

    void turnOff() {
      this->isOn = false;
      this->setHigh();
    }

    bool isRelayOn() {
      return this->isOn;
    }
};
