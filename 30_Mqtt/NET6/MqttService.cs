using MQTTnet;
using MQTTnet.Client;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Intrinsics.Arm;
using System.Runtime.Intrinsics.X86;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace DemoEsp32_Net_MQTT
{
    internal class MqttService
    {
        private IMqttClient mqttClient;
        
        public async Task Initialize(string brokerIpAddress)
        {
            var factory = new MqttFactory();

            var options = new MqttClientOptionsBuilder()
            .WithClientId("Client1")
            .WithTcpServer(brokerIpAddress, 1883)
            .Build();

            mqttClient = factory.CreateMqttClient();

            mqttClient.ConnectedAsync += (async e =>
            {
                await mqttClient.SubscribeAsync(new MqttTopicFilterBuilder().WithTopic("hello/world/esp32").Build());
            });

            mqttClient.ApplicationMessageReceivedAsync += (async e =>
            {
                Console.WriteLine($"+ Payload = {Encoding.UTF8.GetString(e.ApplicationMessage.Payload)}");
            });

            await mqttClient.ConnectAsync(options, CancellationToken.None);
        }

        public async Task SendMqtt(object payload)
        {
            var json = JsonSerializer.Serialize(payload);

            var applicationMessage = new MqttApplicationMessageBuilder()
                                       .WithTopic("hello/world/net")
                                       .WithPayload(json)
                                       .Build();

            await Task.Run(() => mqttClient.PublishAsync(applicationMessage));

        }
    }
}
