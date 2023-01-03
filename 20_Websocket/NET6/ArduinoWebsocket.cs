using System;
using WebSocketSharp.Server;
using WebSocketSharp;

namespace DemoEsp32_Net_Websockets
{
    public class ArduinoWebsocket : WebSocketBehavior
    {
        public static string LastRecieved { get; private set; } = "";

        public static event EventHandler DataArrived;

        protected override void OnMessage(MessageEventArgs e)
        {
            LastRecieved = e.Data;
            DataArrived?.Invoke(this, new EventArgs());
        }
    }
}
