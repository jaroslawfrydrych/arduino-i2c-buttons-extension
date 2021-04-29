class Led {
  private:
    int pin;
    
  public:
    Led(int pin) {
      this->pin = pin;
    }

    void setupPin() {
      pcfSteering.pinMode(this->pin, OUTPUT);
      this->turnOff();
    }

    void turnOn() {
      pcfSteering.digitalWrite(this->pin, LOW); 
    }

    void turnOff() {
      pcfSteering.digitalWrite(this->pin, HIGH);
    }
};
