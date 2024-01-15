#include <avr/io.h>
#include <util/delay.h>

// Define connections
#define LCD_RS 6
#define LCD_EN 4
#define LCD_DB4 3
#define LCD_DB5 2
#define LCD_DB6 1
#define LCD_DB7 0

#define LCD_PORT PORTB
#define LCD_DDR  DDRB

#define LCD_DIGIT_COUNT 16

#define TEXT "KOMM"
#define TEXT_LENGTH 4

// HD44780 LCD Command Codes
#define CLEAR_DISPLAY       0x01   // Clear display
#define RETURN_HOME         0x02   // Return to home position
#define ENTRY_MODE_SET      0x06   // Set cursor move direction and shift
#define DISPLAY_ON_OFF      0x0C   // Turn display on/off, cursor on/off, blink on/off
#define FUNCTION_SET        0x28   // Function set: 4-bit mode, 2 lines, 5x8 font
#define SET_DDRAM_ADDRESS_A 0x80   // Set DDRAM address command for first line
#define SET_DDRAM_ADDRESS_B 0xC0   // Set DDRAM address command for second line
#define SHIFT_DISPLAY_LEFT  0x18   // Shift display left
#define SHIFT_DISPLAY_RIGHT 0x1C   // Shift display right

#define LEFT 0
#define RIGHT 1
#define FIRST_ROW 0
#define SECOND_ROW 1

// Function prototypes
void LCD_command(unsigned char command);
void LCD_data(unsigned char data);
void LCD_init();
void LCD_clear();
void LCD_gotoxy(unsigned char x, unsigned char y);
void LCD_displayString(char *str);
void LCD_shiftText();

int main() {
    // Set data direction for LCD pins
    LCD_DDR |= (1 << LCD_RS) | (1 << LCD_EN) | (1 << LCD_DB4) | (1 << LCD_DB5) | (1 << LCD_DB6) | (1 << LCD_DB7);

    // Initialize LCD
    LCD_init();
    LCD_gotoxy(0, SECOND_ROW);
    LCD_displayString(TEXT);
    while (1) {
        for (int i = 0; i < LCD_DIGIT_COUNT-TEXT_LENGTH; i++) {
            _delay_ms(300);
            LCD_command(SHIFT_DISPLAY_RIGHT);
        }
        for (int i = 0; i < LCD_DIGIT_COUNT-TEXT_LENGTH; i++) {
            _delay_ms(300);
            LCD_command(SHIFT_DISPLAY_LEFT);
        }
    }

    return 0;
}

// Function to send a command to the LCD
void LCD_command(unsigned char command) {
    // Set the higher nibble of the command on the data bus (DB4-DB7)
    LCD_PORT = (LCD_PORT & 0xF0) | ((command >> 4) & 0x0F);

    // Set RS (Register Select) low to indicate a command
    LCD_PORT &= ~(1 << LCD_RS);

    // Generate a pulse on EN (Enable) pin to latch in the command
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);

    // Set the lower nibble of the command on the data bus (DB4-DB7)
    LCD_PORT = (LCD_PORT & 0xF0) | (command & 0x0F);

    // Generate another pulse on EN (Enable) pin to latch in the lower nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);

    // Introduce a delay to allow the LCD to process the command
    _delay_ms(2);
}

// Function to send data to be displayed on the LCD
void LCD_data(unsigned char data) {
    // Set the higher nibble of the data on the data bus (DB4-DB7)
    LCD_PORT = (LCD_PORT & 0xF0) | ((data >> 4) & 0x0F);

    // Set RS (Register Select) high to indicate data
    LCD_PORT |= (1 << LCD_RS);

    // Generate a pulse on EN (Enable) pin to latch in the data
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);

    // Set the lower nibble of the data on the data bus (DB4-DB7)
    LCD_PORT = (LCD_PORT & 0xF0) | (data & 0x0F);

    // Generate another pulse on EN (Enable) pin to latch in the lower nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);

    // Introduce a delay to allow the LCD to process the data
    _delay_ms(2);
}

void LCD_init() {
    _delay_ms(15);
    LCD_command(FUNCTION_SET);
    LCD_command(DISPLAY_ON_OFF);
    LCD_command(ENTRY_MODE_SET);
    LCD_command(CLEAR_DISPLAY);
}

void LCD_gotoxy(unsigned char x, unsigned char y) {
    if (y == 0) {
        LCD_command(SET_DDRAM_ADDRESS_A + x);
    } else if (y == 1) {
        LCD_command(SET_DDRAM_ADDRESS_B + x);
    }
}

void LCD_displayString(char *str) {
    while (*str != '\0') {
        LCD_data(*str);
        str++;
    }
}