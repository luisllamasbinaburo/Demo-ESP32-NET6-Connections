/***************************************************
Copyright (c) 2020 Luis Llamas
(www.luisllamas.es)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License along with this program.  If not, see <http://www.gnu.org/licenses
****************************************************/

#include <M5StickC.h>


TFT_eSprite tftSprite = TFT_eSprite(&M5.Lcd);

void setup() {
	Serial.begin(115200);
	M5.begin();
	M5.Lcd.setRotation(0);
	M5.IMU.Init();

	tftSprite.setColorDepth(16);
	tftSprite.createSprite(m5.Lcd.width(), m5.Lcd.height());
	tftSprite.fillScreen(TFT_BLACK);
}

bool isOn = false;

bool GetIsTumbado()
{
	float accX = 0;
	float accY = 0;
	float accZ = 0;
	M5.IMU.getAccelData(&accX, &accY, &accZ);
	return accZ > 0.8f;
}

void Update()
{
	if(isOn == false && GetIsTumbado() == false)
	{
		isOn = true;
		Serial.println("A");
	}
	else if(isOn == true && GetIsTumbado() == true)
	{
		isOn = false;
		Serial.println("B");
	}
}

void Render()
{
	tftSprite.fillScreen(isOn ? TFT_RED : TFT_GREEN);
	tftSprite.pushSprite(0, 0);
}

void loop()
{
	M5.update();

	delay(200);

	Update();
	Render();
}