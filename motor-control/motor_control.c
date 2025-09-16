/*
 * PIC18F4580 Motor Control with LCD
 * Author: Jizan Rehman
 * 
 * Functionality:
 * - RB0 button → Rotate motor clockwise, display "clockwise"
 * - RB1 button → Rotate motor anti-clockwise, display "Anti-clockwise"
 * - RB2 button → Stop motor, display "stop"
 */

#include <pic18.h>

// Function Prototypes
void delay(void);
void data(char d);
void com(char c);
void print(char *p);

void main()
{
    TRISC = 0x00;    // PORTC as output (motor + LCD control)
    TRISD = 0x00;    // PORTD as output (LCD data lines)
    TRISB = 0xFF;    // PORTB as input (buttons)
    ADCON1 = 0x0F;   // Configure PORTB as digital

    // LCD Initialization
    com(0x01);   // Clear display
    com(0x38);   // 8-bit mode, 2-line display
    com(0x06);   // Auto-increment cursor
    com(0x0F);   // Display on, cursor blinking
    com(0x80);   // Set cursor to first line

    while (1)
    {
        // Clockwise
        if (RB0 == 0)
        {
            com(0x01);  // Clear LCD
            RC0 = 1;
            RC1 = 0;
            delay();
            print("clockwise");
        }

        // Anti-clockwise
        if (RB1 == 0)
        {
            com(0x01);
            RC0 = 0;
            RC1 = 1;
            delay();
            print("Anti-clockwise");
        }

        // Stop
        if (RB2 == 0)
        {
            com(0x01);
            RC0 = 0;
            RC1 = 0;
            delay();
            print("stop");
        }
    }
}

// Print string to LCD
void print(char *p)
{
    while (*p)
    {
        data(*p);
        p++;
    }
}

// Send data to LCD
void data(char d)
{
    LATD = d;
    RC6 = 1;    // RS = 1 (data)
    RC7 = 1;    // EN = 1
    delay();
    RC7 = 0;    // EN = 0
}

// Send command to LCD
void com(char c)
{
    LATD = c;
    RC6 = 0;    // RS = 0 (command)
    RC7 = 1;    // EN = 1
    delay();
    RC7 = 0;    // EN = 0
}

// Delay function
void delay(void)
{
    for (int i = 0; i < 300; i++)
        for (int j = 0; j < 300; j++);
}

