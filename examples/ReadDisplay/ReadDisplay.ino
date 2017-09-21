// Include the libraries we need
#include <SSD1311.h>
#include "Wire.h"

SSD1311 Screen;

void setup(void) {
	Serial.begin(9600);
	Wire.begin();

	Screen.powerMode(SSD1311_LCD_OFF);// actual for reset pressed
	Screen.selectRomRam(SSD1311_ROM_A, SSD1311_CGRAM_1);// select ROM and RAM
	Screen.powerMode(SSD1311_LCD_ON);// power on SCREEN
	Screen.clear();

	Screen.sendString("Ssd1311test", 3, 1);

	// we have to ignore first line in answer
	char DISP_CHARS[10];
	Screen.readString(DISP_CHARS, 5, 1, 5);

	uint8_t i;
	Serial.println("--------");
	Serial.print("|");
	for(i=0; i<6; i++) {
		Serial.print(DISP_CHARS[i]);
	}
	Serial.println("|");
	Serial.println("--------");

}

void loop() {
}
