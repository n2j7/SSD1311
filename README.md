#SSD1311 Library#

I'll add some description here

/**
 * LCD Info:
 *     2 lines x 16 cells
 *     5x7 (5x8) char
 *     256 step contrast
 *     i2c interface
 *     character generator 256 * 5x8 CGROM
 *     character generator 64 * 8 bits CGRAM
 *     display data 80 * 8 bits
 *     3 sets of CGROM (ROM A / B / C)
 *     Row Re-mapping and Column Re-mapping
 *     Double-height Font characters
 *     Bi-direction shift function
 *     All character reverse display
 *     Display shift per line
 *     Screen saving fade in / out feature
 *     
 *     
 * Notes:
 *     Frame:
 *     (1) i2c address is 7 bit long
 *     (2) next bit is a direction (READ or WRITE)
 *     (3) next byte define is it command or data packet
 *     (4) next byte is the command|data byte
 *     
 *     
 *     IS, RE, SD is a logical bits which can be set by doing command request to LCD
 *     D/C# is a (3) in frame. First Wire.write after Wire.beginTransmission in code
 *     R/W# is a bit (2) in frame. 
 *         You can "control" it by doing Wire.requestFrom() or Wire.beginTransmission()
 *         R/W# = 0 when Wire.beginTransmission()
 *         R/W# = 1 when Wire.requestFrom()
 *
 * Character Generator RAM (CGRAM)
 * Display Data RAM (DDRAM)
 *
 * Links:
 *     https://playground.arduino.cc/Main/WireLibraryDetailedReference
 *     http://playground.arduino.cc/Code/BitMath
 *     https://www.i2c-bus.org/addressing/
 *     
 */

![OLED i2c 1602 Screen](http://www.wide.hk/image/cache/catalog/I2C1602/1602OLED_2-500x500.jpg)
