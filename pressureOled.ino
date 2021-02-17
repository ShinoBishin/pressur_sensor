#include <DHT_U.h>
#include <DHT.h>

#include <U8g2lib.h>
#include <U8x8lib.h>
#include <SparkFun_LPS25HB_Arduino_Library.h>
#include <Arduino.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE); // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED
// U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/SCL, /* data=*/SDA, /* reset=*/U8X8_PIN_NONE); // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);  // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C
//U8G2_SSD1306_128X32_WINSTAR_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C
//U8G2_SSD1306_64X48_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   // EastRising 0.66" OLED breakout board, Uno: A4=SDA, A5=SCL, 5V powered

LPS25HB pressureSensor;

void setup(void)
{
    u8g2.begin();
    Serial.begin(9600);
    Serial.println("LPS25HB Pressure Sensor Example 1 - Basic Readings");
    Serial.println();

    Wire.begin();
    pressureSensor.begin(); // Begin links an I2C port and I2C address to the sensor, sets an I2C speed, begins I2C on the main board, and then sets default settings

    if (pressureSensor.isConnected() == false) // The library supports some different error codes such as "DISCONNECTED"
    {
        Serial.println("LPS25HB disconnected. Reset the board to try again.");     // Alert the user that the device cannot be reached
        Serial.println("Are you using the right Wire port and I2C address?");      // Suggest possible fixes
        Serial.println("See Example2_I2C_Configuration for how to change these."); // Suggest possible fixes
        Serial.println("");
        while (1)
            ;
    }
}

char pressure[64];
char temp[64];
float a = 1000.0;

void loop(void)
{
    float hpa = pressureSensor.getPressure_hPa();
    float tp = pressureSensor.getTemperature_degC();

    //Serial.print("Pressure in hPa: ");
    Serial.print(pressureSensor.getPressure_hPa()); // Get the pressure reading in hPa
    //Serial.print(", Temperature (degC): ");
    Serial.println(pressureSensor.getTemperature_degC()); // Get the temperature in degrees C

    String str = String(hpa);
    String tmp = String(tp);

    str.toCharArray(pressure, str.length());
    tmp.toCharArray(temp, tmp.length());

    // delay(40); // Wait - 40 ms corresponds to the maximum update rate of the sensor (25 Hz)

    u8g2.clearBuffer();                           // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr);           // choose a suitable font
    u8g2.drawStr(0, 10, "pre:");                  // write something to the internal memory
    u8g2.drawStr(25, 10, pressure);               // write something to the internal memory
    u8g2.drawStr(55, 10, " hpa");                 // write something to the internal memory
    u8g2.drawStr(0, 20, "tmp: ");                 // write something to the internal memory
    u8g2.drawStr(25, 20, temp);                   // write something to the internal memory
    u8g2.drawStr(55, 20, " C");                   // write something to the internal memory
    u8g2.drawStr(0, 30, "Mini Pre Sensor Vol.1"); // write something to the internal memory
    u8g2.sendBuffer();                            // transfer internal memory to the display

    delay(1000);
}
