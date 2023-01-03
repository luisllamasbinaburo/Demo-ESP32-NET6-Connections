using System.Diagnostics;
using System.Reactive.Linq;

var isOn = false;
var timer = Observable.Interval(TimeSpan.FromSeconds(2))
.Subscribe(async _ =>
{
    isOn = !isOn;
    var url = @$"http://192.168.1.xxx/{(isOn ? "A" : "B")}";

    var response = await new HttpClient().GetAsync(url);
    var data = await response.Content.ReadAsStringAsync();
    Console.WriteLine(data);
});

Console.ReadLine();