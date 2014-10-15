/*
 Copyright (C) 2014 Andreas Steinel <A.Steinel@gmail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * @file FlashBasedSerialOut.h
 *
 * Macro wrapper for outputting to serial while using PROGMEM
 * instead of RAM for storing string data.
 */


#ifndef __FLASH_BASED_SERIAL_OUT_H
#define __FLASH_BASED_SERIAL_OUT_H

#if ARDUINO < 100
    #include <WProgram.h>
#else
    #include <Arduino.h>
#endif

#include <avr/pgmspace.h>
#include <stdio.h>

// Code from 
// http://playground.arduino.cc/Main/Printf

// create a FILE structure to reference our UART output function
static FILE uartout = {0} ;

// create a output function
// This works because Serial.write, although of
// type virtual, already exists.
static int uart_putchar (char c, FILE *stream)
{
    Serial.write(c) ;
    return 0 ;
}

void begin_serial() {
    // fill in the UART file descriptor with pointer to writer.
    fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);

    // The uart is the standard output device STDOUT.
    stdout = &uartout ;
}

#define p(str, ...) printf_P( PSTR(str), ##__VA_ARGS__ ) 
#define serialout p

#endif // __FLASH_BASED_SERIAL_OUT_H
