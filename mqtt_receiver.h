#pragma once
#include <string>
#include <memory>
namespace YGV{
  struct MQTTReceiver{
    virtual void receive(const std::string& topic,const std::string& payload) = 0;
  };
  
  using MQTTReceiverPtr = std::shared_ptr<MQTTReceiver>;
}
