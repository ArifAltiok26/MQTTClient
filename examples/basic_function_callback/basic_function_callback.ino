#include <ESP8266WiFi.h>
#include <mqtt_client.h>
#include <mqtt_receiver_with_topic.h>

const char*     ssid          = "YOUR_SSID_ID";
const char*     password      = "YOUR_PASSWORD";

// Also you don't have to use adafruit.com as an mqtt broker.
// I just performed the experiments there.

const char*     MQTT_SERVER   = "io.adafruit.com";
const uint16_t  MQTT_PORT     = 1883;

const char*     AIO_USER      = "YOUR_USER";
const char*     AIO_KEY       = "YOUR_KEY";


WiFiClient wifi;
YGV::MQTTClient mqtt;

void callback(const std::string& topic,const std::string& message){
  Serial.println(topic.c_str());
  Serial.println(message.c_str());
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("WiFi connected.IP address: ");
  Serial.println(WiFi.localIP());

  mqtt.begin(wifi, MQTT_SERVER, MQTT_PORT);
  
  mqtt.connect(AIO_USER,AIO_KEY);

  if(mqtt.isConnected()){
    Serial.println("Mqtt connected");
  }

  mqtt.subscribe("aaltiok/feeds/d0",std::make_shared<YGV::MQTTReceiverWithTopic>(callback);
}

void loop() {
  if(!mqtt.isConnected()){
    mqtt.connect(AIO_USER,AIO_KEY);
  }

  mqtt.loop();
}
