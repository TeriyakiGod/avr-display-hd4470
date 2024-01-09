#include <uart.h>

// Function to initialize the UART
void uart_init(void)
{
    UBRRH = (BAUDRATE >> 8);                             // Shift the register right by 8 bits
    UBRRL = BAUDRATE;                                    // Set baud rate
    UCSRB |= (1 << TXEN) | (1 << RXEN);                  // Enable receiver and transmitter
    UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // 8bit data format
}

// Function to send data
void uart_transmit(uint8_t data)
{
    char buffer[3];
    sprintf(buffer, "%02X", data); // Convert binary value to hexadecimal string

    for (int i = 0; buffer[i]; i++)
    {
        while (!(UCSRA & (1 << UDRE)))
            ;            // Wait for empty transmit buffer
        UDR = buffer[i]; // Send data
    }

    while (!(UCSRA & (1 << UDRE)))
        ;       // Wait for empty transmit buffer
    UDR = 0x0A; // Send new line character
}

// Function to receive data
unsigned char uart_receive(void)
{
    while (!(UCSRA) & (1 << RXC))
        ;       // Wait while data is being received
    return UDR; // Return the data
}