// Include the libraries we need
#include <SSD1311.h>
#include "Wire.h"

SSD1311 Screen;

void setup(void) {
	Wire.begin();
	Screen.selectRomRam(SSD1311_ROM_A, SSD1311_CGRAM_1);

	uint8_t symb_num = 0;
	char my_symbol0[] = {
		B01000000,
		B01000000,
		B01001000,
		B01010101,
		B01000010,
		B01000000,
		B01000000,
		B01000000,
	};
	Screen.writeRamSymbol(my_symbol0, symb_num);

	symb_num = 1;
	char my_symbol1[] = {
		B01000000,
		B01000000,
		B01000100,
		B01001010,
		B01010001,
		B01000000,
		B01000000,
		B01000000,
	};
	Screen.writeRamSymbol(my_symbol1, symb_num);

	symb_num = 2;
	char my_symbol2[] = {
		B01000000,
		B01000000,
		B01000010,
		B01010101,
		B01001000,
		B01000000,
		B01000000,
		B01000000,
	};

	symb_num = 3;
	char my_symbol3[] = {
		B01000000,
		B01000000,
		B01010001,
		B01001010,
		B01000100,
		B01000000,
		B01000000,
		B01000000,
	};
	Screen.writeRamSymbol(my_symbol3, symb_num);

	Screen.clear();
	Screen.powerMode(SSD1311_LCD_ON);
}

uint8_t anim_index=0;
uint8_t anim_max_index = 3;
uint8_t i=0;
uint8_t animation[] = {0,1,2,3};
void loop() {
	//char line[10];//Ten characters, I hope that's enough
	//dtostrf(anim_index,2,0,line);
	//Screen.sendString(line, 0,0);
	Screen.setCursorPosition(6,0);
	for (i=0; i < 4; i++) {
		Screen.sendData(animation[i]);
	}
	
	updateAnimation();
	delay(50);
}

uint8_t updateAnimation() {
	for (i=0; i < 4; i++) {
		animation[i]=animation[i]+1;
		if (animation[i]> anim_max_index) {
			animation[i] = 0;
		}
	}
}
