# SSD1311 Library

I've searched for good library for my OLED 16x02 screen, but i haven't found anything! So i've tried to implement my own library! 
There were some pieces of code in different repositories without any(or poor) description what each part do, with strange method names and bad comments...
I've started to search information about my OLED screen and have found a full SSD1311 controller datasheet on which my screen was based!

So, what i have:

* `wide.hk` label on the front left side
* `Op162i` text on the back
* `1602 i2c OLED screen` as product name from seller 
* product picture with link to youtube https://youtube.com/watch?v=74Wso_3TskA

![ssd1311 16x02 screen][device]

After some research i had:

* controller SSD1311
* OLED screen
* 2 lines x 16 cells
* 5x7 (5x8) char
* 256 step contrast
* i2c interface
* character generator 256 * 5x8 CGROM
* character generator 64 * 8 bits CGRAM
* display data 80 * 8 bits
* 3 sets of CGROM (ROM A / B / C)
* Row Re-mapping and Column Re-mapping
* Double-height Font characters
* Bi-direction shift function
* All character reverse display
* Display shift per line
* Screen saving fade in / out feature

Useful links:

+ [Product at original site](http://www.wide.hk/index.php?route=product/product&path=18_46&product_id=69)
+ [Blogpost about screen](https://gadjetsblog.blogspot.com/2013/09/oled-1602-display-and-library-for.html)
+ [Library on github with very awful code](https://github.com/gadjet/1602-OLED-Arduino-Library)
+ [Library for Raspberry Pi](https://github.com/0xFACE/RPi-OLED-Display-SSD1311)
+ [Scroll text example](https://github.com/nathanchantrell/OLED1602)
+ [Another library with awful code](https://github.com/rafaelcamacho/Oled-SSD131x)
+ [One more library](https://github.com/jafrado/2004_i2c_oled)

More links with some basic information:

- [Wire Library](https://playground.arduino.cc/Main/WireLibraryDetailedReference)
- [Bits operations](http://playground.arduino.cc/Code/BitMath)
- [i2c Adressing](https://www.i2c-bus.org/addressing/)

### Notes about library core:

Frame consist of:

* (1) i2c address is 7 bit long
* (2) next bit is a direction (READ or WRITE)
* (3) next byte define is it command or data packet
* (4) next byte is the command|data byte

Datasheet contains some naming for important moments. There are some explanations:

`IS`, `RE`, `SD` is a logical bits which can be set by doing command requests to screen

`D/C#` is a (3) in frame. First `Wire.write` after `Wire.beginTransmission` in code

`R/W#` is a bit (2) in frame. You can "control" it by doing `Wire.requestFrom()` or `Wire.beginTransmission()`

  *  R/W# = 0 when Wire.beginTransmission()
  *  R/W# = 1 when Wire.requestFrom()

CGRAM is Character Generator RAM

DDRAM is Display Data RAM

[device]: https://github.com/n2j7/SSD1311/raw/master/media/screen16x02.jpg