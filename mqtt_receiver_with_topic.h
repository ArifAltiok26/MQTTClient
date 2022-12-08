#pragma once
#include "mqtt_receiver.h"
#include <functional>
namespace YGV{
  class MQTTReceiverWithTopic : public MQTTReceiver{
  public:
    using Callback = std::function<void(const std::string& topic,const std::string& payload)>;

    MQTTReceiverWithTopic(Callback callback);

    void receive(const std::string& topic,const std::string& payload) override final;

  private:
    Callback m_callback;
  };
}