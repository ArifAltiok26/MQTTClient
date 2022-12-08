#include <ESP8266WiFi.h>
#include <mqtt_client.h>
#include <mqtt_receiver_with_topic.h>
#include <mqtt_receiver_without_topic.h>

const char*     ssid          = "YOUR_SSID_ID";
const char*     password      = "YOUR_PASSWORD";

// Also you don't have to use adafruit.com as an mqtt broker.
// I just performed the experiments there.

const char*     MQTT_SERVER   = "io.adafruit.com";
const uint16_t  MQTT_PORT     = 1883;

const char*     AIO_USER      = "YOUR_USER";
const char*     AIO_KEY       = "YOUR_KEY";


// How to create a custom receiver
class LedController : public YGV::MQTTReceiver{
public:
  LedController(uint8_t pin,uint8_t initialState = 0) : m_pin(pin){
    pinMode(m_pin,OUTPUT);
    digitalWrite(m_pin,initialState);
  }

  void receive(const std::string& topic,const std::string& message)override final{
    // Assume that message will be "ON" or "OFF";
    // We can do that if message "ON" then led will be open else led will be close.
    digitalWrite(m_pin, message == "ON");
  }
private:
  uint8_t m_pin;
};

WiFiClient wifi;
YGV::MQTTClient mqtt;

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

  
  mqtt.subscribe("aaltiok/feeds/d1",std::make_shared<YGV::MQTTReceiverWithoutTopic>([](const std::string& message){
    Serial.print("I received only message. ");
    Serial.println(message.c_str());
  }));

  //
  // Be carefull. I subscribed another one under the same topic.
  mqtt.subscribe("aaltiok/feeds/d1",std::make_shared<YGV::MQTTReceiverWithTopic>([](const std::string& topic,const std::string& message){
    Serial.print("I received topic and message. Topic: ");
    Serial.print(topic.c_str());
    Serial.print(" message: ");
    Serial.println(message.c_str());
  }));

  // This is a custom receiver which is under the d2 topic. You should mount a led where is in D5.
  // Thus, this receiver automatically controls the led according to the incoming message.
  mqtt.subscribe("aaltiok/feeds/d2",std::make_shared<LedController>(D3));
}

void loop() {
  if(!mqtt.isConnected()){
    mqtt.connect(AIO_USER,AIO_KEY);
  }

  mqtt.loop();
}
