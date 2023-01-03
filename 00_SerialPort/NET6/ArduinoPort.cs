using System;
using System.IO.Ports;
using System.Threading;

namespace Demo_Esp32_Net6_Serial
{
    public class ArduinoPort
    {
        SerialPort _serialPort = new SerialPort();
        public string LastRecieved { get; private set; } = "";

        public bool IsReady { get; private set; }

        public bool IsOpen = false;

        public event EventHandler DataArrived;

        public ArduinoPort()
        {
        }

        public void Open(string port, int baud)
        {
            if (IsOpen) return;

            IsOpen = true;
            _serialPort.PortName = port;
            _serialPort.BaudRate = baud;
            _serialPort.DtrEnable = true;
            _serialPort.ReadTimeout = 1;
            _serialPort.WriteTimeout = 1;
            _serialPort.Open();
            _serialPort.DiscardInBuffer();
            _serialPort.DiscardOutBuffer();
            _serialPort.DataReceived += _serialPort_DataReceived; ;
        }

        public void Close()
        {
            if (!IsOpen) return;
            try
            {
                _serialPort.DataReceived -= _serialPort_DataReceived;
                _serialPort.Close();
                IsOpen = false;
            }
            catch (Exception)
            {
                //do nothing
            }
        }

        public void Write(string text)
        {
            _serialPort.Write(text);
        }
        
        private void _serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            LastRecieved = _serialPort.ReadExisting().Replace('\n'.ToString(), "").Replace('\r'.ToString(), "");
            DataArrived?.Invoke(this, new EventArgs());
        }
    }
}