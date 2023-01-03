#pragma once

const char* MQTT_BROKER_ADRESS = "192.168.1.xxx";
const uint16_t MQTT_PORT = 1883;
const char* MQTT_CLIENT_NAME = "ESP32Client_1";

#include <functional>

#include <PubSubClient.h>
#include <ArduinoJson.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);

class MqttService
{
public:
	void Init()
	{
		mqttClient.setServer(MQTT_BROKER_ADRESS, MQTT_PORT);
		SuscribeMqtt();

		mqttClient.setCallback([this](char* topic, uint8_t* payload, unsigned int length) -> void
		{
			this->OnMqttReceived(topic, payload, length);
		});
	}

	void ConnectMqtt()
	{
		while (!mqttClient.connected())
		{
			Serial.print("Starting MQTT connection...");
			if (mqttClient.connect(MQTT_CLIENT_NAME))
			{
				SuscribeMqtt();
			}
			else
			{
				Serial.print("Failed MQTT connection, rc=");
				Serial.print(mqttClient.state());
				Serial.println(" try again in 5 seconds");

				delay(5000);
			}
		}
	}

	void HandleMqtt()
	{
		if (!mqttClient.connected())
		{
			ConnectMqtt();
		}
		mqttClient.loop();
	}

	void SuscribeMqtt()
	{
		mqttClient.subscribe("hello/world/net");
	}

	String payload;
	void SendB()
	{
		String topic = "hello/world/esp32";
		payload = "A";
		mqttClient.publish(topic.c_str(), payload.c_str());
	}

	void SendA()
	{
		String topic = "hello/world/esp32";
		payload = "B";
		mqttClient.publish(topic.c_str(), payload.c_str());
	}

	String content = "";
	void OnMqttReceived(char* topic, uint8_t* payload, unsigned int length)
	{
		content = "";
		for (size_t i = 0; i < length; i++)
		{
			content.concat((char)payload[i]);
		}

		Serial.println(content);
	}
};