using DemoEsp32_Net_MQTT;
using System.Reactive.Linq;

var brokerIpAddress = "192.168.1.xxx";

Console.WriteLine("** Starting ***");

Console.Write("  - Initializing MQTT:");
var mqttService = new MqttService();
await mqttService.Initialize(brokerIpAddress);
Console.WriteLine(" OK");

var timer = Observable.Interval(TimeSpan.FromSeconds(2))
.Subscribe(async _ =>
{
try
{
    await mqttService.SendMqtt(new { data = System.DateTime.Now });
}
catch (Exception ex)
{
        Console.WriteLine($"{DateTime.Now} Error sending: {ex.Message}");                      
}                   
});

Console.ReadLine();