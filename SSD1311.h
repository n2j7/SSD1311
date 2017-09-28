#ifndef SSD1311_h
#define SSD1311_h 1
#include "Arduino.h"
#include "Wire.h"

#define SSD1311_LCD_ON 1
#define SSD1311_LCD_OFF 0
#define SSD1311_CMD_MODE 0x80// ONE next byte is COMMAND, next one have to be one from (0x80;0x40;0xC0)
#define SSD1311_DATA_MODE 0x40// ALL next bytes will be read as a DATA
#define SSD1311_DATA_BATCH_MODE 0xC0// ONE next byte is DATA, next one have to be from (0x80;0x40;0xC0)

#define SSD1311_CGRAM_240 0
#define SSD1311_CGRAM_248 1
#define SSD1311_CGRAM_250 2
#define SSD1311_CGRAM_256 3

#define SSD1311_CGRAM_1 0 // alias for 240
#define SSD1311_CGRAM_2 1 // alias for 248
#define SSD1311_CGRAM_3 2 // alias for 250
#define SSD1311_CGRAM_4 3 // alias for 256

#define SSD1311_ROM_A 0
#define SSD1311_ROM_B 1
#define SSD1311_ROM_C 2


class SSD1311 {
	public:
		uint8_t cursor_on;
		uint8_t cursor_blinking;
		uint8_t reverse_mode;
		uint8_t double_height;
		uint8_t cursor_inverting;
		uint8_t display_shift;
		uint8_t cursor_shift;
		SSD1311();
		~SSD1311();
		void powerMode(uint8_t is_on);
		void sendCommand(unsigned char command);
		void sendData(unsigned char data);
		void sendBatch(unsigned char pack[], uint8_t length);
		void sendString(const char *String, uint8_t col, uint8_t row);
		void readData(char *buf, uint8_t length);
		void clear();
		void setFont();
		void setDisplayShift();
		void setCursorShift();
		void setContrast(uint8_t level);
		void setDDRAM(uint8_t addr);
		void setCGRAM(uint8_t addr);
		void setCursorPosition(uint8_t col, uint8_t row);
		void selectRomRam(uint8_t rom, uint8_t ram);
		void switchToDataMode();
		void switchToCmdMode();
		void readRamSymbol(char *symb_data, uint8_t symb_ind);
		void writeRamSymbol(char *symb_data, uint8_t symb_ind);
		void readString(char *symb_data, uint8_t col, uint8_t row, uint8_t len);
	protected:
		uint8_t mc_address;
		uint8_t IS;
		uint8_t RE;
		uint8_t SD;
		uint8_t N;// Display line number control bit
		uint8_t NW;// 4 Line mode enable bit
		uint8_t FW;
		uint8_t display_lines;
		void setRE(uint8_t state);
		void setIS(uint8_t state);
		void setSD(uint8_t state);

	/*
		TODO:
			- Entry Mode Set
			- Double Height (4-line) / Display-dot shift
			- Shift Enable
			- Scroll Enable
			- Set Scroll Quantity
			- Read Busy Flag and Address/ Part ID
			--------------------------
			- Vdd regulator at 5V I/O application mode
			- Set Display Clock Divide Ratio/Oscillator Frequency
			- Set Phase Length
			- Set SEG Pins Hardware Configuration
			- Set V COMH Deselect Level
			- Function Selection C
			- Set Fade Out and Fade in / out
			--------------------------------------------
			- implement batch mode inside commands
	*/
};
#endif