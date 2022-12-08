#include "mqtt_receiver_without_topic.h"
namespace YGV{
  MQTTReceiverWithoutTopic::MQTTReceiverWithoutTopic(Callback callback) : m_callback(callback){}

  void MQTTReceiverWithoutTopic::receive(const std::string& topic,const std::string& payload){
    m_callback(payload);
  }
}