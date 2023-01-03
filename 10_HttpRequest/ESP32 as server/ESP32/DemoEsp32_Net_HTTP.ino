/***************************************************
Copyright (c) 2020 Luis Llamas
(www.luisllamas.es)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses
****************************************************/

#include <M5StickCPlus.h>

#include <WiFi.h>
#include <WebServer.h>
 
#include "./utils/config.h"
#include "./utils/M5StackUtils.h"

TFT_eSprite tftSprite = TFT_eSprite(&M5.Lcd);

#include "./src/Server.hpp"

void setup(void) 
{
	Serial.begin(115200);
	M5.begin();
	M5.Lcd.setRotation(0);
	M5.IMU.Init();
   
   	tftSprite.setColorDepth(16);
	tftSprite.createSprite(m5.Lcd.width(), m5.Lcd.height());
	tftSprite.fillScreen(TFT_BLACK);

	ConnectWiFi_STA();
 
	InitServer();
}

void setup() {
	Serial.begin(115200);
	M5.begin();
	M5.Lcd.setRotation(0);
	M5.IMU.Init();

	tftSprite.setColorDepth(16);
	tftSprite.createSprite(m5.Lcd.width(), m5.Lcd.height());
	tftSprite.fillScreen(TFT_BLACK);

	WIFI_Connect();
}

void loop()
{
	M5.update();

	server.handleClient();
	delay(100);
}