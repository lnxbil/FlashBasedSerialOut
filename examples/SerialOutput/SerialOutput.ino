// This is an example to use strings stored in PROGMEM (flash)
// instead of using strings stored in RAM.
//
// The serialout is a macro wrapper around PSTR, which is used
// under the hood.

#include <FlashBasedSerialOut.h>

void setup()
{
  Serial.begin(57600);
  begin_serial();
  
  // direct output without string formatting
  serialout("FlashBasedSerialOut - Strings stored in PROGMEM instead of RAM\n\n");
  
  /* This line here is now the cruial part, because it allocates TOO much RAM, which
   * can unfortunately not be checked in Arduino IDE, yet you can enable verbose compilation
   * and investigate the compiled program itself.
   * You need the second last line before 'Binary sketch size', the elf-file is the final
   * 'program' in AVR machine code.
   *
   * On a Mac your need something like this:
   *
   * /Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-size \
   *     -C --mcu=atmega328p \ 
   *     /var/folders/s9/z1rhsc815135dtf2sn8jwp1h0000gn/T/build4268546277391880544.tmp/SerialOutput.cpp.elf
   *
   * using 'printf' results in a really full DATA section,  crashing MCU due to RAM shortage
   *
   *     AVR Memory Usage
   *     ----------------
   *     Device: atmega328p
   *   
   *     Program:    6780 bytes (20.7% Full)
   *     (.text + .data + .bootloader)
   *     
   *     Data:       2347 bytes (114.6% Full)
   *     (.data + .bss + .noinit)
   *
   * 
   *  If you use 'serialout' instead of 'printf' it works!
   *
   *     AVR Memory Usage
   *     ----------------
   *     Device: atmega328p
   *   
   *     Program:    6258 bytes (19.1% Full)
   *     (.text + .data + .bootloader)
   *   
   *     Data:        227 bytes (11.1% Full)
   *     (.data + .bss + .noinit)
   */

  // use printf/Serial.print for crash or serialout for working example!
  serialout( \
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
  
  serialout("I am %d years old which is 0x%02X in hex and %04o in octal\n", 30, 30, 30);
}

void loop()
{
  unsigned long current_time = micros();
  
  // direct output with string formatting
  serialout("Current MCU time is %010lu\n",  current_time);
  delay(1000);
}