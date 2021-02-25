#include <MsTimer2.h>
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

LPS25HB pressureSensor;

void print_data(void);

void setup(void)
{
    u8g2.begin();
    Serial.begin(9600);
    Wire.begin();
    pressureSensor.begin();
    MsTimer2::set(300000, print_data);
    MsTimer2::start();
}

char pressure[64];
char temp[64];
float hpa;
float tp;

void loop(void)
{
    hpa = pressureSensor.getPressure_hPa();
    tp = pressureSensor.getTemperature_degC();

    // Serial.print(hpa);
    // Serial.print(", ");
    // Serial.println(tp);

    String str = String(hpa);
    String tmp = String(tp);

    str.toCharArray(pressure, str.length());
    tmp.toCharArray(temp, tmp.length());

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 10, "pre:");
    u8g2.drawStr(25, 10, pressure);
    u8g2.drawStr(55, 10, " hpa");
    u8g2.drawStr(0, 20, "tmp: ");
    u8g2.drawStr(25, 20, temp);
    u8g2.drawStr(55, 20, " C");
    u8g2.drawStr(0, 30, "Mini Pre Sensor Vol.1");
    u8g2.sendBuffer();

    delay(1000);
}

void print_data(void)
{
    Serial.print(hpa);
    Serial.print(", ");
    Serial.println(tp);
}