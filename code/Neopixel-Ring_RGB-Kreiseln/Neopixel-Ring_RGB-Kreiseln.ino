/************************************************************************************************* 
                                      PROGRAMMINFO
************************************************************************************************** 
Funktion: NEO-Pixel-Ring

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

// Parameter 1 = Anzahl der Pixel im Streifen
// Parameter 2 = Arduino Pin-Nummer
// Parameter 3 = Pixeltyp-Flags:
//   NEO_KHZ800  800 KHz bitstream (die meisten NeoPixel Produkte mit WS2812 LEDs)
//   NEO_KHZ400  400 KHz (klassische 'v1' (nicht v2) FLORA Pixel, WS2811 Treiber)
//   NEO_GRB     Pixel sind für GRB-Bitstream (die meisten NeoPixel-Produkte) verdrahtet
//   NEO_RGB     Pixel sind für RGB-Bitstream verdrahtet (v1 FLORA-Pixel, nicht v2)
//   NEO_RGBW    Pixel sind für RGBW-Bitstream (NeoPixel RGBW-Produkte) verdrahtet
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// WICHTIG: Um das NeoPixel-Burnout-Risiko zu reduzieren, fügen Sie 1000 uF-Kondensatoren
// Pixel-Power-Leads, fügen Sie 300 - 500 Ohm Widerstand auf der ersten Pixel Data Input

void setup() {
  // Dies ist für Trinket 5V 16MHz, können Sie diese drei Zeilen entfernen, wenn Sie kein Trinket verwenden
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialisieren Sie alle Pixel auf "aus"
}

void loop() {
  // Einige Beispielverfahren, die zeigen, wie den Pixeln angezeigt wird:
  colorWipe(strip.Color(255, 0, 0), 50); // Rot
  colorWipe(strip.Color(0, 255, 0), 50); // Grün
  colorWipe(strip.Color(0, 0, 255), 50); // Blau
//colorWipe(strip.Color(0, 0, 0, 255), 50); // Weis RGBW
}

// Füllen Sie die Punkte nacheinander mit einer Farbe
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}





//Theater-Stil Kriechlichter mit Regenbogen-Effekt
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Geben Sie einen Wert 0 bis 255 ein, um einen Farbwert zu erhalten.
// Die Farben sind ein Übergang r - g - b - zurück zu r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
