class Led {
  private:
    int pin;
    
  public:
    Led(int pin) {
      this->pin = pin;
    }

    void setupPin() {
      pcf8575.pinMode(this->pin, OUTPUT);
      this->turnOff();
    }

    void turnOn() {
      pcf8575.digitalWrite(this->pin, LOW); 
    }

    void turnOff() {
      pcf8575.digitalWrite(this->pin, HIGH);
    }
};
