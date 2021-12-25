// Control OLED by NodeMCU ESP8266
#include <Wire.h>
#include <SH1106.h>
// DHT11
#include "DHT.h"
#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//SSD1306 display(Addr,SDA,SCL);
SH1106 display(0x3c, D1, D2);
void setup() {
  Serial.begin (9600);
  dht.begin();
  display.init();
}
void loop() {
  float h = dht.readHumidity();             //รับค่าความชื้น
  float t = dht.readTemperature();          //รับค่าอุณหภูมิ
  Serial.println("Temp = "+String(t,1)+" C");
  Serial.println("Humi = "+String(h,1)+" %");
  display.setFont(ArialMT_Plain_10);
  display.clear();
  display.drawString(25, 0, "Temp = ");
  display.drawString(75, 0, String(t, 1)+" C");
  display.drawString(25, 10, "Humid = ");
  display.drawString(75, 10, String(h, 1)+" %");
  display.display();
  delay(1000);

}
