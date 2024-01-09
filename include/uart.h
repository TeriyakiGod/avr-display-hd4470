#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>

#define F_CPU 16000000UL                       // Define clock speed of the MCU
#define BAUD 9600                              // Define baud rate
#define BAUDRATE ((F_CPU) / (BAUD * 16UL) - 1) // Set baud rate speed

// Function to initialize the UART
void uart_init(void);

// Function to send data
void uart_transmit(uint8_t data);

// Function to receive data
unsigned char uart_receive(void);

#endif // UART_H