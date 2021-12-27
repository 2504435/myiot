#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h> 

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

const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80
const char fingerprint[] PROGMEM = "62 f8 bd 9a 9f 24 0c d5 58 3e 6c 26 39 3b 29 5b b4 a3 48 a6";

// REPLACE with your Domain name and URL path or IP address with path
const char* serverPath = "/phpScript/insertData.php";
const char* host = "192.168.1.1";

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
    // WiFiClient client;
    WiFiClientSecure httpsClient;    //Declare object of class WiFiClient
    
    Serial.println(host);

    Serial.printf("Using fingerprint '%s'\n", fingerprint);
    httpsClient.setFingerprint(fingerprint);
    httpsClient.setTimeout(15000); // 15 Seconds
    delay(1000);
      
    Serial.println("HTTPS Connecting");
    int r=0; //retry counter
    while((!httpsClient.connect(host, httpsPort)) && (r < 30)){
        delay(100);
        Serial.print(".");
        r++;
    }
    if(r==30) {
      Serial.println("Connection failed");
    }
    else {
      Serial.println("Connected to web");
    }
    // Prepare your HTTP POST request data
    String httpsRequest = String(serverPath) + "?api_key=" + apiKeyValue + "&sensor=" + sensorName
                          + "&location=" + sensorLocation + "&temp=" + String(t, 2)
                          + "&humid=" + String(h, 2) + "";
    Serial.print("requestHeader: ");
    Serial.println(httpsRequest);
    
    httpsClient.print(String("GET ") + httpsRequest + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +               
                "Connection: close\r\n\r\n");

    Serial.println("Get packet detail : ");
    Serial.println(String("GET ") + httpsRequest + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +               
                "Connection: close\r\n\r\n");
    Serial.println("request sent");
        
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
