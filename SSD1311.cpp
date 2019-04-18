#include "SSD1311.h"

SSD1311::SSD1311(){
	// default settings
	mc_address = 0x3c;
	cursor_on = false;
	cursor_blinking = false;
	reverse_mode = false;
	double_height = false;
	cursor_inverting = false;
	display_lines = 2;// @TODO control this, write function to change registers N and NW
	display_shift = true;
	display_shift_dir = SSD1311_DIRECTION_RIGHT;
	cursor_shift = false;
	cursor_direction = SSD1311_DIRECTION_RIGHT;
	BDC=true;
	BDS=true;
	// default states
	IS=0;
	RE=0;
	SD=0;
	N=1;// for 2 line display
	NW=0;// for 2 line display 
	FW=0;// font-width "1" for 6-dot font; "0" for 5-dot font @TODO: control this
}

void SSD1311::setLines(uint8_t lines){
	display_lines=lines;
	if (display_lines > 1)
		NW = 1;
	else
		NW = 0;
	
	if (display_lines % 2)
		N=0;
	else
		N=1;
	
}

SSD1311::~SSD1311(){}

void SSD1311::powerMode(uint8_t is_on) {
	// @Note: 
	//     It is recommended to turn off the
	//     cursor and blinking effects when
	//     updating internal RAM contents for
	//     better visual performance; refer to
	//     Section 9.1.4 for details

	delay(105);//waiting for Vdd become stable @TODO: remove delay with async code
	//setDisplayShift();
	//setCursorShift();
	//setFont();
	//clear();
	// [IS=X,RE=0,SD=0] power on command
	// 0 0 0 0 1 D C B
	// D - display on
	// C - cursor on
	// B - blink on
	int base_cmd = 0x08; // 0b00001000
	base_cmd = base_cmd | (is_on << 2);// set 3-nd bit
	base_cmd = base_cmd | (cursor_on << 1);// set 2-nd bit
	base_cmd = base_cmd | cursor_blinking;//set 1-st bit
	sendCommand(base_cmd);
}

void SSD1311::setEntryMode() {
	// [IS=X,RE=0,SD=0]
	// 0 0 0 0 0 1 I/D S
	// I/D - cursor direction
	// S - display shift
	int base_cmd = 0x08; // 0b00000100
	base_cmd = base_cmd | (cursor_direction << 1);// set 2-nd bit
	base_cmd = base_cmd | display_shift;//set 1-st bit
	sendCommand(base_cmd);

	// [IS=X,RE=1,SD=0]
	// 0 0 0 0 0 1 BDC BDS
	// BDC - "0": COM31 -> COM0; "1": COM0 -> COM31
	// BDS = "0": SEG99 -> SEG0; "1": SEG0 -> SEG99
	base_cmd = 0x08; // 0b00000100
	base_cmd = base_cmd | (BDC << 1);// set 2-nd bit
	base_cmd = base_cmd | BDS;//set 1-st bit
	setRE(1);
	sendCommand(base_cmd);
	setRE(0);
}

void SSD1311::sendCommand(unsigned char command) {
	Wire.beginTransmission(mc_address);
	Wire.write(SSD1311_CMD_MODE);// Set OLED Command mode [Co=1, D/C#=0]
	Wire.write(command);
	// @TODO: here may be more than one command in queue, each command prepending by 0x80 uint8_t
	Wire.endTransmission();
}

void SSD1311::sendData(unsigned char data) {
	Wire.beginTransmission(mc_address);
	Wire.write(SSD1311_DATA_MODE);// Set OLED Data mode [Co=0, D/C#=1]
	Wire.write(data);
	Wire.endTransmission();
}

void SSD1311::sendBatch(unsigned char pack[], uint8_t length) {
	uint8_t i=0;
	Wire.beginTransmission(mc_address);
	for (i=0; i < length; i = i + 1) {
		Wire.write(pack[i]);
	}
	Wire.endTransmission();
}

void SSD1311::sendString(const char *String, uint8_t col, uint8_t row) {
	setCursorPosition(col, row);
	unsigned char i=0;
	while(String[i]) {
		sendData(String[i]);
		i++;
	}
}

void SSD1311::readData(char *buf, uint8_t length) {
	Wire.requestFrom(mc_address, length);
	uint8_t idx=0;
	while (Wire.available()) {
		buf[idx] =  Wire.read();
		idx++;
	}
}

void SSD1311::clear() {
	sendCommand(0x01);// [IS=X,RE=X,SD=0] clear command
}

void SSD1311::home() {
	sendCommand(0x02);// [IS=X,RE=0,SD=0] go to pos 0,0 without changing DDRAM
}

void SSD1311::setRE(uint8_t state) {
	uint8_t base_cmd = 0x20; // 0b00100000
	RE=state;
	if (state) {
		// 0 0 1 0 N BE RE REV
		// N - Numbers of display line
		// BE - CGRAM blink enable
		// RE register set to 1
		// REV - reverse display
		base_cmd = base_cmd | (N << 3);
		// @TODO: handle CGRAM blink
		base_cmd = base_cmd | (RE << 1);
		base_cmd = base_cmd | reverse_mode;
	}
	else {
		// 0 0 1 0 N DH RE IS
		// N - Numbers of display line
		// DH - Double height font control
		// RE register set to 0
		// IS register
		base_cmd = base_cmd | (N << 3);
		base_cmd = base_cmd | (double_height << 2);
		base_cmd = base_cmd | (RE << 1);
		base_cmd = base_cmd | IS;
	}
	sendCommand(base_cmd);
}

void SSD1311::setIS(uint8_t state) {
	// [IS=X,RE=0,SD=0]
	// 0 0 1 0 N DH RE IS
	// N - Numbers of display line
	// DH - Double height font control
	// RE register = 0
	// IS register
	IS=state;
	uint8_t base_cmd = 0x20; // 0b00100000
	base_cmd = base_cmd | (N << 3);
	base_cmd = base_cmd | (double_height << 2);
	//base_cmd = base_cmd | (RE << 0); nothing to change in RE
	base_cmd = base_cmd | state;
	sendCommand(base_cmd);
}

void SSD1311::setSD(uint8_t state) {
	// [IS=X,RE=1,SD=X]
	// 0 1 1 1 1 0 0 SD
	SD=state;
	uint8_t base_cmd = 0x78; // 0b01111000
	base_cmd = base_cmd + state;
	setRE(1);
	sendCommand(base_cmd);
}

void SSD1311::setFont() {
	// [IS=X,RE=1,SD=0]
	// 0 0 0 0 1 FW B/W NW
	// FW - font width
	// B/W - cursor inverting
	// NW - display mode
	uint8_t base_cmd = 0x08; // 0b00001000
	base_cmd = base_cmd | (FW << 2);
	base_cmd = base_cmd | (cursor_inverting << 1);
	base_cmd = base_cmd | NW;

	setRE(1);
	sendCommand(base_cmd);
	setRE(0);//@TODO is it required?
}

void SSD1311::setDisplayShift() {
	// [IS=0,RE=0,SD=0]
	// 0 0 0 1 S/C R/L 0 0
	// S/C - screen 1 or cursor 0
	// R/L - shift to right 1 or left 0
	uint8_t base_cmd = 0x18; // 0b00011000
	base_cmd = base_cmd | (display_shift_dir << 2);
	sendCommand(base_cmd);
}

void SSD1311::setCursorShift() {
	// [IS=0,RE=0,SD=0]
	// 0 0 0 1 S/C R/L 0 0
	// S/C - screen 1 or cursor 0
	// R/L - shift to right 1 or left 0
	uint8_t base_cmd = 0x10; // 0b00010000
	base_cmd = base_cmd | (cursor_shift << 2);
	sendCommand(base_cmd);
}

void SSD1311::setContrast(uint8_t level) {
	// [IS=X,RE=1,SD=1]
	// this is two bytes command
	setRE(1);
	setSD(1);
	sendCommand(0x81);
	sendCommand(level);
	setSD(0);
	setRE(0);
}

void SSD1311::setDDRAM(uint8_t addr) {
	// [IS=X,RE=0,SD=0]
	// 1 AC6 AC5 AC4 AC3 AC2 AC1 AC0
	// ACX - Address Counter bit
	addr = addr & B01111111;// remove top bit
	sendCommand(0x80 | addr);
};

void SSD1311::setCGRAM(uint8_t addr) {
	// [IS=0,RE=0,SD=0]
	// 0 1 AC5 AC4 AC3 AC2 AC1 AC0
	// ACX - Address Counter bit
	addr = addr & B00111111;// remove 2 top bit
	sendCommand(0x40 | addr);
};

void SSD1311::setCursorPosition(uint8_t col, uint8_t row) {
	uint8_t row_offsets[] = { 0x00, 0x20, 0x40, 0x60 };
	if (display_lines == 2 )
		row_offsets[1] = 0x40;
	setDDRAM(col + row_offsets[row]);
};

void SSD1311::selectRomRam(uint8_t rom, uint8_t ram) {
	// @NOTE:
	//      It is recommended to turn off the
	//      disply (cmd 08h) before setting no. of
	//      CGRAM and defining character ROM,
	//      while clear display (cmd 01h) is
	//      recommended to sent afterwards
	// [IS=X,RE=1,SD=0]
	// this is two bytes command
	// 0 0 0 0 RO1 RO0 OP1 OP0
	// RO[1:0]  ROM  |  OP[1:0]    CGROM    CGRAM
	//   00      A   |     00       240       8
	//   01      B   |     01       248       8
	//   10      C   |     10       250       6
	//   11  Invalid |     11       256       0
	rom = rom & B00000011;// remove all bits except last two
	ram = ram & B00000011;// remove all bits except last two
	setRE(1);
	sendCommand(0x72);
	sendData((rom << 2) | ram);
	setRE(0);
}

void SSD1311::switchToDataMode() {
	Wire.beginTransmission(mc_address);
	Wire.write(SSD1311_DATA_MODE);// Set OLED Data mode [Co=0, D/C#=1]
	Wire.endTransmission();
}

void SSD1311::switchToCmdMode() {
	Wire.beginTransmission(mc_address);
	Wire.write(SSD1311_CMD_MODE);// Set OLED Command mode [Co=1, D/C#=0]
	Wire.endTransmission();
}

void SSD1311::readRamSymbol(char *symb_data, uint8_t symb_ind) {
	setCGRAM(symb_ind*8);// each symbol is 8 bytes long
	switchToDataMode();
	readData(symb_data, 9);// 9 due to we have to ignore first line in answer //@TODO: fix that
}

void SSD1311::writeRamSymbol(char *symb_data, uint8_t symb_ind) {
	setCGRAM(symb_ind*8);
	uint8_t i=0;
	Wire.beginTransmission(mc_address);
	Wire.write(SSD1311_DATA_MODE);
	for (i=0; i < 8; i=i+1) {
		Wire.write(symb_data[i]);
	}
	Wire.endTransmission();
}

void SSD1311::readString(char *symb_data, uint8_t col, uint8_t row, uint8_t len) {
	setCursorPosition(col, row);
	switchToDataMode();
	readData(symb_data, len+1);// +1 due to we have to ignore first line in answer @TODO: fix that
}