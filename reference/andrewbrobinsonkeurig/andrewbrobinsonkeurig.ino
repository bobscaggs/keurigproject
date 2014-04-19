

union send_t {
  struct {
   byte  isOn : 1;
   byte  isEightOzButtonPressed : 1;
   byte  isTenOzButtonPressed : 1;
   byte  isWarmedUp : 1;
   byte  isNeedWater : 1;
   byte  isReadyToBrew : 1;
  };
  byte value;
};
send_t toSend;

int outputCounter = 0;

// Counts toggles, > 3 = READY TO BREW.
int toggleCounter = 0;

// We could use outputCounter to keep track of this value,
// but breaking it out into a separate variable makes it
// a little clearer what exactly is going on.
int toggleTimeCounter = 0;

// The last value, used to determine toggle.
byte lastValue = 0;

void handleOutput() {
  // We want to catch these events no matter what, so we simply
  // AND them with every poll, that way if a button press was detected
  // at any point it's recorded.
  toSend.isEightOzButtonPressed =
    toSend.isEightOzButtonPressed | ((PIND >> 4) & 1);
  toSend.isTenOzButtonPressed =
    toSend.isTenOzButtonPressed | ((PIND >> 5) & 1);

  // We've detected a toggle.
  if(lastValue != ((PIND >> 6) & 1)) {
    // If it's been 500ms - 550ms it's probably the light blinking
    // to symbolize that brewing is ready.
    toggleCounter++;
    toggleTimeCounter = 0;
  }

  // If we've been waiting more than 600ms for a toggle let's give up.
  if(toggleTimeCounter > 600) {
     toggleCounter = 0;
  }

  lastValue = ((PIND >> 6) & 1);

  if(outputCounter % 500 == 0) {
    toSend.isOn = ((PIND >> 3) & 1) ^ 1;
    toSend.isNeedWater = ((PIND >> 7) & 1) ^ 1;
    if(toggleCounter > 3) {
      toSend.isReadyToBrew = 1;
    }

    toSend.isWarmedUp = (lastValue == 0) || toSend.isReadyToBrew || toggleCounter > 0;
    Serial.write(toSend.value);
    toSend.value = 0;
  }
  outputCounter++;
  toggleTimeCounter++;
}
unsigned int commandCounter = 0;

void handleInput() {
  // Here we handle button presses-
  // We simulate a ~200ms press asyncronously
  // to simulate user input. 

  // If commandCounter == 0 we look for UART data,
  // else we block on this specific command and increment
  // up to 200 (~200ms)

  // If a lot of commands were sent at once this would
  // potentially overflow and drop some commands, but
  // I don't think that's a realistic situation.
  if(commandCounter > 0) {
    commandCounter++;
    if(commandCounter == 200) {
      // Set PORTB into high-z state, since the buttons
      // use an analog resistor network we don't want
      // stray current messing with the PIC on the coffee
      // maker
      DDRB = 0;
      // Disable internal pullup resistors
      PORTB = 0;
      // Reset commandCounter
      commandCounter = 0;
    }
  } else if(Serial.available() > 0) {
    switch(Serial.read()) {
      case 'p':
        // Press the power button (Pin 
        PORTB = (1<<0);
        DDRB = (1<<0);
        commandCounter = 1;
      break;
      case 't':
        // Press the 10oz brew button (Pin 9)
        PORTB = (1<<1);
        DDRB = (1<<1);
        commandCounter = 1;
      break;
      case 'e':
        // Press the 8ox brew button (Pin 10)
        PORTB = (1<<2);
        DDRB = (1<<2);
        commandCounter = 1;
      break;
    }
  }
}
void setup() {
  Serial.begin(9600);
}

void loop() {
  handleInput();
  handleOutput();
  delay(1);
}



