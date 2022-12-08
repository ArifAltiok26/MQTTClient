#include "mqtt_receiver_with_topic.h"
namespace YGV{
  MQTTReceiverWithTopic::MQTTReceiverWithTopic(Callback callback) : m_callback(callback){}

  void MQTTReceiverWithTopic::receive(const std::string& topic,const std::string& payload){
    m_callback(topic, payload);
  }
}