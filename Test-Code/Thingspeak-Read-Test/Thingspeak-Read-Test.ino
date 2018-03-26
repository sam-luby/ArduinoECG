#include "ThingSpeak.h"
#define USE_WIFI101_SHIELD
#if !defined(USE_WIFI101_SHIELD) && !defined(USE_ETHERNET_SHIELD) && !defined(ARDUINO_SAMD_MKR1000) && !defined(ARDUINO_AVR_YUN) && !defined(ARDUINO_ARCH_ESP8266) && !defined(ARDUINO_ARCH_ESP32)
  #error "Uncomment the #define for either USE_WIFI101_SHIELD or USE_ETHERNET_SHIELD"
#endif

#if defined(ARDUINO_AVR_YUN)
    #include "YunClient.h"
    YunClient client;
#else
  #if defined(USE_WIFI101_SHIELD) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
    // Use WiFi
    #ifdef ARDUINO_ARCH_ESP8266
      #include <ESP8266WiFi.h>
    #elif defined(ARDUINO_ARCH_ESP32)
      #include <WiFi.h>
  #else
      #include <SPI.h>
      #include <WiFi101.h>
    #endif
    char ssid[] = "THE_INTERNET_2GEXT";    //  your network SSID (name) 
    char pass[] = "Nutgrove37";   // your network password
    int status = WL_IDLE_STATUS;
    WiFiClient  client;
  #elif defined(USE_ETHERNET_SHIELD)
    // Use wired ethernet shield
    #include <SPI.h>
    #include <Ethernet.h>
    byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
    EthernetClient client;
  #endif
#endif
  

unsigned long weatherStationChannelNumber = 12397;
unsigned int temperatureFieldNumber = 4;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  ThingSpeak.begin(client);
}

void loop() {
  // Read the latest value from field 4 of channel 12397
  float temperatureInF = ThingSpeak.readFloatField(weatherStationChannelNumber, temperatureFieldNumber);

  Serial.print("Current temp is: "); 
  Serial.print(temperatureInF);
  Serial.println(" degrees F"); 

  delay(30000); // Note that the weather station only updates once a minute
}


