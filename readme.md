# What does this library do
This library is a wrapper with the ability to direct the desired callback functions or objects of the topics you specify by wrapping the PubSubClient library used as an MQTT client for small iot devices such as Esp32 & Esp8266.

# What is this library not?
It is definitely not a rival library to other mqtt libraries.
My goal was to create a structure that can make different callbacks on the topics I specified. The library certainly does that now.

# Can I customize callbacks? 
You can create your custom callback classes if you want. For this, please have a look at the examples.

# Dependency (Important)
PubSubClient version 2.8.0 was used when the library was created. You must install PubSubClient yourself first. In the future, it may become unstable by updating the dependent library. Please let me know if you notice this.

# Feedbacks
If you spot an error, please consider providing feedback.

# Contribute
If you would like to contribute, you are welcome.