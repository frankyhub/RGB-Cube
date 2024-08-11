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
//**************MPU6050*******************************************************
#include "Wire.h" 
#define MPU6050_ADDR 0x68 // Alternatively set AD0 to HIGH  --> Address = 0x69
int16_t accX, accY, accZ, gyroX, gyroY, gyroZ, tRaw; // Raw register values (accelaration, gyroscope, temperature)
char result[7]; // temporary variable used in convert function
//***************************************************************************

//************************WS2812B********************************************
//#include <Arduino.h>
//#include <Adafruit_MPU6050.h>
//#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <FastLED.h>
#define NUM_LEDS 12
#define DATA_PIN D3
CRGB leds[NUM_LEDS];
//***************************************************************************

void setup() {

  //**************MPU6050*******************************************************
  Serial.begin(115000);
  Wire.begin();
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // wake up!
  Wire.endTransmission(true);
//***************************************************************************

  //**************WS2812*******************************************************
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
 //***************************************************************************
}


void loop() {

  //**************MPU6050*******************************************************  
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. 
                               // As a result, the connection is kept active.
  Wire.requestFrom(MPU6050_ADDR, 14, true); // request a total of 7*2=14 registers

 
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same int16_t variable
  accX = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accY = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accZ = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  tRaw = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyroX = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyroY = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyroZ = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
  
  Serial.print("AcX = "); Serial.print(toStr(accX));
  Serial.print(" | AcY = "); Serial.print(toStr(accY));
  Serial.print(" | AcZ = "); Serial.print(toStr(accZ));
  // from data sheet:
  Serial.print(" | tmp = "); Serial.print((tRaw + 12412.0) / 340.0);
  Serial.print(" | GyX = "); Serial.print(toStr(gyroX));
  Serial.print(" | GyY = "); Serial.print(toStr(gyroY));
  Serial.print(" | GyZ = "); Serial.print(toStr(gyroZ));
  Serial.println();
//***************************************************************************

//************** MPU6050 ******************************************************* 
 if (accY <= 300 && accY >= 10 && accZ >8000) // gerade
  {

    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(0, 255, 255); // cyan
    }
  }

  else if (accX <= 700 && accY >= 2000 && accZ >8000) // links
  {

    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(0, 255, 0); // grün
    }
  } 

  else if (accX < 10  && accY <10 && accZ >8000) // rechts
  {

    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(255, 255, 0); // gelb
    }
  }   

    else if (accX < 10  && accY <10 && accZ <8000) // vorne
  {

    for (int i = 0; i < NUM_LEDS; i++)
    {
      leds[i].setRGB(255, 0, 0); // rot

    }
  }
//***************************************************************************
  FastLED.setBrightness(20);
  FastLED.show();


  
  delay(500);
}

//***************************************************************************
//***************************************************************************

//**************MPU6050******************************************************* 
char* toStr(int16_t character) { // converts int16 to string and formatting
  sprintf(result, "%6d", character);
  return result;
}
//***************************************************************************
