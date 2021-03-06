#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// Control OLED by NodeMCU ESP8266
#include <Wire.h>
#include <SH1106.h>
// DHT11
#include "DHT.h"
#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//SSD1306 display(Addr,SCL,SDA);
SH1106 display(0x3c, D1, D2);

// Replace with your network credentials
const char* ssid     = "surapong_2g";
const char* password = "champ2231";
// Set your Static IP address
IPAddress local_IP(192, 168, 1, 2);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 254);

IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://192.168.1.1/phpScript/insertData.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9";

String sensorName = "DHT11";
String sensorLocation = "myHome";

void setup() {
  Serial.begin(9600);
  dht.begin();
  display.init();

  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  // dht_oled 

}

void loop() {
  // dht_oled

  float h = dht.readHumidity();             
  float t = dht.readTemperature(); 
  if(!isnan(t) && !isnan(h)){
  
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

  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    
    // Prepare your HTTP POST request data
    String httpRequestData = String(serverName) + "?api_key=" + apiKeyValue + "&sensor=" + sensorName
                          + "&location=" + sensorLocation + "&temp=" + String(t, 2)
                          + "&humid=" + String(h, 2) + "";
    Serial.print("httprequestdata: ");
    Serial.println(httpRequestData);
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, httpRequestData);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // you can comment the httprequestdata variable above
    // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)
    //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";

    // Send HTTP GET request
    int httpResponseCode = http.GET();
     
    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
    
    // If you need an HTTP request with a content type: application/json, use the following:
    //http.addHeader("Content-Type", "application/json");
    //int httpResponseCode = http.POST("{\"value1\":\"19\",\"value2\":\"67\",\"value3\":\"78\"}");
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds
  delay(30000);  
  }
  delay(1000);
  Serial.println("begin loop F");
}
