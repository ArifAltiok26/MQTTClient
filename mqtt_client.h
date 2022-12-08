#pragma once
#include "mqtt_receiver.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <unordered_map>
#include <vector>

namespace YGV{
  class MQTTClient{
    using Receivers = std::vector<MQTTReceiverPtr>;
  public:
    void begin(WiFiClient& wifi, const char* server, uint16_t port);

    bool connect();
    
    bool connect(const char* id);

    bool connect(const char* user,const char* password);

    bool connect(const char* id,const char* user,const char* password);

    void disconnect();

    bool isConnected();

    void subscribe(const std::string& topic, MQTTReceiverPtr receiver);

    void unsubscribe(const std::string& topic, MQTTReceiverPtr receiver);

    void publish(const std::string& topic, const std::string& payload);

    void loop();

  private:
    void routing(const char* topic, uint8_t* payload,unsigned int len);
  private:
    std::unordered_map<std::string, Receivers> m_receivers;
    PubSubClient m_client;
  };
}