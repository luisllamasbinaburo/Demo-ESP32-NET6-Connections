using DemoEsp32_Net_HTTP;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

InitWebServer();

Console.ReadLine();

int port;
string[] prefix;
WebServer webServer;

void InitWebServer()
{
    port = 80;
    prefix = new string[] { $"http://*/API/" };
    webServer = new WebServer(ProcessRequest, prefix);
    webServer.Run();
}

string ProcessRequest(HttpListenerRequest request)
{
    var endpoint = request.Url.LocalPath;

    if (endpoint == "/API/EndpointA")
    {
        Console.WriteLine("EndpointA");
        return "";
    }

    if (endpoint == "/API/EndpointB")
    {
        Console.WriteLine("EndpointA");
        return "";
    }

    return "Invalid address";
}
