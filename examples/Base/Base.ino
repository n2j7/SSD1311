// Include the libraries we need
#include <SSD1311.h>
#include "Wire.h"

SSD1311 Screen;

void setup(void) {
	Wire.begin();
	Screen.powerMode(SSD1311_LCD_ON);
	Screen.sendString("OLED i2c 1602 Screen",0,0);
	Screen.sendString("Base.ino",5,1);
}

void loop() {
	delay(1000);
}