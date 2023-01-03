using System.Net;
using System.Text;

namespace DemoEsp32_Net_HTTP
{
    public class WebServer
    {
        private readonly HttpListener _listener = new HttpListener();
        private readonly Func<HttpListenerRequest, string> _responderMethod;

        public WebServer(Func<HttpListenerRequest, string> method, params string[] prefixes)          
        {
            foreach (string s in prefixes) _listener.Prefixes.Add(s);

            _responderMethod = method;
            _listener.Start();
        }

        public void Run()
        {
            ThreadPool.QueueUserWorkItem((o) =>
            {
                while (_listener.IsListening)
                {
                    ThreadPool.QueueUserWorkItem((c) =>
                    {
                        var ctx = c as HttpListenerContext;
                            string rstr = _responderMethod(ctx.Request);
                            SendResponse(ctx, rstr);
                            ctx.Response.OutputStream.Close();
                    }, _listener.GetContext());
                }   
            });
        }

        private static void SendResponse(HttpListenerContext ctx, string rstr)
        {
            ctx.Response.ContentType = "text/html";
            ctx.Response.ContentEncoding = Encoding.Unicode;

            byte[] buf = Encoding.Unicode.GetBytes(rstr);
            ctx.Response.ContentLength64 = buf.Length;
            ctx.Response.OutputStream.Write(buf, 0, buf.Length);
        }

        public void Stop()
        {
            _listener.Stop();
            _listener.Close();
        }
    }
}
