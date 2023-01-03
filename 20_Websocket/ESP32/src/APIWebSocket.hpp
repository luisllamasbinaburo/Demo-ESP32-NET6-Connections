#pragma once

String ApiHost = "192.168.1.150";

WebSocketsClient webSocket;
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

	switch(type) {
		case WStype_DISCONNECTED:
			USE_SERIAL.printf("[WSc] Disconnected!\n");
			break;
		case WStype_CONNECTED:
			USE_SERIAL.printf("[WSc] Connected to url: %s\n", payload);

			// send message to server when Connected
			webSocket.sendTXT("Connected");
			break;
		case WStype_TEXT:
			USE_SERIAL.printf("[WSc] get text: %s\n", payload);

			// send message to server
			// webSocket.sendTXT("message here");
			break;
		case WStype_BIN:
			USE_SERIAL.printf("[WSc] get binary length: %u\n", length);
			//hexdump(payload, length);

			// send data to server
			// webSocket.sendBIN(payload, length);
			break;
		case WStype_ERROR:	
			USE_SERIAL.printf("[WSc] ERROR: %u\n", length);
		case WStype_FRAGMENT_TEXT_START:
		case WStype_FRAGMENT_BIN_START:
		case WStype_FRAGMENT:
		case WStype_FRAGMENT_FIN:
			break;
	}
}

void InitWebSockets()
{
	webSocket.begin(ApiHost, 81, "/API");
	webSocket.onEvent(webSocketEvent);
	Serial.println("Connected websockets");
}

void SendA()
{
	webSocket.sendTXT("A");
}

void SendB()
{
	webSocket.sendTXT("B");
}