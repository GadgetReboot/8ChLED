// 8 Ch LED Indicator
// Uses ATTiny804 and 8 SK6812 mini LEDs
//
// 8 digital GPIO inputs are read and their high/low states are displayed on the LEDs
//
// Tested with      Arduino IDE              1.8.13
//                  megaTinyCore Board file  2.5.10
//
// ATTiny804 pin map for Arduino sketches https://github.com/SpenceKonde/megaTinyCore/blob/master/megaavr/extras/ATtiny_x04.md
//
// Gadget Reboot
// https://www.youtube.com/@gadgetreboot

#include <tinyNeoPixel_Static.h>  // part of the megatinecore board file
#include <Bounce2.h>              // debounce https://github.com/thomasfredericks/Bounce2

#define dataPin   7               // ATTiny804 PB0 is Arduino pin 7 (see megaTinyCore on Github)
#define cfgPin    5               // ATTiny804 PB2 is Arduino pin 5
#define modePin   4               // ATTiny804 PB3 is Arduino pin 4
#define input1    6               // ATTiny804 PB1 is Arduino pin 6
#define input2    3               // ATTiny804 PA7 is Arduino pin 3
#define input3    2               // ATTiny804 PA6 is Arduino pin 2
#define input4    1               // ATTiny804 PA5 is Arduino pin 1
#define input5    0               // ATTiny804 PA4 is Arduino pin 0
#define input6    10              // ATTiny804 PA3 is Arduino pin 10
#define input7    9               // ATTiny804 PA2 is Arduino pin 9
#define input8    8               // ATTiny804 PA1 is Arduino pin 8

const byte NUMPIXELS = 8;         // pcb has 8 SK6812 LEDs
byte pixels[NUMPIXELS * 3];

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
// Parameter 4 = array to store pixel data in

tinyNeoPixel leds = tinyNeoPixel(NUMPIXELS, dataPin, NEO_GRB, pixels);

Bounce buttonDebouncer = Bounce();  // debouncer for mode button

uint32_t assertColor = leds.Color(0, 5, 0);    // green led = input pin asserted
uint32_t nAssertColor = leds.Color(15, 0, 0);  //   red led = input pin not asserted
uint32_t ledOff = leds.Color(0, 0, 0);         //   off led = RGB brightness 0

// define the modes of operation to cycle through when mode button is pressed
enum modes {
  ledDemo,                   // show a demo led pattern
  showAssertedOnly,          // only turn on an led when the input has been asserted
  showAllStates              // show the asserted or un-asserted state on the led
};

enum modes currMode = showAssertedOnly;  // default to only turning on an led if input is asserted

void setup() {
  pinMode(cfgPin, INPUT_PULLUP);   // config input pin
  pinMode(modePin, INPUT_PULLUP);  // mode input pin
  pinMode(dataPin, OUTPUT);        // LED data output pin
  pinMode(input1, INPUT);          // inputs have external pull ups
  pinMode(input2, INPUT);
  pinMode(input3, INPUT);
  pinMode(input4, INPUT);
  pinMode(input5, INPUT);
  pinMode(input6, INPUT);
  pinMode(input7, INPUT);
  pinMode(input8, INPUT);

  buttonDebouncer.attach(modePin);  // mode button debouncer
  buttonDebouncer.interval(30);     // interval in ms

  leds.show();                      // initialize all LEDs to 'off'
}

void loop() {
  boolean checkMode = modePinPressed();   // check if mode button was pressed and change modes if so

  if (currMode == ledDemo) ledDemoRun();  // run through some led demo routines
  readInputs();                           // check inputs and set leds
}

// check if mode pin has been pressed and change the mode
boolean modePinPressed() {
  buttonDebouncer.update();
  if (buttonDebouncer.fell()) {    // cycle through modes if button is pressed, wrapping around to the first mode after the final mode
    currMode = currMode + 1;
    if (currMode > 2) currMode = 0;
    return true;
  }
  return false;
}

void readInputs() {
  boolean activeMode = digitalRead(cfgPin);  // check if inputs are asserted as active high or low
  uint32_t ledColor;                         // assign the led color to use based on input readings

  boolean led1State = digitalRead(input1);   // read inputs to decide how leds should appear
  boolean led2State = digitalRead(input2);
  boolean led3State = digitalRead(input3);
  boolean led4State = digitalRead(input4);
  boolean led5State = digitalRead(input5);
  boolean led6State = digitalRead(input6);
  boolean led7State = digitalRead(input7);
  boolean led8State = digitalRead(input8);

  // set led colors based on whether each input is asserted or not
  if (led1State == activeMode) ledColor = assertColor;
  else {
    if (currMode == showAllStates) ledColor = nAssertColor;
    else {
      if (currMode == showAssertedOnly) ledColor = ledOff;
    }
  }
  leds.setPixelColor(0, ledColor);

  if (led2State == activeMode) ledColor = assertColor;
  else {
    if (currMode == showAllStates) ledColor = nAssertColor;
    else {
      if (currMode == showAssertedOnly) ledColor = ledOff;
    }
  }
  leds.setPixelColor(1, ledColor);

  if (led3State == activeMode) ledColor = assertColor;
  else {
    if (currMode == showAllStates) ledColor = nAssertColor;
    else {
      if (currMode == showAssertedOnly) ledColor = ledOff;
    }
  }
  leds.setPixelColor(2, ledColor);

  if (led4State == activeMode) ledColor = assertColor;
  else {
    if (currMode == showAllStates) ledColor = nAssertColor;
    else {
      if (currMode == showAssertedOnly) ledColor = ledOff;
    }
  }
  leds.setPixelColor(3, ledColor);

  if (led5State == activeMode) ledColor = assertColor;
  else {
    if (currMode == showAllStates) ledColor = nAssertColor;
    else {
      if (currMode == showAssertedOnly) ledColor = ledOff;
    }
  }
  leds.setPixelColor(4, ledColor);

  if (led6State == activeMode) ledColor = assertColor;
  else {
    if (currMode == showAllStates) ledColor = nAssertColor;
    else {
      if (currMode == showAssertedOnly) ledColor = ledOff;
    }
  }
  leds.setPixelColor(5, ledColor);

  if (led7State == activeMode) ledColor = assertColor;
  else {
    if (currMode == showAllStates) ledColor = nAssertColor;
    else {
      if (currMode == showAssertedOnly) ledColor = ledOff;
    }
  }
  leds.setPixelColor(6, ledColor);

  if (led8State == activeMode) ledColor = assertColor;
  else {
    if (currMode == showAllStates) ledColor = nAssertColor;
    else {
      if (currMode == showAssertedOnly) ledColor = ledOff;
    }
  }
  leds.setPixelColor(7, ledColor);

  leds.show();  // update leds with current color scheme
}

void ledDemoRun() {
  // Some example procedures showing how to display to the pixels:
  colorWipe(leds.Color(255, 0, 0), 50); // Red
  colorWipe(leds.Color(0, 255, 0), 50); // Green
  colorWipe(leds.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  theaterChase(leds.Color(127, 127, 127), 50); // White
  theaterChase(leds.Color(127, 0, 0), 50); // Red
  theaterChase(leds.Color(0, 0, 127), 50); // Blue

  //  rainbow(20);
  //  rainbowCycle(20);
  //  theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  if (currMode == ledDemo) {
    for (uint16_t i = 0; i < leds.numPixels(); i++) {
      if (modePinPressed()) break;
      leds.setPixelColor(i, c);
      leds.show();
      delay(wait);
    }
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;
  if (currMode == ledDemo) {
    for (j = 0; j < 256; j++) {
      if (modePinPressed()) break;
      for (i = 0; i < leds.numPixels(); i++) {
        leds.setPixelColor(i, Wheel((i + j) & 255));
      }
      leds.show();
      delay(wait);
    }
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  if (currMode == ledDemo) {
    for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
      if (modePinPressed()) break;
      for (i = 0; i < leds.numPixels(); i++) {
        leds.setPixelColor(i, Wheel(((i * 256 / leds.numPixels()) + j) & 255));
      }
      leds.show();
      delay(wait);
    }
  }
}

// Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  if (currMode == ledDemo) {
    for (int j = 0; j < 10; j++) { // do 10 cycles of chasing
      if (modePinPressed()) break;
      if (currMode == ledDemo) for (int q = 0; q < 3; q++) {
          if (modePinPressed()) break;
          if (currMode == ledDemo) for (uint16_t i = 0; i < leds.numPixels(); i = i + 3) {
              if (modePinPressed()) break;
              leds.setPixelColor(i + q, c);  // turn every third pixel on
            }
          leds.show();

          delay(wait);

          if (currMode == ledDemo) for (uint16_t i = 0; i < leds.numPixels(); i = i + 3) {
              if (modePinPressed()) break;
              leds.setPixelColor(i + q, 0);      // turn every third pixel off
            }
        }
    }
  }
}

// Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  if (currMode == ledDemo) {
    for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
      if (modePinPressed()) break;
      for (int q = 0; q < 3; q++) {
        for (uint16_t i = 0; i < leds.numPixels(); i = i + 3) {
          leds.setPixelColor(i + q, Wheel((i + j) % 255)); // turn every third pixel on
        }
        leds.show();

        delay(wait);

        for (uint16_t i = 0; i < leds.numPixels(); i = i + 3) {
          leds.setPixelColor(i + q, 0);      // turn every third pixel off
        }
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return leds.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return leds.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return leds.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
