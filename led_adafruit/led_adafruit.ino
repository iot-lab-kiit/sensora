#include <ESP8266WiFi.h> // use ESP8266Wifi.h for nodemcu
#include <WiFiClient.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//Defining necessary constants
#define WLAN_SSID       "ssid"
#define WLAN_PASS       "pass"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   
#define AIO_USERNAME    "username" // put your adafruit user id
#define AIO_KEY         "api key" // adafruit api key
#define led_pin D5 


WiFiClient client; // creating a wifi client object

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY); // now create an object for mqtts



Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/test");



void MQTT_connect(); //defining the mqttconnect funtion 
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(led_pin,OUTPUT);
  Serial.println(F("Adafruit MQTT demo by IOT"));


  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  mqtt.subscribe(&onoffbutton);


}
uint32_t x=0;
void loop() {



  MQTT_connect();



  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(2500))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      String status = (char *)onoffbutton.lastread;
      Serial.println(status);
      if(status.equals("ON")){digitalWrite(led_pin,HIGH);}
      else if(status.equals("OFF")){digitalWrite(led_pin,LOW);}
    }
  }
}


void MQTT_connect() {
  int8_t ret;

  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { 
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000); 
       retries--;
       if (retries == 0) {
        
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}