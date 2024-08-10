/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
Funktion: RGB-LED Cube mit Farbwechsel, LED Ring WS2812B und GY-521 3-Achsen-Gyroskop

**************************************************************************************************
Version: 09.08.2024
**************************************************************************************************
Board: LOLIN(WEMOS)D1 R2 & mini
**************************************************************************************************
Libraries:
https://github.com/espressif/arduino-esp32/tree/master/libraries
C:\Users\User\Documents\Arduino

**************************************************************************************************
C++ Arduino IDE V1.8.19
**************************************************************************************************
Einstellungen:
https://dl.espressif.com/dl/package_esp32_index.json
http://dan.drown.org/stm32duino/package_STM32duino_index.json
http://arduino.esp8266.com/stable/package_esp8266com_index.json


Verdrahtung:
ESP8266 GY-521  WS2812B
D1 SCL  SCL
D2 SDA  SDA
D3                IN
+5V     +5V       +5V
GND     GND       GND
**************************************************************************************************/
#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <FastLED.h>

Adafruit_MPU6050 mpu;

float xtreshhold = 0.0;
float ytreshhold = 0.0;
float ztreshhold = 0.0;

#define NUM_LEDS 12
#define DATA_PIN D3

CRGB leds[NUM_LEDS];

void setTreshholds()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  xtreshhold = (a.acceleration.x);
  ytreshhold = (a.acceleration.y);
  ztreshhold = (a.acceleration.z);
}

void setup(void)
{
  Serial.begin(115200);
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (true)
    {
    }
  }
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop()
{

  setTreshholds();

  if (ztreshhold <= -1) // DOWN
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(255, 0, 0); // RED
    }
  }

  else if (ztreshhold >= 1) // UP
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(0, 0, 255); // GREEN
    }
  }

  else if (xtreshhold <= -1) // LEFT
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(0, 255, 0); // BLUE
    }
  }

  else if (xtreshhold >= 1) // RIGHT
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(255, 255, 0); // YELLOW
    }
  }

  else if (ytreshhold <= -1) // FRONT
  {

    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(0, 255, 255); // cyan
    }
  }

  FastLED.setBrightness(20);
  FastLED.show();
}
