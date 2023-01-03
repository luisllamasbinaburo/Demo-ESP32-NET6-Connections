#pragma once

WebServer server(80);

void handleNotFound() 
{
   server.send(404, "text/plain", "Not found");
}

void InitServer()
{
   server.on("/A", []() {
      server.send(200, "text/plain", "A funciona");
      tftSprite.fillScreen(TFT_RED);
	   tftSprite.pushSprite(0, 0);
      Serial.println("A");
   });

   server.on("/B", []() {
      server.send(200, "text/plain", "B funciona");
      tftSprite.fillScreen(TFT_GREEN);
	   tftSprite.pushSprite(0, 0);
      Serial.println("B");
   });
 
   server.onNotFound(handleNotFound);
 
   server.begin();
   Serial.println("HTTP server started");
}