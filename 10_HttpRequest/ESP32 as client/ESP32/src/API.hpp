#pragma once

String ApiHost = "http://192.168.1.xxx:80";

void processResponse(int httpCode, HTTPClient& http)
{
	if (httpCode > 0) {
		Serial.printf("Response code: %d\t", httpCode);

		if (httpCode == HTTP_CODE_OK) {
			String payload = http.getString();
			Serial.println(payload);
		}
	}
	else {
		Serial.printf("Request failed, error: %s\n", http.errorToString(httpCode).c_str());
	}
	http.end();
}

void SendEndpointA()
{
	HTTPClient http;
	http.begin(ApiHost + "/API/EndpointA");
	int httpCode = http.GET();
	processResponse(httpCode, http);
}

void SendEndpointB()
{
	HTTPClient http;
	http.begin(ApiHost + "/API/EndpointB");
	int httpCode = http.GET();
	processResponse(httpCode, http);
}
