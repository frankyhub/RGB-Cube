/************************************************************************************************* 
                                      PROGRAMMINFO
************************************************************************************************** 
Funktion: NEO-Pixel-Ring Rot/Weis Warnlicht

**************************************************************************************************
Version: 06.05.2021
**************************************************************************************************
Board: NANO
NEOPIXEL Ring – 16 Pixel – RGB LED W/integrierten Treibern Amazon 16,99€
6Bit RGB LED Ring WS2812 5V ähnl. Neopixel Ebay 2€ Verkäufer fandigist
**************************************************************************************************
C++ Arduino IDE V1.8.13
**************************************************************************************************
Einstellungen:
https://dl.espressif.com/dl/package_esp32_index.json
http://dan.drown.org/stm32duino/package_STM32duino_index.json
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json
**************************************************************************************************
Librarys
- Adafruit_NeoPixel.h V 1.7.0
**************************************************************************************************

 **************************************************************************************************/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NUMPIXELS 16
#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // alle Pixel auf "aus"
}

void loop() {

  // Pixel Kreisel:
  theaterChase(strip.Color(127, 127, 127), 20); // Weiß
  theaterChase(strip.Color(127, 0, 0), 50); // Rot
// theaterChase(strip.Color(0, 0, 127), 50); // Blau
//    theaterChase(strip.Color(0, 127, 127), 50); // Türkis
}

//LED Umlauf
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<5; j++) {  //Wechsel nach 3 Runden
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //jeder 3 Pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //jeder 3 Pixel off
      }
    }
  }
}
