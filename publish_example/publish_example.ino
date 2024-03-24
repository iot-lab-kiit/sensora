#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>


#define WIFI_SSID       "wifi ssid"
#define WIFI_PASSWORD   "wifi pass"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   
#define AIO_USERNAME    "username" // enter your adafruit io user name
#define AIO_KEY         "apikey" // enter your adafruit io api key


#define TOPIC          "uuun/feeds/test" // Enter your feed username/feeds/feedname given by you


WiFiClient client;


Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish mqttPublish = Adafruit_MQTT_Publish(&mqtt, TOPIC);

void setup() {
  Serial.begin(115200);
  delay(10);

  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (mqtt.connected()) {
    mqttPublish.publish("Suman Saha");// Write your name here
  } else {
    Serial.println("Suman Saha");// Write your name here
  } else {
    if (mqtt.connect()) {
      Serial.println("Connected to Adafruit IO");
    } else {
      Serial.println("Connection to Adafruit IO failed...");
      delay(6000); // 
    }
  }
  
  delay(6000); // 
}
