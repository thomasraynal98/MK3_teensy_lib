#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN1 13
// #define PIN2 22
// #define PIN3 23

#define NUM 300 // CORRESPOND AU NOMBRE DE LED QUI S'ALLUME
// #define NUM3 34

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM, PIN1, NEO_GRB + NEO_KHZ800);
// Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM, PIN2, NEO_GRB + NEO_KHZ800);
// Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUM3, PIN3, NEO_GRB + NEO_KHZ800);


// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip1.begin();
  // strip2.begin();
  // strip3.begin();
  strip1.setBrightness(100);
  // strip2.setBrightness(50);
  // strip3.setBrightness(50);
  strip1.show(); // Initialize all pixels to 'off'
  // strip2.show();
  // strip3.show();
}

// Fill the dots one after the other with a color
void warning(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip1.numPixels(); i++) {
    strip1.setPixelColor(i, c);
    // strip2.setPixelColor(i, c);
    strip1.show();
    // strip2.show();
    delay(wait);
  }
}

// Fill the dots one after the other with a color
// void right(uint32_t c, uint8_t wait) {
//   for(uint16_t i=0; i<strip2.numPixels(); i++) {
//     strip2.setPixelColor(i, c);
//     strip2.show();
//     delay(wait);
//   }
// }

// Fill the dots one after the other with a color
// void left(uint32_t c, uint8_t wait) {
//   for(uint16_t i=0; i<strip1.numPixels(); i++) {
//     strip1.setPixelColor(i, c);
//     strip1.show();
//     delay(wait);
//   }
// }


// void static1(int r, int g, int b)
// {
//   for(int i=0;i<=NUM3;i++)
//   {
//     strip3.setPixelColor(i, strip3.Color(r,g,b));
//     strip3.show();
//   }
// }

void loop() {
  // Some example procedures showing how to display to the pixels:
  
  warning(strip1.Color(255, 69, 0), 10); // orange
  warning(strip1.Color(0, 0, 0), 10); // orange

  // right(strip2.Color(255, 69, 0), 100); // orange
  // right(strip2.Color(0, 0, 0), 100); // orange

  // left(strip1.Color(255, 69, 0), 100); // orange
  // left(strip1.Color(0, 0, 0), 100); // orange

  // static1(255, 0, 0);

  // theaterChase(255, 0, 0, 100);
}