#include <avr/io.h>
#include <util/delay.h>

#define RESET_BUTTON_PIN PINC5
#define PAUSE_BUTTON_PIN PINC6
#define PLAY_BUTTON_PIN PINC7

// Array to map numbers to segments for common anode display
uint8_t segment_map[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90}; // 0-9

// Array to map digit select lines to PORTC for common anode display
uint8_t digit_select[4] = {0xFE, 0xFD, 0xFB, 0xF7}; // 1, 2, 3, 4

int main(void)
{
    DDRA = 0xFF; // Port A Data Direction Register
    DDRC = 0x07; // Port C Data Direction Register - set the upper 3 bits as input for the buttons
    PORTA = 0;   // Port A Data Register
    PORTC = 0;   // Port C Data Register

    int count = 9100;
    int iteration = 0;
    int paused = 0;
    while (1)
    {
        if (!(PINC & (1 << RESET_BUTTON_PIN))) // If reset button is pressed
        {
            count = 9100;
            iteration = 0;
        }

        if (!(PINC & (1 << PAUSE_BUTTON_PIN))) // If pause button is pressed
        {
            paused = 1;
        }

        if (!(PINC & (1 << PLAY_BUTTON_PIN))) // If play button is pressed
        {
            paused = 0;
        }

        if (!paused)
        {
            for (int i = 0; i < 4; i++)
            {
                PORTC = digit_select[i];                                // Select digit
                PORTA = ~segment_map[count / (int)pow(10, 3 - i) % 10]; // Extract digit at position i and display
                _delay_ms(50);                                          // Delay for multiplexing
            }

            iteration++;
            if (iteration % 5 == 0)
            {
                count--; // Decrement count every 5 iterations (250ms)
            }
            if (count < 8888) // Reset count to 9100 after 10 seconds
            {
                count = 9100;
                iteration = 0;
            }
        }
    }

    return 0;
}