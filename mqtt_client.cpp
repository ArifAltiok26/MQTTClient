#include "mqtt_client.h"
namespace YGV{

  void MQTTClient::begin(WiFiClient& wifi, const char* server, uint16_t port){
    m_client.setClient(wifi);
    m_client.setServer(server,port);
    m_client.setCallback(std::bind(&MQTTClient::routing,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
  }

  bool MQTTClient::connect(){
    return connect(String(random(0,65536)).c_str());
  }

  bool MQTTClient::connect(const char* id){
    if(isConnected()){
      return true;
    }
    return m_client.connect(id);
  }

  bool MQTTClient::connect(const char* user,const char* password){
    return connect(String(random(0,65536)).c_str(),user,password);
  }
  
  bool MQTTClient::connect(const char* id,const char* user,const char* password){
    if(isConnected()){
      return true;
    }
    return m_client.connect(id, user, password);
  } 

  void MQTTClient::disconnect(){
    if(isConnected()){
      m_client.disconnect();
    }
  }

  bool MQTTClient::isConnected(){
    return m_client.connected();
  }

  void MQTTClient::subscribe(const std::string& topic, MQTTReceiverPtr receiver){
    auto iter = m_receivers.find(topic);
    if(iter == m_receivers.end()){
      m_receivers[topic] = {receiver};
      m_client.subscribe(topic.c_str());
    }
    else{
      Receivers& receivers = iter->second;
      receivers.push_back(receiver);
    }
  }

  void MQTTClient::unsubscribe(const std::string& topic, MQTTReceiverPtr receiver){
    auto iter = m_receivers.find(topic);
    if(iter != m_receivers.end()){
      Receivers& receivers = iter->second;
      auto receiver_iter = std::find_if(receivers.begin(),receivers.end(),[&receiver](const MQTTReceiverPtr& inApp){
        return receiver.get() == inApp.get();
      });

      if(receiver_iter != receivers.end()){
        receivers.erase(receiver_iter);
      }

      if(receivers.empty()){
        m_receivers.erase(iter);
        m_client.unsubscribe(topic.c_str());
      }
    }
  }


  void MQTTClient::publish(const std::string& topic, const std::string& payload){
    m_client.publish(topic.c_str(),payload.c_str());
  }

  void MQTTClient::loop(){
    m_client.loop();
  }


  void MQTTClient::routing(const char* topic, uint8_t* payload,unsigned int len){
    std::string sTopic(topic);
    auto iter = m_receivers.find(sTopic);
    if(iter != m_receivers.end()){
      Receivers& receivers = iter->second;
      std::string message;
      message.resize(len);
      memcpy_P(&message[0],payload,len);
      for(MQTTReceiverPtr& receiver : receivers){
        receiver->receive(sTopic,message);
      }
    }
  }
}