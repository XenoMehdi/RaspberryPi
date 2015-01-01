#include "lcd.h"

int  lcd_hundler;

void lcd_initialize ( const char *ip ){

// Setup the wiringPi library
wiringPiSetup();
// Set  and LCD_A as outputs
pinMode(LCD_A, OUTPUT);

// Trigger GPIO.10 ON
digitalWrite (LED, HIGH) ;

// Initialize Lcd
lcd_hundler = lcdInit( 2, 16, 4, RS, EN, D4, D5, D6, D7, D_UNUSED, D_UNUSED, D_UNUSED, D_UNUSED) ;

// display the result of lcd initialization
if(lcd_hundler == -1)
{
printf("Lcd init fail..\n");
digitalWrite (LCD_A, LOW) ;
}
else
{
// set cursor on the initial position
lcdHome (lcd_hundler) ;
// clear lcd
lcdClear (lcd_hundler) ;
// turn off cursor blinking
lcdCursorBlink (lcd_hundler, FALSE) ;
// turn display on (TRUE)
lcdDisplay (lcd_hundler, TRUE) ;

// write Hello on screen 
lcdPosition (lcd_hundler, 0, 0) ; lcdPuts (lcd_hundler, "  FEZ EMBEDDED  ") ;
lcdPosition (lcd_hundler, 0, 1) ; lcdPuts (lcd_hundler, "SYSTEMS INDUSTRY") ;

printf("Lcd init succes..\n");
digitalWrite (LCD_A, HIGH) ;
}
sleep(3);
// clear lcd
lcdClear (lcd_hundler) ;
lcdPosition (lcd_hundler, 0, 0) ; lcdPuts (lcd_hundler, "    F.E.S.I     ") ;
lcdPosition (lcd_hundler, 2, 1) ; lcdPuts (lcd_hundler, ip) ;

}
