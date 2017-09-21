// Include the libraries we need
#include <SSD1311.h>
#include "Wire.h"

//#define █ 1
//#define ░ 0

// █░░░░█
// █░░░░█
// ███░░█
// ░░░░░░
// ████░░
// ░░█░░░
// ░█░░░░
// ████░░

SSD1311 Screen;

void setup(void) {
	Wire.begin();
	Screen.selectRomRam(SSD1311_ROM_A, SSD1311_CGRAM_1);

	uint8_t symb_num = 3;
	char my_symbol[] = {
		B01010001,// █░░░░█
		B01010001,// █░░░░█
		B01011101,// ███░░█
		B01000000,// ░░░░░░
		B01011110,// ████░░
		B01000100,// ░░█░░░
		B01001000,// ░█░░░░
		B01011110,// ████░░
	};
	Screen.writeRamSymbol(my_symbol, symb_num);

	Screen.clear();
	Screen.powerMode(SSD1311_LCD_ON);

	Screen.setCursorPosition(5, 1);
	Screen.sendData(symb_num);
	Screen.sendData(symb_num);
	Screen.sendData(symb_num);
}

void loop() {
	showGliphs();
	delay(10);// not required
}

unsigned long gliphsTime = 0;
int lastGlyphCode = 0;
void showGliphs() {
	unsigned long time = millis();
	unsigned char packet[19];
	uint8_t i = 0;
	if (time - gliphsTime > 1000) {
		packet[0] = SSD1311_CMD_MODE;
		//packet[1] = 0x01; // clear screen
		packet[1] = 0x80; // set cursor to 0,0
		packet[2] = SSD1311_DATA_MODE;
		uint8_t shift = 3;
		for(i=0; i<16; i=i+1){
			packet[shift+i] = lastGlyphCode + i;
		}
		lastGlyphCode = lastGlyphCode + 16;
		Screen.sendBatch(packet, 19);
		gliphsTime = time;
	}
}
