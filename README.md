# Overview
This tiny library for Arduino offers you a very simple ```printf``` like function to use with your ```Serial``` setup which stores all strings automatically in ```PROGMEM``` space, so you do not use SRAM on your Arduino. This is always the prefered way to store strings and with this tiny helper, it is as simple as using ```printf```.

## Memory Problem
Why exactly is the aforementioned problem a real problem?

Let's see:
Image you want to display this garbage on your Arduino Uno (max 2 KB SRAM):

```javascript
Serial.print( \
  // over 2K of data
  //    0     5    10   5    20        30        40        50        60        70        80        90       100
  "00 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "01 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "02 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "03 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "04 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "05 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "06 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "07 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "08 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "09 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "10 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "11 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "12 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "13 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "14 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "15 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "16 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "17 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "18 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  "19 - 0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n" \
  );
```

Nothing will be printed at all on your serial monitor, you exhausted your SRAM on your MCU,
which can unfortunately not be checked inside the Arduino IDE. You have to enable verbose compilation
in the settings dialog and investigate the compiled program itself.

You need the second last line before 'Binary sketch size', the elf-file is the final 'program' in AVR machine code.

* On a Mac your need something like this:
```Shell
/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-size \
    -C --mcu=atmega328p \ 
    /var/folders/s9/z1rhsc815135dtf2sn8jwp1h0000gn/T/build4268546277391880544.tmp/SerialOutput.cpp.elf
```

* Linux and Windows are similar.

The output of the program is very interessting:

* If you use the code as described above (```Serial.print``` or ```printf```), it yields
* 
```javascript
AVR Memory Usage
----------------
Device: atmega328p

Program:    6780 bytes (20.7% Full)
(.text + .data + .bootloader)
 
Data:       2347 bytes (114.6% Full)
(.data + .bss + .noinit)
```
And you can clearly see, that the ```data``` section is too big.

* If you use the function from this tiny library called ```serialout```, it'll work and use very little SRAM.

```
AVR Memory Usage
----------------
Device: atmega328p

Program:    6258 bytes (19.1% Full)
(.text + .data + .bootloader)

Data:        227 bytes (11.1% Full)
(.data + .bss + .noinit)
```
# Usage

There are two version:

* Simple ```Serial.print()``` replacement
```javascript
p("This is my PROGMEM stored string\n");
```
* More complex ```printf``` replacement
```javascript
p("I am %d years old which is 0x%02X in hex and %04o in octal\n", 30, 30, 30);
```

# How it works

There are plenty to tutorials about ```PROGMEM```, yet I was too tired of typing or copying all the code together
to minimize the impact on my SRAM while pumping out tons of strings over serial.

So here is a list for reference:

* http://arduino.cc/en/pmwiki.php?n=Reference/PROGMEM
* http://playground.arduino.cc/Main/Printf