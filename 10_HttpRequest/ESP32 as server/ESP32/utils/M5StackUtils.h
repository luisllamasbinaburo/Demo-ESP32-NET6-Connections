#pragma once

// Connects to WIFI
void  WIFI_Connect() {
	int i = 0;
	// Connect to WiFi network
	Serial.println();
	Serial.println();
	Serial.printf("Connecting to WIFI: %s\n", ssid);

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(100);
		Serial.print(".");
		i++;
		if (i > 15) {
			i = 0;
			Serial.printf("\nConnecting to WIFI: %s\n", ssid);
		}
	}

	Serial.println("");
	Serial.println("WiFi connected");
}