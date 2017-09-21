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

	Screen.sendData(0x00);// display symbol on SCREEN
	Screen.sendData(0x01);// display symbol on SCREEN
	Screen.sendData(0x02);// display symbol on SCREEN
	Screen.sendData(0x03);// display symbol on SCREEN
	Screen.sendData(0x04);// display symbol on SCREEN
	Screen.sendData(0x05);// display symbol on SCREEN
	Screen.sendData(0x06);// display symbol on SCREEN
	Screen.sendData(0x07);// display symbol on SCREEN

	// 9 due to we have to ignore first line in answer
	char CGRAM_symbol[9];
	Screen.readRamSymbol(CGRAM_symbol, 3);

	uint8_t i;
	Serial.println("--------");
	for(i=0; i<9; i++) {
		byte one_b = CGRAM_symbol[i];
		graphicByte(one_b);
		//Serial.println(CGRAM_symbol[i], BIN);
	}
	Serial.println("--------");

}

void loop() {
}


void graphicByte(char symbol) {
	uint8_t bi;
	uint8_t step_data;
	for(bi=0;bi<8;bi++) { // each bit in a byte
		step_data = symbol >> (7-bi);
		step_data = step_data & 0x01;
		if (bi<2) {
			Serial.print(step_data, BIN);
			continue;
		}
		if (bi==2) {
			Serial.print("|");
			continue;
		}
		if (step_data == 0x01) {
			Serial.print("█");
		}
		else {
			Serial.print(" ");
		}
	}
	Serial.println("");
}