#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

// Array to map numbers to segments for common anode display
uint8_t segment_map[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90}; // 0-9

// Array to map digit select lines to PORTC for common anode display
uint8_t digit_select[4] = {0xF7, 0xFB, 0xFD, 0xFE}; // 1, 2, 3, 4

int get_digit(int number, int index)
{
    int pow = 1;
    for (int i = 0; i < index; i++)
        pow *= 10;
    return (number / pow) % 10;
}

int main(void)
{
    DDRA = 0xFF; // Port A Data Direction Register
    DDRB = 0x07; // Port C Data Direction Register - set the upper 3 bits as input for the buttons
    PORTA = 0;   // Port A Data Register
    PORTB = 0;   // Port C Data Register

    int count = 9100;
    int paused = 0;

    while (1)
    {
        if (!paused)
        {
            for (int i = 0; i < 4; i++)
            {
                int digit = get_digit(count, 3 - i);
                PORTC = digit_select[i];    // Select digit
                PORTA = segment_map[digit]; // Display digit
                _delay_ms(50);              // Delay for multiplexing
            }
            _delay_ms(50);
            count--;
            if (count < 8888)
            {
                count = 9100;
            }
        }
    }

    return 0;
}