using Demo_Esp32_Net6_Serial;
using System.Reactive.Linq;

ArduinoPort arduinoPort = new ArduinoPort();
arduinoPort.DataArrived += ArduinoPort_DataArrived;

// ejemplo USB port en Windows
arduinoPort.Open("COM4", 115200);

// ejemplo USB port en Linux
//arduinoPort.Open("/dev/ttyUSB0", 115200);

Console.ReadLine();

// ejemplo que envia de forma temporizada, para el código ESP32 'receive'
// var isOn = false;
// var timer = Observable.Interval(TimeSpan.FromSeconds(2))
// .Subscribe(async _ =>
// {
//     var message = isOn ? "A" : "B";
//     isOn = !isOn;
//     arduinoPort.Write(message);
//     Console.WriteLine(message);
// });

void ArduinoPort_DataArrived(object? sender, EventArgs? e)
{
    var lastRecieved = arduinoPort.LastRecieved;
    Console.WriteLine(lastRecieved);
}
