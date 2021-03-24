class Button {
  private:
    int pin;
    bool pressed;
    buttonType type;
    uint8_t lastReading = LOW;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;

    uint8_t readingValue() {
      return pcf8575.digitalRead(this->pin);
    }

    bool isPinHigh(uint8_t value) {
      return value == HIGH;
    }
    
  public:
    Button(int pin, buttonType type) {
      this->pin = pin;
      this->type = type;
    }

    void readButtonState(void (*callbackOnKeydown)(int callbackOnKeydownParam),
                         void (*callbackOnKeyup)(int callbackOnKeyupParam),
                         int callbacksParam) {
      uint8_t reading = this->readingValue();
      
      if (this->isPinHigh(reading)) {
        this->keydown(callbackOnKeydown, callbacksParam);
      } else {
        this->keyup(callbackOnKeyup, callbacksParam);
      }
    }

    void setupPin() {
      pcf8575.pinMode(this->pin, INPUT);
    }

    void keydown(void (*callback)(int callbackParam), int callbackParam) {
      if (this->pressed) {
        return;
      }

      this->pressed = true;
      callback(callbackParam);
    }

    void keyup(void (*callback)(int callbackParam), int callbackParam) {

      if (!this->pressed) {
        return;
      }
      
      this->pressed = false;
      callback(callbackParam);
    }

    bool isMomenatryType() {
      return this->type == MOMENTARY;
    }
};
