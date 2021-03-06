#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <SoftwareSerial.h>   // We need this even if we're not using a SoftwareSerial object
                              // Due to the way the Arduino IDE compiles


#define PIN 5
//#define PIN2 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(160, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(160, PIN2, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

uint32_t A = strip.Color(255, 0, 0);
uint32_t B = strip.Color(0, 255, 0);
uint32_t C = strip.Color(0, 0, 255);
uint32_t D = strip.Color(0, 0, 0, 255);
uint32_t E = strip.Color(127, 127, 127);
uint32_t F = strip.Color(127, 0, 0);
uint32_t G = strip.Color(0, 0, 127);
uint32_t H = 20;
uint32_t I = 50;

uint32_t a = 50;
uint32_t b = 30;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  Serial.begin(9600);
  Serial.println("Ready");

  strip.begin(); // Initialize all pixels to 'off'
  strip2.begin();
  strip.show();
  strip2.show();
}

void loop() {
  
  char inByte = ' ';
  if(Serial.available()){ // only send back dataif data has been sent 
    char inByte = Serial.read(); // read the incoming data
    Serial.println(inByte); // send the data back in a new line so that it is not all one line
  }
  delay(120); //delay
  
////  // Some example procedures showing how to display to the pixels:
//uint32_t A = strip.Color(255, 0, 0);
//uint32_t B = strip.Color(0, 255, 0);
//uint32_t C = strip.Color(0, 0, 255);
//uint32_t D = strip.Color(0, 0, 0, 255);
//
//uint32_t a = 50;
//uint32_t b = 30;
//
//colorWipe(A, a); // Red
////colorWipe(B, a); // Green
////colorWipe(C, a); // Blue
////colorWipe(D, a); // White RGBW
//
//////Send a theater pixel chase in...
//uint32_t E = strip.Color(127, 127, 127);
//uint32_t F = strip.Color(127, 0, 0);
//uint32_t G = strip.Color(0, 0, 127);
//
////theaterChase(E, a); // White
////theaterChase(F, a); // Red
////theaterChase(G, a); // Blue

//// Rainbow options 
//uint32_t H = 20;
//uint32_t I = 50;

//rainbow(H);
//rainbowCycle(H);
//theaterChaseRainbow(I);
//
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    strip2.setPixelColor(i, c);
    strip2.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
     // strip2.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    //strip2.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      strip2.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    strip2.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);
        strip2.setPixelColor(i+q, c);//turn every third pixel on
      }
      strip.show();
      strip2.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);
        strip2.setPixelColor(i+q, 0);  //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255)); 
        strip2.setPixelColor(i+q, Wheel( (i+j) % 255));  //turn every third pixel on
      }
      strip.show();
      strip2.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
        strip2.setPixelColor(i+q, 0);
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    return strip2.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    return strip2.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  return strip2.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void unrecognized()
{
  Serial.println("What?"); 
}

