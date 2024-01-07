#include <avr/io.h>
int main(void)
{
    TCCR1B = 0x04;
    DDRA = 0xFF;
    PORTA = 0;
    while (1)
    {
        if (TCNT1 >= 100)
        {
            PORTA++;
            TCNT1 = 0;
        }
    }
    return 0;
}