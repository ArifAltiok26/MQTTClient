#pragma once
#include "mqtt_receiver.h"
#include <functional>
namespace YGV{
  class MQTTReceiverWithoutTopic : public MQTTReceiver{
  public:
    using Callback = std::function<void(const std::string&)>;

    MQTTReceiverWithoutTopic(Callback callback);

    void receive(const std::string& topic,const std::string& payload) override final;

  private:
    Callback m_callback;
  };
}