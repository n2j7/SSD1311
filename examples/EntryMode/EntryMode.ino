// Include the libraries we need
#include <SSD1311.h>
#include "Wire.h"

SSD1311 Screen;

void setup(void) {
	Serial.begin(9600);
	Wire.begin();

	//Screen.powerMode(SSD1311_LCD_ON);// power on SCREEN
	//Screen.clear();
}

void loop() {
	normalOutput();
	noDisplayShift();
	cursorLeft();
	BDCreverse();
	BDSreverse();
	BDC_BDSreverse();
}

void normalOutput(){
	Screen.powerMode(SSD1311_LCD_OFF);
	Screen.display_shift=true;
	Screen.cursor_blinking=false;
	Screen.cursor_direction=SSD1311_DIRECTION_RIGHT;
	Screen.BDC=true;
	Screen.BDS=true;
	Screen.setEntryMode();
	Screen.powerMode(SSD1311_LCD_ON);
	Screen.clear();
	Screen.sendString("1 This is the test of long line", 0, 0);
	delay(5000);
}

void noDisplayShift() {
	Screen.powerMode(SSD1311_LCD_OFF);
	Screen.display_shift=false;
	Screen.setEntryMode();
	Screen.powerMode(SSD1311_LCD_ON);
	Screen.clear();
	Screen.sendString("2 Second line is still too long", 0, 0);
	delay(5000);
}

void cursorLeft() {
	Screen.powerMode(SSD1311_LCD_OFF);
	Screen.display_shift=true;
	Screen.cursor_blinking=true;
	Screen.cursor_direction = SSD1311_DIRECTION_LEFT;
	Screen.setEntryMode();
	Screen.powerMode(SSD1311_LCD_ON);
	Screen.clear();
	Screen.sendString("3 Test :)", 0, 0);
	delay(5000);
}

void BDCreverse() {
	Screen.powerMode(SSD1311_LCD_OFF);
	Screen.cursor_blinking=false;
	Screen.cursor_direction = SSD1311_DIRECTION_RIGHT;
	Screen.BDC=false;
	Screen.setEntryMode();
	Screen.powerMode(SSD1311_LCD_ON);
	Screen.clear();
	Screen.sendString("4 Test BDC long line with additional data", 0, 0);
	delay(5000);
}

void BDSreverse() {
	Screen.powerMode(SSD1311_LCD_OFF);
	Screen.cursor_blinking=false;
	Screen.cursor_direction = SSD1311_DIRECTION_RIGHT;
	Screen.BDC=true;
	Screen.BDS=false;
	Screen.setEntryMode();
	Screen.powerMode(SSD1311_LCD_ON);
	Screen.clear();
	Screen.sendString("5 Test BDS this string is out of screen", 0, 0);
	delay(5000);
}

void BDC_BDSreverse() {
	Screen.powerMode(SSD1311_LCD_OFF);
	Screen.cursor_blinking=false;
	Screen.cursor_direction = SSD1311_DIRECTION_RIGHT;
	Screen.BDC=false;
	Screen.BDS=false;
	Screen.setEntryMode();
	Screen.powerMode(SSD1311_LCD_ON);
	Screen.clear();
	Screen.sendString("6 Test BDC, BDS this line is out of screen", 0, 0);
	delay(5000);
}