using DemoEsp32_Net_Websockets;
using WebSocketSharp.Server;

InitWebSocketServer();

Console.ReadLine();

void InitWebSocketServer()
{
    var web = new WebSocketServer(81);
    web.AddWebSocketService<ArduinoWebsocket>("/API");

    ArduinoWebsocket.DataArrived += DataArrived;
    web.Start();
}

void DataArrived(object sender, EventArgs e)
{
    if (ArduinoWebsocket.LastRecieved == "A")
    {
        Console.WriteLine("A");
    }
    else if (ArduinoWebsocket.LastRecieved == "B")
    {
        Console.WriteLine("B");
    }
}